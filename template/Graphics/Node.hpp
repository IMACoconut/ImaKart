#pragma once

#include <Core/Vector3.hpp>

namespace {
	class Node {
	public:
		Node();
		Node(const Node& other) = delete;
		virtual ~Node();

		void SetPosition(const core::Vector3d& position);
		core::Vector3d GetPosition() const;

		void SetRotation(const core::Vector3d& rotation);
		core::Vector3d GetRotation() const;

		void SetScale(const core::Vector3d& scale);
		core::Vector3d GetScale() const;

	protected:
		core::Vector3d position, rotation, scale;
	};
}