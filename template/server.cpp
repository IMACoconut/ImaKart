#include <Network.hpp>
#include <Utility.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

std::string ip;
uint16_t port;

/* On définit une classe message qu'on peut envoyer sur le réseau */
class Message : public NzSerializable
{
public:
    Message() {} // L'objet sérialisable doit avoir un constructeur par défaut.

    Message(const std::string& msg) : m_msg(msg) {}

    // Fonctions de sérialisation à redéclarer impérativement
    virtual void Serialize(NzArchive& flux) const
    {
        flux << m_msg;
    }
    virtual void Deserialize(NzArchive& flux)
    {
        flux >> m_msg;
    }
    virtual int GetID() const
    {
        return 1;
    }
    virtual int GetVersion() const
    {
        return 1;
    }

    std::string getMessage() { return m_msg; }

private:
    std::string m_msg;
};

class Client {
    public:
        Client(NzTcpSocket* s, const std::string& n) : socket(s), name(n) {}
        ~Client() { delete socket; }
        NzTcpSocket* socket;
        std::string name;
};

std::atomic_bool running;
std::vector<Client*> clients;
std::vector<NzTcpSocket*> pending;
std::mutex mutexClients;
std::mutex mutexPending;
std::mutex mutexLog;

bool is_empty(const std::string& str) {
	for(size_t i = 0; i<str.size(); ++i)
		if(str[i] != ' ')
			return false;

	return true;
}

void writeToLog(const std::string& msg)
{
    // On récupère l'heure locale
    std::string line;
    line.reserve(23);
    line.resize(23);
    time_t currentTime = std::time(nullptr);
	std::strftime(&line[0], 24, "%d/%m/%Y - %H:%M:%S", std::localtime(&currentTime));

	// Puis on écrit le message dans le log.
	// NB: Vous pouvez très bien logguer dans un fichier plutôt que dans la console.
    std::lock_guard<std::mutex> lock(mutexLog);
    std::cout << "[" << line << "] " << msg << std::endl;
}

void addNewClient(Client* c)
{
    std::lock_guard<std::mutex> lock(mutexClients);
    clients.push_back(c);
    writeToLog("client added to pending list");
}

