#pragma once

#include <string>
#include <Graphics/Mesh.hpp>

namespace Graph {
	class Skydome : public Mesh {
		public:
			Skydome();
			bool loadSkyMaterial(const std::string& mat);
			bool loadGlowMaterial(const std::string& mat);
	
	};
}