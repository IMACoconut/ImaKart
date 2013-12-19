#pragma once

#include <vector>
#include <Game/Kart.hpp>

//namespace Game{

	class Item;

	class VectorItem{
		const int sizeMax;
		int currentItem;
		std::vector<Item*> items;
	public:
		VectorItem();
		bool isEmpty();
		int size();
		void pushItem(Item* items);
		void use(Kart& kartUser);
	};
//}