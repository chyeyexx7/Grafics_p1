#pragma once

#include "Material.h"

class Metal : public Material
{

public:
    Metal() {};
    Metal(const vec3& color);
    Metal(const vec3& a, const vec3& d, const vec3& s, const float k);
    Metal(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
    virtual ~Metal();
    virtual vec3 getAttenuation(const Ray& r_in, const HitInfo& rec) const override;
    virtual bool getOneScatteredRay(const Ray& r_in, const HitInfo& rec, Ray& r_out) const override;
    virtual bool getMultipleScatteredRays(const Ray& r_in, const HitInfo& rec, std::vector<Ray>& r_out) const override;
private:
    const int MULTIPLE_SCATTER_SAMPLES = 5;
};
