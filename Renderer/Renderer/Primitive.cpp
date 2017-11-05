#include "stdafx.h"
#include "Primitive.h"

Primitive::Primitive() : center(float3::zero), material(new Material()), distanceToCamera(0.0f), useVerticesUVW(true)
{ }

Primitive::Primitive(const float3 center, Material *material, const bool &useVerticesUVW) : center(center), material(material), distanceToCamera(0.0f), useVerticesUVW(useVerticesUVW)
{ }

Primitive::Primitive(Material *material, const bool &useVerticesUVW) : center(float3::zero), material(material), distanceToCamera(0.0f), useVerticesUVW(useVerticesUVW)
{ }

Primitive::Primitive(const float3 center, const bool &useVerticesUVW) : center(center), material(new Material()), distanceToCamera(0.0f), useVerticesUVW(useVerticesUVW)
{ }

Primitive::~Primitive()
{ }

float Primitive::CalculateLocalIntersectionPoint(const float & point, const float & scale)
{
	float returnValue = fmodf(point + scale, 2.0F * scale) / scale;

	return (returnValue < 0.0F) ? returnValue + 1 : returnValue - 1;
}

void Primitive::CalculateDistanceToCamera(float3& camPos)
{
	distanceToCamera = float3::Distance(center, camPos);
}

std::ostream & operator<<(std::ostream &os, const Primitive &value)
{
	os << "center: " << value.center << ", distance: " << value.distanceToCamera /*<<", color ambient material: " << value.material->ColorAmbient()*/;

	return os;
}
