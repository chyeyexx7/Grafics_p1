#include "Lambertian.h"

Lambertian::Lambertian(const vec3& color): Material()
{
    Kd = color;
}

Lambertian::Lambertian(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Lambertian::Lambertian(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}
Lambertian::~Lambertian()
{
}

vec3 Lambertian::getAttenuation(const Ray& r_in, const HitInfo& rec) const  {
    return Kd;
}

bool Lambertian::getOneScatteredRay(const Ray& r_in, const HitInfo& rec, Ray& r_out) const  {
    vec3 target = rec.p + rec.normal + Hitable::RandomInSphere();
    r_out =  Ray(rec.p, target-rec.p);
    return true;
}
bool Lambertian::getMultipleScatteredRays(const Ray& r_in, const HitInfo& rec,  std::vector<Ray>& r_out) const  {
    for (int i = 0; i < MULTIPLE_SCATTER_SAMPLES; i++) {
        vec3 target = rec.p + rec.normal + Hitable::RandomInSphere();
        r_out.push_back( Ray(rec.p, target-rec.p));
    }
    return true;
}
