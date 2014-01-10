#include <Game/Map.hpp>
#include <Game/Logic/GameLogic.hpp>
#include <Game/Logic/Checkpoint.hpp>
#include <Game/Logic/ItemSpawn.hpp>
#include <Game/IA/PlayerBehavior.hpp>
#include <Game/IA/IABehavior.hpp>
#include <tinyxml2/tinyxml2.h>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>
#include <Utility/FilePath.hpp>
#include <vector>
#include <iostream>

Map::~Map() {
	clear();
}

void Map::clear() {
	while(m_checkpoints.size()) {
		delete m_checkpoints.back();
		m_checkpoints.pop_back();
	}
	for(auto* i: m_itemSpawns)
		delete i;
	m_itemSpawns.clear();
	m_karts.clear();

}
bool Map::loadFromFile(const std::string& file){
	clear();
	/*int numberOfKarts = 1;
	int numberOfPlayer = 1;
*/
	Util::FilePath path(file);
	tinyxml2::XMLDocument doc;
	int res = doc.LoadFile(file.c_str());
	if(res != 0){
		Util::LogManager::error("Impossible de charger le fichier "+file);
		return false;
	}
	tinyxml2::XMLElement* root = doc.FirstChildElement("map");
	if(root == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <map> manquante");
		return false;
	}

	tinyxml2::XMLElement* info = root->FirstChildElement("info");
	if(info == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <info> manquante");
		return false;
	}

	std::string name = Util::getStringFromXML(info, "name");
	add("name", new Component<std::string>(1, name));

	float scale = Util::getFloatFromXML(info, "scale");
	add("scale", new Component<float>(1, scale));

	std::string heightmap = Util::getStringFromXML(info, "heightmap");
	add("heightmap", new Component<std::string>(1, path.getDirectory()+heightmap));

	std::string detailmap = Util::getStringFromXML(info, "detailmap");
	add("detailmap", new Component<std::string>(1, path.getDirectory()+detailmap));

	tinyxml2::XMLElement* startgrid = root->FirstChildElement("startgrid");
	if(startgrid == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <startgrid> manquante");
		return false;
	}	
	tinyxml2::XMLElement* startpos = startgrid->FirstChildElement("pos");
	glm::vec3 start;
	start.x = Util::getFloatFromXML(startpos, "x");
	start.z = Util::getFloatFromXML(startpos, "y");

	float width = Util::getFloatFromXML(startgrid, "width");

	tinyxml2::XMLElement* startdir = startgrid->FirstChildElement("dir");
	glm::vec3 direction;
	direction.x = Util::getFloatFromXML(startdir, "x");
	direction.z = Util::getFloatFromXML(startdir, "y");

	grid = Startgrid(start*scale, direction, width);


	tinyxml2::XMLElement* checkpoints = root->FirstChildElement("checkpoints");
	if(checkpoints == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <checkpoints> manquante");
		return false;
	}	

	tinyxml2::XMLNode* checkpoint = checkpoints->FirstChildElement("checkpoint");
	std::vector<glm::vec2> check;
	while(checkpoint != nullptr){
		glm::vec2 c;
		c.x = Util::getFloatFromXML((tinyxml2::XMLElement*)checkpoint,"x");
		c.y = Util::getFloatFromXML((tinyxml2::XMLElement*)checkpoint,"y");
		check.push_back(c);
		checkpoint = checkpoint->NextSibling();
	}
	add("check", new Component<std::vector<glm::vec2>>(1, check));
	
	/*for (int i = 0; i < (int)karts.size(); ++i)
	{
		addKart(karts[i]);
	}*/
	
	/*tinyxml2::XMLElement* lights = root->FirstChildElement("lights");
	if(lights == nullptr){
		Util::LogManager::error("Lumière invalide : balise <lights> manquante");
		return false;
	}
	add("lights", new Component<std::string>(1, std::string(lights->GetText())));

	try{
		tinyxml2::XMLElement* spotlight = lights->FirstChildElement("spotlight");
		if(spotlight){	
			glm::vec3 pos = Util::getVec3FromXML(spotlight, "position");
			add("position", new Component<glm::vec3>(1, pos));

			float intensity = Util::getFloatFromXML(spotlight, "intensity");
			add("intensity", new Component<float>(1, intensity));

			float radius = Util::getFloatFromXML(spotlight, "radius");
			add("radius", new Component<float>(1, radius));

			glm::vec3 dir = Util::getVec3FromXML(spotlight, "direction");
			add("direction", new Component<glm::vec3>(1, dir));

			sf::Color col = Util::getColorFromXML(spotlight, "color");
			add("color", new Component<sf::Color>(1, col));
		}
	}catch(int){
		Util::LogManager::error("Impossible de charger la spotlight");
	}

	try{
		tinyxml2::XMLElement* directionallight = lights->FirstChildElement("directionallight");
		if(directionallight){	
			glm::vec3 pos = Util::getVec3FromXML(directionallight, "position");
			add("position", new Component<glm::vec3>(1, pos));

			float intensity = Util::getFloatFromXML(directionallight, "intensity");
			add("intensity", new Component<float>(1, intensity));

			sf::Color col = Util::getColorFromXML(directionallight, "color");
			add("color", new Component<sf::Color>(1, col));
		}
	}catch(int){
		Util::LogManager::error("Impossible de charger la lumière directionnelle");
	}


	try{
		tinyxml2::XMLElement* pointlight = lights->FirstChildElement("pointlight");
		if(pointlight){	
			glm::vec3 pos = Util::getVec3FromXML(pointlight, "position");
			add("position", new Component<glm::vec3>(1, pos));

			float intensity = Util::getFloatFromXML(pointlight, "intensity");
			add("intensity", new Component<float>(1, intensity));

			float radius = Util::getFloatFromXML(pointlight, "radius");
			add("radius", new Component<float>(1, radius));

			sf::Color col = Util::getColorFromXML(pointlight, "color");
			add("color", new Component<sf::Color>(1, col));
		}
	}catch(int){
		Util::LogManager::error("Impossible de charger la pointlight");
	}*/



	//uint32_t WINDOW_WIDTH = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("width")->GetText()));
	//uint32_t WINDOW_HEIGHT = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("height")->GetText()));
	
	Util::LogManager::notice("Map chargée");
	Util::LogManager::notice("Nom : "+get<std::string>("name"));
	Util::LogManager::notice("Scale : "+Util::ToString(get<float>("scale")));
	Util::LogManager::notice("Heightmap : "+get<std::string>("heightmap"));
	Util::LogManager::notice("Detailmap : "+get<std::string>("detailmap"));
	return true;
}

