#pragma once

namespace core {

	template <typename T>
	class Vector3 {
	public:
		Vector3() = default;
		Vector3(T x, T y, T z);
		Vector3(const Vector3& other) = default;

		Vector3& operator=(const Vector3& other) = default;

		T x,y,z;
	};

	typedef Vector3<double> Vector3d;
	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3ui;
}

#include <Core/Vector3.inl>