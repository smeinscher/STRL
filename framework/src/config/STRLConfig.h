//
// Created by SterlingMeinscher on 2/17/2024.
//

#ifndef STRLCONFIG_H
#define STRLCONFIG_H

namespace strl
{

// TODO: define this elsewhere
#define STRL_RENDER_API_OPENGL

const int STRL_IGNORE = -1;

#define DEFINE_KEY(name, code) STRL_KEY_##name = code
enum STRLKey
{
	DEFINE_KEY(IGNORE, STRL_IGNORE),
	DEFINE_KEY(UNKNOWN, 0),

	DEFINE_KEY(LEFT_CONTROL, 17),
	DEFINE_KEY(RIGHT_CONTROL, 18),
	DEFINE_KEY(LEFT_SHIFT, 19),
	DEFINE_KEY(RIGHT_SHIFT, 20),

	DEFINE_KEY(TAB, 21),

	DEFINE_KEY(ESCAPE, 27),

	DEFINE_KEY(A, 65),
	DEFINE_KEY(B, 66),
	DEFINE_KEY(C, 67),
	DEFINE_KEY(D, 68),
	DEFINE_KEY(E, 69),
	DEFINE_KEY(F, 70),
	DEFINE_KEY(G, 71),
	DEFINE_KEY(H, 72),
	DEFINE_KEY(I, 73),
	DEFINE_KEY(J, 74),
	DEFINE_KEY(K, 75),
	DEFINE_KEY(L, 76),
	DEFINE_KEY(M, 77),
	DEFINE_KEY(N, 78),
	DEFINE_KEY(O, 79),
	DEFINE_KEY(P, 80),
	DEFINE_KEY(Q, 81),
	DEFINE_KEY(R, 82),
	DEFINE_KEY(S, 83),
	DEFINE_KEY(T, 84),
	DEFINE_KEY(U, 85),
	DEFINE_KEY(V, 86),
	DEFINE_KEY(W, 87),
	DEFINE_KEY(X, 88),
	DEFINE_KEY(Y, 89),
	DEFINE_KEY(Z, 90),

	DEFINE_KEY(MAX, 192)
};

enum STRLMouseButton
{
	STRL_MOUSE_BUTTON_0 = 0,
	STRL_MOUSE_BUTTON_1 = 1,
	STRL_MOUSE_BUTTON_2 = 2,
	STRL_MOUSE_BUTTON_3 = 3,
	STRL_MOUSE_BUTTON_4 = 4,
	STRL_MOUSE_BUTTON_5 = 5,
	STRL_MOUSE_BUTTON_6 = 6,
	STRL_MOUSE_BUTTON_7 = 7,
	STRL_MOUSE_BUTTON_LEFT = 0,
	STRL_MOUSE_BUTTON_RIGHT = 1,
	STRL_MOUSE_BUTTON_MIDDLE = 2
};

enum STRLKeyMods
{
	STRL_KEY_MOD_SHIFT = 0x0001,
	STRL_KEY_MOD_CONTROL = 0x0002,
	STRL_KEY_MOD_ALT = 0x0004,
	STRL_KEY_MOD_SUPER = 0x0008,
	STRL_KEY_MOD_CAPS_LOCK = 0x0010,
	STRL_KEY_MOD_NUM_LOCK = 0x0020
};

// Defines a plane xy, xz, or yz
// Can be used for things like movement (move along X and Y axis for example)
enum class STRLPlane
{
	XY,
	XZ,
	YZ
};

// enum class for possible types of vertex attributes (used in vertex shader)
enum class VertexDataType
{
	POSITION,
	UV,
	COLOR,
	LAST_VERTEX_DATA_TYPE
};

// useful for parameter packing what vertex data types we need, enforces the VertexDataType type
template <typename T>
concept VDType = std::is_same<T, VertexDataType>::value;

const float PHYSICS_SCALE = 0.1f;

} // strl

#endif //STRLCONFIG_H
