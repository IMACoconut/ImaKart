#pragma once 

#include <glm/glm.hpp>

class Startgrid{
public:
	Startgrid() :
		gridwidth(0), lines(0)
	{}
	
	Startgrid(const glm::vec3& position, const glm::vec3& dir, float width) : 
		position(position), currPos(position), dir(glm::normalize(dir)),
		gridwidth(width), lines(0)
	{}

	void placeKart(Kart& kart){
		glm::vec3 kartSize = kart.getMesh()->getBoundingBox().getSize();

		currPos += dir*kartSize.x;
		if(glm::length(currPos-position) >= gridwidth){
			glm::vec3 bot(glm::cross(glm::vec3(0,1,0), dir));
			currPos = position+bot*kartSize.z*(1.5f*++lines);
		}
		kart.setPosition(currPos+kartSize*0.5f,0);
		currPos += dir*kartSize.x;
	}

private:
	glm::vec3 position, currPos;
	glm::vec3 dir;
	float gridwidth;
	int lines;


};