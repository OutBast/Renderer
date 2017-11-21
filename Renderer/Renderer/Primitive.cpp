#include "stdafx.h"
#include "Primitive.h"

Primitive::Primitive() : center(float3::zero), material(new Material()), distanceToCamera(0.0f)
{ }

Primitive::Primitive(const float3 center, Material *material) : center(center), material(material), distanceToCamera(0.0f)
{ }

Primitive::Primitive(Material *material) : center(float3::zero), material(material), distanceToCamera(0.0f)
{ }

Primitive::Primitive(const float3 center) : center(center), material(new Material()), distanceToCamera(0.0f)
{ }

Primitive::~Primitive()
{ }

void Primitive::CalculateDistanceToCamera(float3& camPos)
{
	distanceToCamera = float3::Distance(center, camPos);
}

std::ostream & operator<<(std::ostream &os, const Primitive &value)
{
	os << "center: " << value.center << ", distance: " << value.distanceToCamera /*<<", color ambient material: " << value.material->ColorAmbient()*/;

	return os;
}
