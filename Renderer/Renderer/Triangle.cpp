#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle() :
    vertices({ float3::zero, float3::zero, float3::zero }),
    barycentric({ 0.0f, 0.0f, 0.0f }),
    normal(float3::up)
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}


Triangle::Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const float3 &normal, Material &material) :
    Primitive((v1 + v2 + v3) * 0.333f, &material, true),
    vertices({ v1, v2, v3 }),
    barycentric({ 0.0f, 0.0f, 0.0f }),
    normal(normal)
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}

Triangle::Triangle(const Triangle &triangle) :
    Primitive((triangle.Vertices()[0] + triangle.Vertices()[1] + triangle.Vertices()[2]) * 0.333f, triangle.material, true),
    vertices({ triangle.Vertices()[0], triangle.Vertices()[1], triangle.Vertices()[2] }),
    barycentric({ triangle.barycentric[0], triangle.barycentric[1], triangle.barycentric[2] }),
    normal(triangle.Normal()),
    verticesUVW({ triangle.VerticesUVW()[0], triangle.VerticesUVW()[1], triangle.VerticesUVW()[2] })
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}

Triangle::Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const float3 &normal, Material &material, const float3 &v1T, const float3 &v2T, const float3 &v3T) :
    Primitive((v1 + v2 + v3) * 0.333f, &material, true),
    vertices({ v1, v2, v3 }),
    barycentric({ 0.0f, 0.0f, 0.0f }),
    normal(normal),
    verticesUVW({ v1T, v2T, v3T })
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}

Triangle::~Triangle()
{ }

void Triangle::CalculateSurfaceArea()
{
    float3 firstVec = vertices[0] - vertices[1];
    float3 secondVec = vertices[2] - vertices[1];

    surfaceArea = 0.5f * firstVec.Magnitude() * secondVec.Magnitude() * sin(DegreesToRadians(float3::Angle(firstVec, secondVec)));
}

void Triangle::CheckValueForInf(float& value)
{
    if (isinf(value))
    {
        value = 0.0F;
    }
}

void Triangle::CalculateMaxDistances()
{
    maxXDistance = fmaxf(fabsf(vertices[0].X() - center.X()), fmaxf(fabsf(vertices[1].X() - center.X()), fabsf(vertices[2].X() - center.X())));
    maxYDistance = fmaxf(fabsf(vertices[0].Y() - center.Y()), fmaxf(fabsf(vertices[1].Y() - center.Y()), fabsf(vertices[2].Y() - center.Y())));
    maxZDistance = fmaxf(fabsf(vertices[0].Z() - center.Z()), fmaxf(fabsf(vertices[1].Z() - center.Z()), fabsf(vertices[2].Z() - center.Z())));
    maxOfMaxDistances = max(maxXDistance, max(maxYDistance, maxZDistance));
}

// PLANE & NEXT CHECK ANGLES
//bool Triangle::Intersect(Ray &ray)
//{
//	float t = surfacePlane.IntersectReturnT(ray);
//	if (t >= EPSILON)
//	{
//		float3 fa, fb, fc;
//		float3 x;
//		float3 point = ray.Origin() + ray.Direction() * t;
//
//		fa = vertices[0] - point;
//		fb = vertices[1] - point;
//		fc = vertices[2] - point;
//
//
//		x = float3::Cross(fa, fb);
//		x.Normalize();
//
//		if (float3::Dot(x, normal) < -EPSILON)
//		{
//			return false;
//		} 
//		else
//		{
//			x = float3::Cross(fb, fc);
//			x.Normalize();
//			if (float3::Dot(x, normal) < -EPSILON)
//			{
//				return false;
//			} 
//			else
//			{
//				x = float3::Cross(fc, fa);
//				x.Normalize();
//				if (float3::Dot(x, normal) < -EPSILON)
//				{
//					return false;
//				}
//				else
//				{
//					ray.Destination(point);					
//					ray.Distance(float3::Distance(ray.Origin(), ray.Destination()));
//					if (ray.Distance() < ray.ClippingValue())
//					{
//						ray.ClippingValue(ray.Distance());
//						ray.Intersected(true);
//						return true;
//					}
//					else
//					{
//						ray.Intersected(false);
//						return false;
//					}
//				}
//			}
//		}
//	}
//
//	return false;
//}

