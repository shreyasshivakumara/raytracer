#ifndef MATERIALH
#define MATERIALH

struct hit_record;

class material {
public:
 virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
<<<<<<< HEAD
=======
 virtual vec3 emitted(float u, float v, const vec3& p) const {
    return vec3(0,0,0);
 }
>>>>>>> cornell_box
};

class lambertian : public material {
public:
<<<<<<< HEAD
 lambertian(const vec3& a) : albedo(a) {}
 virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
  vec3 target = rec.p + rec.normal + random_in_unit_sphere();
  scattered = ray(rec.p, target-rec.p);
  attenuation = albedo;
  return true;
 }
 vec3 albedo;
=======
    vec3 albedo;
    lambertian(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        //vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
>>>>>>> cornell_box
};

class metal : public material {
public:
<<<<<<< HEAD
 metal(const vec3& a, float f) : albedo(a) {if(f<1) fuzz=f; else fuzz=1;}
 virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
  vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
  scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
  attenuation = albedo;
  return (dot(scattered.direction(),rec.normal)>0);
 }
 vec3 albedo;
 int fuzz;
};

#endif
=======
    vec3 albedo;
    int fuzz;
    metal(const vec3& a, float f) : albedo(a) {if (f<1) fuzz=f; else fuzz=1;}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(),rec.normal)>0);
    }
};

class transluscent : public material {
public:
    vec3 albedo;
    transluscent(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 scatter_direction = rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class dielectric : public material {
public:
    float ref_idx;
    dielectric(float ri) : ref_idx(ri) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = vec3(1.0, 1.0, 1.0);  // Transparent materials do not absorb light
        vec3 refracted;
        float reflect_prob;
        float cosine;

        if (dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }

        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            reflect_prob = 1.0;
        }

        if (drand48() < reflect_prob) {
            scattered = ray(rec.p, reflected);
        } else {
            scattered = ray(rec.p, refracted);
        }
        return true;
        }
};


class emissive : public material {
public:
    vec3 albedo;
    emissive(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        return false;
    }
    virtual vec3 emitted(float u, float v, const vec3& p) const {
        return albedo;
    }
};
#endif
>>>>>>> cornell_box
