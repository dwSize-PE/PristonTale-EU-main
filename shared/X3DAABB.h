#pragma once

namespace X3D
{

class Vector3;

class AABB
{
public:
	Vector3 vMin, vMax;

	AABB( Vector3 Min, Vector3 Max ) : vMin(Min), vMax(Max) {};

};

};