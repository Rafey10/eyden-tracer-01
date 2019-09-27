// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		Vec3f nab = (m_b-ray.org).cross(m_a-ray.org);
		Vec3f nbc = (m_c-ray.org).cross(m_b-ray.org);
		Vec3f nca = (m_a-ray.org).cross(m_c-ray.org);
		
		float sum = nab.dot(ray.dir)+nbc.dot(ray.dir)+nca.dot(ray.dir);
		float lmd1  = nab.dot(ray.dir)/sum;
		float lmd2  = nbc.dot(ray.dir)/sum;
		float lmd3  = nca.dot(ray.dir)/sum; 
		
		if (lmd1 <0 || lmd2 < 0|| lmd3<0){
			return false;
		}
		
		Vec3f norm = (m_b-m_a).cross(m_c-m_a);
		
		float a = -norm.dot(ray.org - m_a);
		float b = norm.dot(ray.dir);
		float t1;
		
		if (b == 0) {
			return false;
		} else {
			t1 = a / b;
		}
		
		if (t1<Epsilon || t1 > ray.t){
			return false;
		}
		
		ray.t = t1;
		
		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
