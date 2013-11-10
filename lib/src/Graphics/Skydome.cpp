#include <Graphics/Skydome.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Vertex.hpp>

namespace Graph {
	Skydome::Skydome() {
		VertexBuffer buff;
		int nb_segments=64;
		int i,j;
	
		const float R = 1./(float)(nb_segments-1);
		
		for(i = 0; i<nb_segments; i++) {
			for(j = 0; j<nb_segments; j++) {
				float x = cos(2*M_PI*j*R)*sin(M_PI*i*R);
				float y = sin(-M_PI_2+M_PI*i*R);
				float z = sin(2*M_PI*j*R)*sin(M_PI*i*R);
				buff.addVertex(Vertex3D(glm::vec3(x,y,z), glm::vec3(-x,-y,-z), glm::vec2(0,0), sf::Color(255,255,255,255)));

			}
		}

		for(i=0; i<nb_segments; i++){
			for(j=0; j<nb_segments; j++){
				//buff.getVertex(i*nb_segments+j).normal = glm::normalize(buff.getVertex(i*nb_segments+j).normal);
				buff.addTriangle(sf::Vector3i((i*nb_segments+j), (i*nb_segments+j+1), ((i+1)*nb_segments+j)));
				buff.addTriangle(sf::Vector3i((i*nb_segments+j+1), ((i+1)*nb_segments+j+1), ((i+1)*nb_segments+j)));
			}
		}

		loadFromMemory(buff);
	}
}