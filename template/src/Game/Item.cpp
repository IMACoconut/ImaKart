#include <Game/Item.hpp>
#include <Game/Alteration.hpp>

//namespace Game{

	Item::Item(std::string name, Alteration* effect) : name(name), effect(effect){}

	UserItem::UserItem(std::string name, Alteration* effect) : Item(name, effect){}

	void UserItem::use(Kart& kartUser){
		//	kartUser.addAlteration(effect);
	}

//}