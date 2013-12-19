#pragma once

namespace ia {
	class Behavior {
	public:
		void update(float elapsed);
		
	protected:
		virtual void onUpdate(float elapsed) = 0;
	};
}