#include <SFML/System/Vector3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <Game/Kart.hpp>
#include <Game/Alteration.hpp>
#include <iostream>
#include <string>

Alteration::Alteration(int time, std::string nameAlteration)
		 : duration(time), currentTime(0), name(nameAlteration){}

FactorAlteration::FactorAlteration(std::string nameAlteration, std::vector<std::string> affectedVariable, std::vector<float> factor, int time)
		 : Alteration(time, nameAlteration){

	add("affectedVariable", new Component<std::vector<std::string>>(1, affectedVariable));
	add("modif", new Component<std::vector<float>>(1, factor));
}

void FactorAlteration::apply(Kart& kart){

		if(currentTime == 0){
std::cout<<"currentTime = 0"<<std::endl;
			std::vector<std::string> affectedVariable = get<std::vector<std::string>>("affectedVariable");
			std::vector<float> modif = get<std::vector<float>>("modif");
			for (size_t i = 0; i < affectedVariable.size(); ++i)
			{
std::cout<<"on applique une modif"<<std::endl;
std::cout<<affectedVariable[i]<<std::endl;
				float tmp = kart.get<float>(affectedVariable[i]);
std::cout<<tmp<<std::endl;
				tmp *= modif[i];
std::cout<<modif[i]<<std::endl;
				kart.set<float>(affectedVariable[i], tmp);
			}
		}

		if(currentTime == duration){
std::cout<<"currentTime = duration"<<std::endl;
			std::vector<std::string> affectedVariable = get<std::vector<std::string>>("affectedVariable");
			std::vector<float> modif = get<std::vector<float>>("modif");
			for (size_t i = 0; i < affectedVariable.size(); ++i)
			{
std::cout<<"on annule une modif"<<std::endl;
				float tmp = kart.get<float>(affectedVariable[i]);
				tmp /= modif[i];
				kart.set<float>(affectedVariable[i], tmp);
			}
		}
		++currentTime;
	}

	StatutAlteration::StatutAlteration(std::string nameAlteration, std::vector<std::string> affectedVariable, int time)
			 : Alteration(time, nameAlteration){

		add("affectedVariable", new Component<std::vector<std::string>>(1, affectedVariable));
	}

	void StatutAlteration::apply(Kart& kart){

		if(currentTime == 0){
			std::vector<std::string> affectedVariable = get<std::vector<std::string>>("affectedVariable");
			for (size_t i = 0; i < affectedVariable.size(); ++i)
			{
				kart.set<int>(affectedVariable[i], 1);
			}
		}

		if(currentTime == duration){
			std::vector<std::string> affectedVariable = get<std::vector<std::string>>("affectedVariable");
			for (size_t i = 0; i < affectedVariable.size(); ++i)
			{
				kart.set<int>(affectedVariable[i], 0);
			}
		}
		++currentTime;
	}