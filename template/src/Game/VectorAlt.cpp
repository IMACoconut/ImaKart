#include <Game/VectorAlt.hpp>
#include <Game/alteration.hpp>
#include <iostream>

	bool VectorAlt::isEmpty(){
		return alterations.empty();
	}

	int VectorAlt::size(){
		return alterations.size();
	}

	void VectorAlt::pushAlteration(Alteration* alteration){
		alterations.push_back(alteration);
	}

	void VectorAlt::apply(Kart& kart){
		int i = 0;
		std::vector<int> dead;
		for(std::vector<Alteration*>::iterator it = alterations.begin(); it != alterations.end();){
			(*it)->apply(kart);
			if((*it)->currentTime > (*it)->duration){
				it = alterations.erase(it);
			} else
				++it;
			++i;
		}
	}