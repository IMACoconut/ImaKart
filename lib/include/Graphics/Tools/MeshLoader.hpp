#pragma once

#include <string>

#include <assimp/Importer.hpp>

namespace Graph {

class Mesh;

class MeshLoader {
public:
	static bool load(const std::string& file, Mesh& mesh);
	static bool load3Ds(const std::string& file, Mesh& mesh);

protected:
	static Assimp::Importer importer;
};

}