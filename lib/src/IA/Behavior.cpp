#include <IA/Behavior.hpp>

namespace ia {
	
void Behavior::update(float elapsed) {
	onUpdate(elapsed);
}

}