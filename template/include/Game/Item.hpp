#pragma once

#include <vector>
#include <string>

//namespace Game{

	class Alteration;
	class Kart;

	class Item{
	public:
		std::string name;
		Alteration* effect;	
		Item(std::string name, Alteration* effect);
		virtual ~Item(){}
		virtual void use(Kart& kartUser) = 0;
	};

	class UserItem : public Item{ //cible l'utilisateur
	public:
		UserItem(std::string name, Alteration* effect);
		~UserItem(){}
		void use(Kart& kartUser);
	};

	class NextItem : public Item{	//cible la personne devant l'utilisateur
	public:
		NextItem(std::string name, Alteration* effect);
		~NextItem(){}
		void use(Kart& kartUser);
	};

	class FirstItem : public Item{	//cible le premier de la course
	public:
		FirstItem(std::string name, Alteration* effect);
		~FirstItem(){}
		void use(Kart& kartUser);
	};

	class AllNextItem : public Item{ //cible toute les personnes devant l'utilisateur
	public:
		AllNextItem(std::string name, Alteration* effect);
		~AllNextItem(){}
		void use(Kart& kartUser);
	};

	class AllItem : public Item{ //cible tout le monde
	public:
		AllItem(std::string name, Alteration* effect);
		~AllItem(){}
		void use(Kart& kartUser);
	};

//}