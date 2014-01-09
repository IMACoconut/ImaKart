#include <Physics/Collidable.hpp>
#include <Graphics/Tools/Node.hpp>




namespace Phys {

	Collidable::Collidable(Graph::Node* n) :
	collidableNode(n), m_shape(nullptr) {}
	

	void Collidable::Init(btCollisionShape* shape) {
		m_shape = shape;

	}
	


}