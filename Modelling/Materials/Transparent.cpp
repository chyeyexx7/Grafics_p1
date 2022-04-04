#include "Transparent.h"

Transparent::Transparent(const vec3& color): Material()
{
    Ks = color;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}

Transparent::~Transparent()
{
}

vec3 Transparent::getAttenuation(const Ray& r_in, const HitInfo& rec) const  {
    return intern ? Ks : Kt;
}


bool Transparent::getOneScatteredRay(const Ray& r_in, const HitInfo& rec, Ray& r_out) const  {
    vec3 target;
    vec3 normal = rec.normal;
    vec3 dir = normalize(r_in.getDirection());
    float ratio;

    // Si el producto escalar es positivo, invertimos el índice de reflexión y normal
    if (dot(dir, normal) > 0) {
        normal = -normal;
        ratio = nut / 1.0003f;
    } else {
        ratio = 1.0003f / nut;
    }
    target = refract(dir, normal, ratio);
    // Si es < EPSILON, entonces es interna total
    if (length(target) < 0.01f) {
        intern = true;
        target = reflect(dir, normal);
    }
    r_out = Ray(rec.p + 0.01f * target, target);

    return true;
}
bool Transparent::getMultipleScatteredRays(const Ray& r_in, const HitInfo& rec,  std::vector<Ray>& r_out) const  {
    for (int i = 0; i < MULTIPLE_SCATTER_SAMPLES; i++) {
        vec3 target = reflect(r_in.getDirection(), rec.normal);
        // 0.01f*target para reducir acne
        r_out.push_back(Ray(rec.p + 0.01f * target, target));
    }
    return true;
}

