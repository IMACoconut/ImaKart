#include <Game/map.hpp>
#include <tinyxml2/tinyxml2.h>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>
#include <vector>
#include <iostream>

Map::~Map() {
	while(meshCheckpoint.size()) {
		delete meshCheckpoint.back();
		meshCheckpoint.pop_back();
	}
}
bool Map::loadFromFile(const std::string& file){
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

	tinyxml2::XMLElement* name = info->FirstChildElement("name");
	if(name == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <name> manquante");
		return false;
	}
	add("name", new Component<std::string>(1, std::string(name->GetText())));

	tinyxml2::XMLElement* scale = info->FirstChildElement("scale");
	if(scale == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <scale> manquante");
		return false;
	}
	add("scale", new Component<int>(1, Util::FromString<int>(std::string(scale->GetText()))));

	tinyxml2::XMLElement* heightmap = info->FirstChildElement("heightmap");
	if(heightmap == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <heightmap> manquante");
		return false;
	}
	add("heightmap", new Component<std::string>(1, std::string(heightmap->GetText())));

	tinyxml2::XMLElement* detailmap = info->FirstChildElement("detailmap");
	if(detailmap == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <detailmap> manquante");
		return false;
	}
	add("detailmap", new Component<std::string>(1, std::string(detailmap->GetText())));

	tinyxml2::XMLElement* checkpoints = root->FirstChildElement("checkpoints");
	if(checkpoints == nullptr){
		Util::LogManager::error("Fichier map invalide : balise <checkpoints> manquante");
		return false;
	}	

	tinyxml2::XMLNode* checkpoint = checkpoints->FirstChildElement("checkpoint");
	std::vector<Checkpoint> check;
	while(checkpoint != nullptr){
		Checkpoint c;
		c.x = Util::FromString<int>(std::string(checkpoint->FirstChildElement("x")->GetText()));
		c.y = Util::FromString<int>(std::string(checkpoint->FirstChildElement("y")->GetText()));
		check.push_back(c);
		checkpoint = checkpoint->NextSibling();
	}
	add("check", new Component<std::vector<Checkpoint>>(1, std::vector<Checkpoint>(check)));

	//uint32_t WINDOW_WIDTH = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("width")->GetText()));
	//uint32_t WINDOW_HEIGHT = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("height")->GetText()));
	
	Util::LogManager::notice("Map chargée");
	Util::LogManager::notice("Nom : "+get<std::string>("name"));
	Util::LogManager::notice("Scale : "+Util::ToString(get<int>("scale")));
	Util::LogManager::notice("Heightmap : "+get<std::string>("heightmap"));
	Util::LogManager::notice("Detailmap : "+get<std::string>("detailmap"));
	return true;
}

bool Map::loadIntoScene(Graph::Shader* s, Graph::Scene& scene){
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
	this->mesh.setScale(glm::vec3(16,16,16));
	this->mesh.setShader(s);
	scene.addMesh(&mesh);
	

	auto c = this->get<std::vector<Checkpoint>>("check");
	for(size_t i = 0; i < c.size(); ++i){
		Graph::Mesh* tmp = new Graph::Mesh;
		if(!tmp->loadFromFile("../resources/models/cube.3DS")){
			Util::LogManager::notice("Erreur au chargement des checkpoints");
			return false;
		}

		tmp->setPosition(glm::vec3(c[i].x*16, this->mesh.offsetHeight(c[i].x,c[i].y)*16, c[i].y*16));
		tmp->setScale(glm::vec3(50,50,50));
		scene.addMesh(tmp);
		meshCheckpoint.push_back(tmp);
	}
	
	return true;
}

void Map::draw(){
	//this->mesh.render();
//	this->drawCheckpoint();
}

void Map::drawCheckpoint(){
	
}