#pragma once

#include <vector>

namespace Core {
	template<typename T, U>
	class System : public Updatable {
	public:
		void update(float elapsed) {
			for(auto t: registered)
				for(auto u: registered)
					for(auto v: actions)
						v(t,u);
		}

		void pushAction(U action) {
			action.push_back(action);
		}

		void pushComponent(T component) {
			registered.push_back(component);
		}

	private:
		std::vector<T> registered;
		std::vector<U> actions;
	};
}