#include <cstring>

namespace Core {

	template <typename T>
	Matrix4<T>::Matrix4() {
		makeIdentity();
	}

	template <typename T>
	void Matrix4<T>::makeIdentity() {
		std::memset(val, 0, 16*sizeof(T));
		val[0] = 1; val[5] = 1; val[10] = 1; val[15] = 1;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::identity() {
		Matrix4<T> id;
		id.makeIdentity();
		return id;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::translate(T x, T y, T z) {
		Matrix4<T> id;
		id.makeIdentity();
		id.val[3] = x; id.val[7] = y; id.val[11] = z;
		return id;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::scale(T x, T y, T z) {
		Matrix4<T> id;
		id.makeIdentity();
		id.val[0] = x; id.val[5] = y; id.val[10] = z;
		return id;
	}

	template <typename T>
	T* Matrix4<T>::data() {
		return val;
	}
}