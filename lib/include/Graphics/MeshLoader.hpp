#pragma once

#include <string>

namespace Graph {

class Mesh;

class MeshLoader {
public:
	static void load(const std::string& file, Mesh* mesh);
	static bool load3Ds(const std::string& file, Mesh* mesh);
};

}