#pragma once 

class Startgrid{
public:
	Startgrid();

	void draw();
	/*(position.x, position.y)(position.x+size.w, position.y + size.w)(position.x+size.w-size.h, position.y+size.w-size.h)(position.x-size.h, position.y-size.h)*/

	void placeKart(Kart& kart){
		kart.setPosition();
	}

private:
	glm::vec2 position;
	glm::vec2 size;
	std::vector<Kart> karts;
	int sizeKart;

};