#pragma once

#include <vector>
#include <Game/Kart.hpp>

	class Alteration;

	class VectorAlt{
		std::vector<Alteration*> alterations;
	public:
		VectorAlt(){}
		bool isEmpty();
		int size();
		void pushAlteration(Alteration* alteration);
		void apply(Kart& kart);
	};