void removeClient(Client* c)
{
    std::lock_guard<std::mutex> lock(mutexClients);

    for(std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
        if(*it == c)
        {
            clients.erase(it);
            break;
        }
}

void addPendingClient(NzTcpSocket* c)
{
    std::lock_guard<std::mutex> lock(mutexPending);
    pending.push_back(c);
}

void removePendingClient(NzTcpSocket* c)
{
    std::lock_guard<std::mutex> lock(mutexPending);

    for(std::vector<NzTcpSocket*>::iterator it = pending.begin(); it != pending.end(); ++it)
        if(*it == c)
        {
            pending.erase(it);
            break;
        }
}

// Fonction qui est en attente des nouvelles demandes
//
void allowPeerDiscovery()
{
    // On créé une socket UDP écoutant sur le port 30001
    NzUdpListener listener(NzNetAddress(30001));

    // On la met en mode non bloquant pour que la fonction readfrom puisse se terminer
    // si on a pas reçu de message.
    listener.SetNonBlocking(true);
    NzNetAddress from;
    NzPacket* p;
    while(running)
    {
        // On vérifie si l'on a reçu un paquet.
        p = listener.ReadFrom(from);

        if(p != nullptr)
        {
            // Ici l'objet from est rempli avec les informations du client distant

            // On log la détection du broadcast du client
            writeToLog("client broadcasted from " + from.GetAddress() + ":" + Util::ToString(from.GetPort()));

            // On renvoie son message au client: il sait qu'un serveur existe.
            listener.WriteTo(p, from);

            // On libère la mémoire du packet.
            p->drop();
        } else
        {
            // On a rien reçu, on met donc le thread en pause.
            pause(500);
        }
    }
}

void checkPendingClients()
{
    NzTcpSocket* client;
    NzPacket* p = nullptr;
    size_t i = 0;
    while(running)
    {
        client = nullptr;
        {
            std::lock_guard<std::mutex> lock(mutexPending);
            if(!pending.empty())
            {
                if(i >= pending.size())
                    i = 0;

                client = pending.at(i);
            }
        }
        if(!client)
        {
            pause(500);
            continue;
        }

        p = client->Read();
        if(!p)
        {
            pause(500);
            continue;
        }

        if(NzPacketDecoder::GetDataType(p) != 1)
        {
            writeToLog("Dropped client <"+ client->GetBindAddress().GetAddress() + ":" + Util::ToString(client->GetBindAddress().GetPort())+">. Reason: sent invalid data");
            removePendingClient(client);
            delete client;
            i++;
            continue;
        }
        Message m = NzPacketDecoder::GetData<Message>(p);
        Client* c = new Client(client, m.getMessage());
        addNewClient(c);
        removePendingClient(client);
        writeToLog(c->name+" logged in");
        p->drop();

    }

}

void allowPeerConnection()
{
    NzTcpListener listener(NzNetAddress(30002));
    listener.SetNonBlocking(true);
    while(running)
    {
        NzTcpSocket* c = listener.WaitForClient();
        if(c == nullptr)
            pause(500);
        else {
            writeToLog("client connected from " + c->GetBindAddress().GetAddress() + ":" + Util::ToString(c->GetBindAddress().GetPort()));
            c->SetNonBlocking(true);
            addPendingClient(c);
        }
    }
}

void removeAllClients()
{
    std::lock_guard<std::mutex> lock(mutexClients);
    while(!clients.empty())
    {
        delete clients.back();
        clients.pop_back();
    }
}

void sendAll(NzPacket* p)
{
    std::lock_guard<std::mutex> lock(mutexClients);
    for(std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
        (*it)->socket->Write(p);

}
void recvFunc()
{
    size_t i = 0;
    Client* client;
    while(running)
    {
        client = nullptr;
        {
            std::lock_guard<std::mutex> lock(mutexClients);

            if(!clients.empty())
            {
                if(i >= clients.size())
                    i = 0;

                client = clients.at(i);
            }
        }
        if(!client)
        {
            pause(100);
            continue;
        }
        
       	NzPacket* p = client->socket->Read();
        if(!p)
        {

            pause(100);
            i++;
            continue;
        }
        if(NzPacketDecoder::GetDataType(p) == 1)
        {

            Message m = NzPacketDecoder::GetData<Message>(p);
            std::string msg = m.getMessage();
            NzPacket* p2 = nullptr;
            std::cout << msg.substr(0,5) << std::endl;
            if(msg.substr(0,5) == "/exit")
            {
                p2 = new NzPacket(Message(client->name+" has left"));
                removeClient(client);
            }
            else if(msg.substr(0,6) == "/nick ")
            {
                std::string nick = msg.substr(6);
                p2 = new NzPacket(Message(client->name+" is now known as "+nick));
                client->name = nick;
            }
            else if(!is_empty(msg)) {
                p2 = new NzPacket(Message(client->name+": "+m.getMessage()));
            }

            if(p2) {
                sendAll(p2);
                writeToLog("<"+client->socket->GetBindAddress().GetAddress()+":"+Util::ToString(client->socket->GetBindAddress().GetPort())+ "> " + client->name + ": " + m.getMessage());
                p2->drop();
            }
        }
        p->drop();

        i++;
    }

    removeAllClients();
}

template <typename T>
struct Initializer {
public:
	Initializer() {
		T::Initialize();
	}
	~Initializer() {
		T::Uninitialize();
	}
};

int main()
{
	Initializer<NzNetwork> network;

    running = true;
    std::thread pendingThread(checkPendingClients);
    std::thread peerDiscovery(allowPeerDiscovery);
   	std::thread peerConnection(allowPeerConnection);
    std::thread recvThread(recvFunc);
    std::cout << "All threads running" << std::endl;
    std::string a;
    do {
        std::cin >> a;
        if(a == "exit")
            running = false;
    } while(running);

    pendingThread.join();
    peerDiscovery.join();
    peerConnection.join();
    recvThread.join();

	return EXIT_SUCCESS;
}
