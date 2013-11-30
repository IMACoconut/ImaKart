#include <Graphics.hpp>
#include <Utility.hpp>
#include <Network.hpp>
#include <Game/Network/NetworkTCP.hpp>
#include <Game/Network/NetworkUDP.hpp>

#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>
#include <TGUI/TGUI.hpp>

#include <Game/Entity.hpp>
#include <Game/Component.hpp>
#include <Game/kart.hpp>
#include <Game/alteration.hpp>
#include <Game/VectorAlt.hpp>

#include <Graphics/Scene/OrbitCamera.hpp>

#include <unistd.h>

#include <iostream>
#include <vector>

#define THEME_CONFIG_FILE "../resources/widgets/Black.conf"

static const unsigned int FPS = 30;

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
void loadWidgets( tgui::Gui& gui )
{
    // Create the username label
    tgui::Label::Ptr labelUsername(gui);
    labelUsername->setText("Username:");
    labelUsername->setPosition(200, 100);
 
    // Create the password label
    tgui::Label::Ptr labelPassword(gui);
    labelPassword->setText("Password:");
    labelPassword->setPosition(200, 250);
 
    // Create the username edit box
    tgui::EditBox::Ptr editBoxUsername(gui, "Username");
    editBoxUsername->load("../resources/widgets/Black.conf");
    editBoxUsername->setSize(400, 40);
    editBoxUsername->setPosition(200, 140);
 
    // Create the password edit box (we will copy the previously created edit box)
    tgui::EditBox::Ptr editBoxPassword = gui.copy(editBoxUsername, "Password");
    editBoxPassword->setPosition(200, 290);
    editBoxPassword->setPasswordCharacter('*');
 
    // Create the login button
    tgui::Button::Ptr button(gui);
    button->load("../resources/widgets/Black.conf");
    button->setSize(260, 60);
    button->setPosition(270, 440);
    button->setText("Login");
    button->bindCallback(tgui::Button::LeftMouseClicked);
    button->setCallbackId(1);
}

