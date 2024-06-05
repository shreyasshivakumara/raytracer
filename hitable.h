#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material;

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
	float u;
	float v;
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual bool is_emissive() const { return false; }
    virtual vec3 random_point() const { return vec3(0, 0, 0); }
};

#endif