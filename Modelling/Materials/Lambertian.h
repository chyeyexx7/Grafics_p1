#pragma once

#include "Material.h"

class Lambertian : public Material
{

public:
    Lambertian() {};
    Lambertian(const vec3& color);
    Lambertian(const vec3& a, const vec3& d, const vec3& s, const float k);
    Lambertian(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
    virtual ~Lambertian();
    virtual vec3 getAttenuation(const Ray& r_in, const HitInfo& rec) const override;
    virtual bool getOneScatteredRay(const Ray& r_in, const HitInfo& rec, Ray& r_out) const override;
    virtual bool getMultipleScatteredRays(const Ray& r_in, const HitInfo& rec, std::vector<Ray>& r_out) const override;
private:
    const int MULTIPLE_SCATTER_SAMPLES = 5;
};
