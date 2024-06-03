#ifndef PLANEH
#define PLANEH

#include "hitable.h"

class plane : public hitable {
public:
    vec3 p0;        // A point on the plane
    vec3 normal;    // The normal vector of the plane
    material *mat_ptr;
    float size;     // Size of the plane

    plane() {}
    plane(const vec3& p0, const vec3& normal, material* m, float size) : p0(p0), normal(normal), mat_ptr(m), size(size) {}

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

    bool within_bounds(const vec3& point) const;
};

bool plane::within_bounds(const vec3& point) const {
    vec3 diff = point - p0;
    float half_size = size / 2.0;
    return fabs(diff.x()) <= half_size && fabs(diff.y()) <= half_size && fabs(diff.z()) <= half_size;
}

bool plane::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    float denom = dot(normal, r.direction());
    if (fabs(denom) > 1e-6) {
        float t = dot((p0 - r.origin()), normal) / denom;
        if (t < t_max && t > t_min) {
            vec3 hit_point = r.point_at_parameter(t);
            if (within_bounds(hit_point)) {
                rec.t = t;
                rec.p = hit_point;
                rec.normal = normal;
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }
    }
    return false;
}

#endif
