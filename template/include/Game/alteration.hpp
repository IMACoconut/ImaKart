#pragma once

#include <string>
#include <Game/Entity.hpp>
#include <Game/kart.hpp>
#include <vector>


	class Alteration : public Entity{

	public:

		int duration;
		int currentTime;
		std::string name;

		Alteration(int time, std::string nameAlteration);
		virtual ~Alteration(){}
		virtual void apply(Kart& kart) = 0;
	};

	class FactorAlteration : public Alteration{
	public:
		int modif;

		FactorAlteration(std::string nameAlteration, std::vector<std::string> affectedVariable, std::vector<float> factor, int time);
		~FactorAlteration(){}
		void apply(Kart& kart);
	};

	class StatutAlteration : public Alteration{
	public:
		StatutAlteration(std::string nameAlteration, std::vector<std::string> affectedVariable, int time);
		~StatutAlteration(){}
		void apply(Kart& kart);
	};