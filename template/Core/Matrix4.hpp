#pragma once

namespace Core {
	template <typename T>
	class Matrix4 {
	public:
		Matrix4();

		void makeIdentity();

		static Matrix4 identity();
		static Matrix4 translate(T x, T y, T z);
		static Matrix4 scale(T x, T y, T z);

		T* data();

	protected:
		T val[16];
	};

	typedef Matrix4<float> Matrix4f;
}

#include <Core/Matrix4.inl>