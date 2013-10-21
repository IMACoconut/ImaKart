#pragma once

#include <Graphics/Node.hpp>
#include <Graphics/VBO.hpp>

namespace {
	class Mesh : public Node {
		public:
			Mesh();
			virtual ~Mesh();

			bool LoadFromFile(const std::string& name);


		protected:
			VBO* m_vbo;
	};
}