bool Map::loadIntoScene(Graph::Scene& scene){
	if(!this->mesh.loadFromFile(this->get<std::string>("heightmap"))) {
		Util::LogManager::notice("Erreur au chargement de la heightmap");
		return false;
		//std::cerr << "Error" << std::endl;
	}
	if(!this->hmtex.loadFromFile(get<std::string>("detailmap"))) {
		Util::LogManager::notice("Erreur au chargement des textures");
		return false;
		//std::cerr << "Error while loading material" << std::endl;
	}


	this->mesh.setMaterial(0, &this->hmtex);
	float sc = get<float>("scale");
	this->mesh.setScale(glm::vec3(sc,sc/2,sc));
	scene.addMesh(&mesh);
	//mesh.setLightening(false);

	auto c = this->get<std::vector<glm::vec2>>("check");
	for(size_t i = 0; i < c.size(); ++i){
		Checkpoint* tmp = new Checkpoint(*this, i);
		if(!tmp->loadFromFile("../resources/models/cube.3DS")){
			Util::LogManager::notice("Erreur au chargement des checkpoints");
			return false;
		}
		glm::vec3 pos(c[i].x*sc, 0, c[i].y*sc);
		pos.y = mesh.realHeight(pos.x, pos.z);
		tmp->setPosition(pos);
		tmp->setScale(glm::vec3(50,50,50));
		//scene.addMesh(tmp);
		m_checkpoints.push_back(tmp);
	}
	

	for(auto itr: m_karts){
		Kart* tmp = std::get<0>(itr);

		glm::vec3 position = m_checkpoints[0]->getPosition();
		tmp->setPosition(glm::vec3(position.x, position.y, position.z), 90.f);

		tmp->updateOrientation(this->mesh, 1);
		tmp->loadIntoScene(scene);

		grid.placeKart(*tmp);
		
		glm::vec3 pos = tmp->get<glm::vec3>("position");
		//pos.x *= sc; pos.z *= sc;
		pos.y = mesh.realHeight(pos.x, pos.z);//pos.y = mesh.offsetHeight(c[0].x,c[0].y)*get<float>("scale")/2;
		tmp->setPosition(pos, 0);
		//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl
	}

	return true;
}

