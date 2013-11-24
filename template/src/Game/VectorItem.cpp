#include <Game/VectorItem.hpp>
#include <Game/Item.hpp>
#include <Game/alteration.hpp>
#include <iostream>

#define NB_ITEM 3

namespace Game{

	VectorItem::VectorItem() : sizeMax(NB_ITEM), currentItem(0){}

	bool VectorItem::isEmpty(){
		return items.empty();
	}

	int VectorItem::size(){
		return items.size();
	}

	void VectorItem::pushItem(Item* item){
		items.push_back(item);
	}

	void VectorItem::use(Kart& kartUser){
		(*(items.begin()+currentItem))->use(kartUser);
	}
}