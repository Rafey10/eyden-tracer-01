// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		Vec3f d= ray.org - m_center;
		
		float a = ray.dir.dot(ray.dir);
		float b = 2*ray.dir.dot(d);
		float c = d.dot(d) - (m_radius*m_radius);
		
		float det = (b*b) - 4*a*c;
		
		if (det<0){
			return false;
		}
		
		float t1 = (-b - sqrt(det))/a;
		
		if (t1<Epsilon){
			t1 = (-b + sqrt(det))/a;
		}
		
		if (t1<Epsilon || t1 >ray.t){
			return false;
		}
		
		ray.t = t1;
		
		return true;
	}
	
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

