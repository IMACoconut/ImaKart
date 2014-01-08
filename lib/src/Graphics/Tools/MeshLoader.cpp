#include <Graphics/Tools/MeshLoader.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <Graphics/Geometry/MeshBuffer.hpp>
#include <fstream>
#include <Utility/LogManager.hpp>

#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace Graph {

Assimp::Importer MeshLoader::importer;
bool MeshLoader::load(const std::string& fname, Mesh& mesh) {
	std::ifstream file(fname.c_str());
	if(file.fail()){
		Util::LogManager::error("Unable to load mesh \""+fname+"\"");
		return false;
	}
	else
		file.close();

	const aiScene* scene = importer.ReadFile(fname, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);

	if(!scene)
		return false;

	for(size_t c = 0; c < scene->mNumMeshes; ++c) {
		aiMesh* m = scene->mMeshes[c];
		VertexBuffer buffer;
		for(uint32_t i=0;i<m->mNumFaces;i++)
		{
			const aiFace& face = m->mFaces[i];

			for(int j=0;j<3;j++)
			{
				glm::vec2 uv;
				if(m->mTextureCoords[0] != nullptr) {
					aiVector3D uvtmp = m->mTextureCoords[0][face.mIndices[j]];
					uv = glm::vec2(uvtmp.x, 1-uvtmp.y);
				} else {
					uv = glm::vec2(0,0);
				}
				 
				aiVector3D normaltmp = m->mNormals[face.mIndices[j]];
				glm::vec3 normal(normaltmp.x, normaltmp.y, normaltmp.z);
				 
				aiVector3D postmp = m->mVertices[face.mIndices[j]];
				glm::vec3 pos(postmp.x, postmp.y, postmp.z);

				buffer.addVertex(Vertex3D(pos, normal, uv, sf::Color(255,255,255)));
			}
			buffer.addTriangle(sf::Vector3i(face.mIndices[0], face.mIndices[1], face.mIndices[2]));
		}
		mesh.loadFromMemory(buffer);
	}

	return true;
}

/*bool MeshLoader::load3Ds(const std::string &name, Mesh* parent)
{
	std::ifstream file(name.c_str(), std::ios::binary);
	if(!file.is_open()) {
			return false;
	}

	unsigned short id;
	unsigned int length;
	file.seekg(0, std::ios_base::end);
	int filelength = file.tellg();
	file.seekg(0, std::ios_base::beg);

	VertexBuffer buff;
	while(!file.eof() && file.tellg() < filelength) {

		file.read((char*)&id, sizeof(unsigned short));
		file.read((char*)&length, sizeof(unsigned int));
		//std::cerr << std::hex << file.tellg() << " id: " << id <<" " << std::dec << id << " length: " << std::hex << length << " " << std::dec << length << std::endl;
		switch(id) {
			case 0x4d4d:
				//std::cerr << "main chunck" << std::endl;
				break;
			case 0x3d3d:
				//std::cerr << "3Ds chunck" << std::endl;
				break;
			case 0x4000:
				unsigned char c;
				unsigned char name[20];
				for(int i = 0; i<20; i++) {
					file.read((char*)&c, sizeof(char));
					name[i] = c;
					if(c == '\0')
						break;
				}
				if(buff.getVerticesCount() > 0)
				{
					parent->loadFromMemory(buff);
					buff.clear();
				}
				//std::cout << buff.getVerticesCount() << std::endl;
				buff.clear();
				//std::cerr << "object block " << std::dec << name << std::endl;

				break;
			case 0x4100:
				//std::cerr << "vertice list" << std::endl;
				break;
			case 0x4110:
				unsigned short nbvert;
				file.read((char*)&nbvert, sizeof(unsigned short));
				//std::cerr << nbvert << " vertices" << std::endl;
				for(int i = 0; i<nbvert; i++) {
					float x,y,z;
					file.read((char*)&x, sizeof(float));
					file.read((char*)&y, sizeof(float));
					file.read((char*)&z, sizeof(float));
					auto vert = glm::vec3(x,y,z);
					buff.addVertex(Vertex3D(vert));
					//std::cerr << "vert: " << x << "," << y << "," << z << std::endl;
				}
				break;
			case 0x4120:
				unsigned short nbpoly;
				file.read((char*)&nbpoly, sizeof(unsigned short));
				//std::cerr << nbpoly << " polys" << std::endl;
				for (int i=0; i<nbpoly; i++)
				{
					unsigned short a,b,c,f;
					file.read((char*)&a, sizeof(unsigned short));
					file.read((char*)&b, sizeof(unsigned short));
					file.read((char*)&c, sizeof(unsigned short));
					file.read((char*)&f, sizeof(unsigned short));
					auto face = sf::Vector3i(a,b,c);
					buff.addTriangle(face);
					//std::cerr << "poly: " << a << "," << b << "," << c << " flag: " << f << std::endl;
				}

			break;
			case 0x4140:
				unsigned short nbcoord;
				file.read((char*)&nbcoord, sizeof(unsigned short));
				//std::cerr << "map coord: " << nbcoord << std::endl;
				for(int i=0; i<nbcoord; i++)
				{
					float u,v;
					file.read((char*)&u, sizeof(float));
					file.read((char*)&v, sizeof(float));
					//std::cerr << "coord: " << u << "," << v << std::endl;
					auto tex = glm::vec2(u,v);
					buff.getVertex(i).uv = tex;
				}
			break;
			default:
				//std::cerr << "jump" << std::endl << std::endl;
				file.seekg(length-6, std::ios_base::cur);
				break;
		}
	}

	if(buff.getVerticesCount() > 0)
		parent->loadFromMemory(buff);

	return true;
}*/

}