int main(void) {

	Game::Kart kart;
	std::vector<std::string> affectedVariable;
	affectedVariable.push_back("maniability");
	affectedVariable.push_back("weight");

	std::vector<float> factor;
	factor.push_back(5);
	factor.push_back(9);

	Game::FactorAlteration alt = Game::FactorAlteration("yo", affectedVariable, factor, 5);

	std::cout<<"maniability : "<<kart.get<float>("maniability")<<" weight : "<< kart.get<float>("weight")<<" alteration : "<<(kart.get<Game::VectorAlt>("alterations")).size()<<std::endl;

	kart.update();

	std::cout<<"maniability : "<<kart.get<float>("maniability")<<" weight : "<< kart.get<float>("weight")<<" alteration : "<<(kart.get<Game::VectorAlt>("alterations")).size()<<std::endl;

	kart.addAlteration(&alt);

	std::cout<<"maniability : "<<kart.get<float>("maniability")<<" weight : "<< kart.get<float>("weight")<<" alteration : "<<(kart.get<Game::VectorAlt>("alterations")).size()<<std::endl;

	for (int i = 0; i < 8; ++i)
	{
		kart.update();

		std::cout<<"maniability : "<<kart.get<float>("maniability")<<" weight : "<< kart.get<float>("weight")<<" alteration : "<<(kart.get<Game::VectorAlt>("alterations")).size()<<std::endl;
	}

	std::cout<<"lol"<<std::endl;
	 return 0;

	tinyxml2::XMLDocument doc;
	doc.LoadFile("../resources/data/config.xml");

	uint32_t WINDOW_WIDTH = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("width")->GetText()));
	uint32_t WINDOW_HEIGHT = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("height")->GetText()));

	Util::LogManager::init();
	NzNetwork::Initialize();
	/*NetworkTCP* tcp = new NetworkTCP(NzNetAddress(30001), true);
	NetworkUDP* udp = new NetworkUDP(NzNetAddress(30002), true);
	udp->send(new NzPacket(Message("coucou")));
	pause(10000);
	return 0;*/
	Util::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL4Imacs");
	if (window.getGui().setGlobalFont("../resources/widgets/DejaVuSans.ttf") == false)
        return 1;
 
    loadWidgets(window.getGui());

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		Util::LogManager::error("Unable to initialize GLEW : "+Util::ToString(glewGetErrorString(glewCode)));
		return EXIT_FAILURE;
	}

	
	Graph::Shader* skyShader = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"skyBox", "../resources/shaders/skybox.vert", "../resources/shaders/skybox.frag");
	Graph::Shader* celShad = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"celShad", "../resources/shaders/textured.vert", "../resources/shaders/textured.frag");

	Graph::Shader* lightPoint = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightPoint", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightPoint.frag");
	Graph::Shader* lightDirectional = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightDirectional", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightDirectional.frag");
	Graph::Shader* lightSpot = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightSpot", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightSpot.frag");

	glClearColor(0,0,0,0);

	Graph::Heightmap mesh;
	if(!mesh.loadFromFile("../resources/maps/dummy2/heightmap.png")) {
		std::cerr << "Error" << std::endl;
	}
	Graph::Material hmtex;
	if(!hmtex.loadFromFile("../resources/maps/dummy2/detail.png")) {
		std::cerr << "Error while loading material" << std::endl;
	}
	mesh.setMaterial(0, &hmtex);
	mesh.setScale(glm::vec3(16,16,16));
	mesh.setShader(celShad);
	Graph::Skydome sky;
	sky.setShader(skyShader);

	Graph::Mesh mesh2(Graph::Mesh::CreateQuad(sf::Color(0,127,255, 127)));
	mesh2.setScale(glm::vec3(5000,5000,1));
	mesh2.setRotation(glm::vec3(90,0,0));
	mesh2.setPosition(glm::vec3(127*16,12*1*100,127*16));
	/*Graph::Material nmtex;
	if(!nmtex.loadFromFile("../resources/images/normalmap.png")) {
		std::cerr << "Error while loading material" << std::endl;
	}
	mesh2.setMaterial(1,&nmtex);*/
	mesh2.getMeshBuffer(0)->setRenderMode(Graph::RenderMode::AlphaBlending);
	
	Graph::PointLight light;
	light.setColor(glm::vec3(0,1,0));
	light.setIntensity(3.f);
	light.setRadius(1000.f);
	light.setPosition(glm::vec3(128*16,100.f*15,128*16));
	light.setShader(lightPoint);

	Graph::PointLight light4;
	light4.setColor(glm::vec3(0,0,1));
	light4.setIntensity(10.f);
	light4.setRadius(100.f);
	light4.setPosition(glm::vec3(128*16,100.f*16,128*16));
	light4.setShader(lightPoint);

	Graph::SpotLight light2;
	light2.setColor(glm::vec3(1,0, 0));
	light2.setShader(lightSpot);

	Graph::DirectionalLight light3;
	light3.setColor(glm::vec3(1,1,1));
	light3.setIntensity(.4f);
	light3.setPosition(glm::vec3(0,-9000,0));
	light3.setShader(lightDirectional);
	//s.bind();*/
	Graph::Scene scene;
	Graph::OrbitCamera cam(window, &mesh);
	cam.setAspect(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.setCamera(&cam);
	scene.setBackground(&sky);
	scene.addMesh(&mesh);
	scene.addMesh(&mesh2);
	scene.addLight(&light);
	scene.addLight(&light2);
	scene.addLight(&light3);
	scene.addLight(&light4);

	window.setMouseCursorVisible(false);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	Util::LogManager::notice("Running");
	
	/*Util::InputManager::Keyboard.bind(sf::Keyboard::A, [&mesh](bool b) {if(b) mesh.getMeshBuffer(0)->setDrawMode(Graph::DrawMode::Point);});
	Util::InputManager::Keyboard.bind(sf::Keyboard::Z, [&mesh](bool b) {if(b) mesh.getMeshBuffer(0)->setDrawMode(Graph::DrawMode::Wireframe);});
	Util::InputManager::Keyboard.bind(sf::Keyboard::E, [&mesh](bool b) {if(b) mesh.getMeshBuffer(0)->setDrawMode(Graph::DrawMode::Full);});
	Util::InputManager::Keyboard.bind(sf::Keyboard::Escape, [&window](bool b){if(b) window.close(); });*/
	//Util::InputManager::Mouse.bindMove([&cam](int, int, int x, int y) {cam.rotate(x,y);});
	
	sf::Clock frameTime, clock;
	std::string fpsStr = "0 FPS";
	int fps = 0;

	while(window.isOpen()) {

		sf::Event e;
		while(window.pollEvent(e)) {
			switch(e.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if(e.key.code == sf::Keyboard::Escape)
						window.close();
					break;
				default:
					break;

			}
		}

		float elapsed = clock.getElapsedTime().asMilliseconds() * 0.0005f;


		if(frameTime.getElapsedTime().asSeconds() >= 1) {
			frameTime.restart();
			fpsStr = Util::ToString(fps)+"FPS";
			window.setTitle("ImaKart "+fpsStr);
			
			fps = 0;
		}

		window.getMouse().setPosition(sf::Vector2i(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
		//Util::InputManager::Mouse.setCursorPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

		light3.setPosition(glm::vec3(sin(elapsed*.5f)*9000,cos(elapsed*.5f)*9000,0));
		light.setPosition(glm::vec3(128*16+sin(elapsed*3)*128*3,100*16,128*16+cos(elapsed*3)*128*3));
		light2.setPosition(glm::vec3(128*16,100*16+sin(elapsed*5),128*14+cos(elapsed*5)*128*3));
		light4.setPosition(glm::vec3(128*14+sin(elapsed*10)*128*3,100*16,128*16+cos(elapsed*10)*128*3));
		scene.update(elapsed);
		scene.render();

		// Dessin de la GUI
		window.resetGLStates(); // On reset les matrices openGL avant de dessiner la gui
		//gui.draw();

		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		window.display();
		fps++;
	}
	NzNetwork::Uninitialize();
	return EXIT_SUCCESS;	
}
