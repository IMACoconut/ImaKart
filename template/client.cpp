#include <Network.hpp>
#include <Utility.hpp>
#include <iostream>
#include <thread>
#include <atomic>

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


bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

std::atomic_bool running;

void writeToScreen(const std::string& msg)
{
    std::cout << msg << std::endl;
}
void recvFunc(NzTcpSocket* s)
{
    while(running)
    {
        NzPacket* p = s->Read();
        if(p != nullptr)
        {
            if(NzPacketDecoder::GetDataType(p) == 1) {
                Message m = NzPacketDecoder::GetData<Message>(p);
                writeToScreen(m.getMessage());
            }
            p->drop();
        }
        pause(500);
    }
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

    nzSocketProtocol ipproto = nzSocketProtocol_IPV4;
    std::string broadip = "255.255.255.255";

    std::vector<NzNetAddress> remote;
    NzNetAddress broadcast(broadip, 30001, ipproto);
    NzPacket* p = new NzPacket(Message("hello"));

    NzUdpSocket list(NzNetAddress(30002, ipproto));
    list.SetNonBlocking(true);
    list.AllowBroadcast(true);
    list.WriteTo(p, broadcast);

    p->drop();
    Util::Clock c;
    do {
        NzNetAddress server;
        p = list.ReadFrom(server);
        if(p == nullptr)
            pause(500);
        else {
        	writeToScreen(server.GetAddress());
            remote.push_back(server);
            p->drop();
            break;
        }

    } while(c.GetSeconds() < 5);

    if(remote.empty())
    {
        std::cout << "No server found." << std::endl;
    }
    else {
        for(size_t i = 0; i<remote.size(); ++i)
        {
            //NzPing pi = NzPingService::Ping(NzNetAddress(remote.at(i).GetAddress(), 0, ipproto));
            std::cout << i+1 << "/ " << remote.at(i).GetAddress() << ":" << remote.at(i).GetPort() << std::endl;//" | " << pi.ms << "ms" << std::endl;
        }
    }

    std::string a;
    int srv = -1;

    do {
        std::cout << "chose a server" << std::endl;
        std::cin >> a;
        if(!is_number(a))
        {
            std::cout << "not a valid number" << std::endl;
        }
        size_t tmp = Util::FromString<size_t>(a);
        if(tmp > 0 && tmp <= remote.size())
            srv = tmp;

    } while(srv == -1);

    std::string nick;
    std::cout << "Enter a nickname: " << std::endl;
    std::cin >> nick;

    std::cout << "Connecting to " << remote.at(srv-1).GetAddress() << ":" << remote.at(srv-1).GetPort() << std::endl;

    NzTcpSocket s(NzNetAddress(remote.at(srv-1).GetAddress(), 30002));
    if(s.IsConnected())
    {
        NzPacket* p2 = new NzPacket(Message(nick));
        s.Write(p2);
        p2->drop();
        running = true;
        std::thread recvThread(recvFunc, &s);
        std::cout << "Connected to remote server" << std::endl;

        std::string msg;
        do {
            std::getline(std::cin, msg);
            NzPacket* p = new NzPacket(Message(msg));
            s.Write(p);
            p->drop();
        } while(msg != "/exit");
        s.Close();
        running = false;
        recvThread.join();

    } else {
        std::cout << "fail" << std::endl;
    }
	
   // delete client;
    return EXIT_SUCCESS;
}