void Map::draw(){
	//this->mesh.render();
//	this->drawCheckpoint();
}

void Map::drawCheckpoint(){
	
}

void Map::update(float e) {
	for(auto c: m_checkpoints)
		c->update(e);
	for(auto i: m_itemSpawns)
		i->update(e);

	for(auto k : m_karts) {
		Kart* kart = std::get<0>(k);	
		kart->update(mesh, e);
		for(auto c: m_checkpoints)
			c->isReached(*kart);
		for(auto i: m_itemSpawns)
			i->isReached(*kart);
	}
}

void Map::addKart(Kart* k) {
	m_karts.push_back(std::make_tuple(k, 0, 3, false));
	/*Kart* k = new Kart(m_karts.size());
	switch(type) {
		case KartType_1:
			// Changer maniabilité, vitesse, etc...
			break;
		case KartType_2:
			break;
		case KartType_3:
			break;
		default:
			break;
	}*/
	//
	//m_karts.push_back(std::make_tuple(k, Util::Clock(), 3, false));
}

std::vector<KartInfos> Map::getResults() {
	sortKartByPosition();
	return m_karts;
}

void Map::hasFinishedLoop(Kart& k) {
	int id = k.get<int>("id");
 	auto& infos = m_karts[id];
 	int& loops = std::get<2>(infos);
 	if(loops == 1) {
 		bool& finished = std::get<3>(infos);
 		finished = true;

 		auto& clock = GameLogic::getInstance().getClock();
 		std::get<1>(infos) = clock.GetMilliseconds();
 		//if(k.isPlayer()) {
 			GameLogic::getInstance().stopRace();
 		//}
 	} else
 		--loops;

 	auto& clock = GameLogic::getInstance().getClock();
 	std::cout << clock.GetMinutes()<< " : "<<clock.GetSeconds() % 60<<std::endl;
 	
}

Graph::Heightmap* Map::getHeightmap() {
	return &mesh;
}

struct SortKart {

	Map* m;

	SortKart(Map* map) : m(map){}

	bool operator()(const KartInfos& k1, const KartInfos& k2){

		int loop1 = std::get<2>(k1), loop2 = std::get<2>(k2);
		int checkpoint1 = (std::get<0>(k1))->get<int>("checkpoint");
		int checkpoint2 = (std::get<0>(k2))->get<int>("checkpoint");
		glm::vec3 position1 = (std::get<0>(k1))->get<glm::vec3>("position");
		glm::vec3 position2 = (std::get<0>(k2))->get<glm::vec3>("position");

		if(loop1 < loop2)
			return false;
		else if(loop2 < loop1)
			return true;

		else if(checkpoint1 < checkpoint2)
			return false;
		else if(checkpoint1 > checkpoint2)
			return true;
		else if (glm::length(position1 - m->getCheckpoints()[checkpoint1]->getPosition()) < glm::length(position2 - m->getCheckpoints()[checkpoint2]->getPosition()))
			return false;
		
		return true;

	}
};
void Map::sortKartByPosition(){
	SortKart sort(this);
	std::sort(m_karts.begin(), m_karts.end(), sort);
}