// BARYCENTRIC
bool Triangle::Intersect(Ray &ray, bool photon)
{
    //float t = surfacePlane.IntersectReturnT(ray);
    //if (t > EPSILON)
    //{
    //    float3 &P = ray.Origin() + ray.Direction() * t;
    //    float3 &P0 = vertices[0], &P1 = vertices[1], &P2 = vertices[2];
    //    float w0 = barycentric[0], w1 = barycentric[1], w2 = barycentric[2];

    //    float3 R = P - P0;
    //    float3 Q1 = P1 - P0;
    //    float3 Q2 = P2 - P0;
    //    float Q1Q2 = float3::Dot(Q1, Q2);
    //    float SQR_Q1Q2 = Q1Q2 * Q1Q2;
    //    float SQR_Q1 = float3::Dot(Q1, Q1);
    //    float SQR_Q2 = float3::Dot(Q2, Q2);

    //    float RQ1 = float3::Dot(R, Q1);
    //    float RQ2 = float3::Dot(R, Q2);

    //    float A = SQR_Q1 * SQR_Q2 - SQR_Q1Q2;
    //    float X1 = RQ1 * SQR_Q2 - (Q1Q2 * RQ2);
    //    float X2 = SQR_Q1 * RQ2 - (RQ1 * Q1Q2);

    //    w1 = X1 / A;
    //    w2 = X2 / A;
    //    w0 = 1.0f - w2 - w1;

    //    if (w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f && (w1 + w2) <= 1.0f)
    //    {
    //        ray.Destination(P);
    //        ray.Distance(float3::Distance(ray.Origin(), ray.Destination()));
    //        ray.NormalInDestinationPoint(normal);
    //        if (ray.Distance() < ray.ClippingValue())
    //        {
    //            barycentric[0] = w0;
    //            barycentric[1] = w1;
    //            barycentric[2] = w2;
    //            ray.ClippingValue(ray.Distance());
    //            ray.Intersected(true);
    //            return true;
    //        }
    //        else
    //        {
    //            ray.Intersected(false);
    //            return false;
    //        }
    //    }
    //}
    return false;
}

void Triangle::IntersectionOutput(const Ray &ray)
{
    //cout << "Intersection between Triangle & Ray" << endl << *this << ray;
    //if (ray.Intersected())
    //{
    //    cout << "Intersetion Point: " << ray.Destination() << endl;
    //    cout << "Intersetion Point(barycentric): " << barycentric[0] * vertices[0] + barycentric[1] * vertices[1] + barycentric[2] * vertices[2] << endl;
    //    cout << "Normal Vector in intersetion point: " << ray.NormalInDestinationPoint() << endl;
    //    cout << "Distance form origin to destination: " << ray.Distance() << endl;
    //}
    //else
    //{
    //    cout << "There is no intersetion point between them!" << endl;
    //}
    //cout << endl;
}

Primitive* Triangle::Clone() const
{
    return new Triangle(*this);
}

float3 Triangle::LocalIntersectionPoint(const float3 &worldIntersectionPoint, const float& scale)
{
    float x = (worldIntersectionPoint.X() - center.X()) / maxXDistance;
    float y = (worldIntersectionPoint.Y() - center.Y()) / maxYDistance;
    float z = (worldIntersectionPoint.Z() - center.Z()) / maxZDistance;
    CheckValueForInf(x);
    CheckValueForInf(y);
    CheckValueForInf(z);
    float3 localIntersectionpoint = float3(CalculateLocalIntersectionPoint(x, scale), CalculateLocalIntersectionPoint(y, scale), CalculateLocalIntersectionPoint(z, scale));
    return localIntersectionpoint;
}

float3 Triangle::GetUVW(const float3& globalIntersectionPoint)
{
    float3 UVW = verticesUVW[0] * barycentric[0] + verticesUVW[1] * barycentric[1] + verticesUVW[2] * barycentric[2];

    return UVW;
}

std::ostream &operator<<(std::ostream &os, const Triangle &value)
{
    os << "Triagle - v1: " << value.Vertices()[0] << ", v2: " << value.Vertices()[1] << ", v3: " << value.Vertices()[2] << endl;
    os << "Normal: " << value.Normal() << endl;
    os << "Surface Area: " << value.SurfaceArea() << endl;

    return os;
}