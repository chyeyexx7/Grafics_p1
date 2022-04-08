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
    vec3 normal = normalize(rec.normal);
    vec3 dir = normalize(r_in.getDirection());
    float ratio = nut / 1.0003f;

    // Si el producto escalar es positivo, invertimos el índice de reflexión y normal
    if (dot(dir, normal) > 0) {
        normal = -normal;
    } else {
        ratio = 1.0003f / nut;
    }
    target = refract(dir, normal, ratio);
    // Si es < EPSILON, entonces es interna total
    if (length(target) < FLT_EPSILON) {
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


void Transparent::read(const QJsonObject& json) {
    Material::read(json);
    if (json.contains("kt") && json["kt"].isArray()) {
        QJsonArray auxVec = json["kt"].toArray();
        Kt[0] = auxVec[0].toDouble();
        Kt[1] = auxVec[1].toDouble();
        Kt[2] = auxVec[2].toDouble();
    }
    if (json.contains("nut") && json["nut"].isDouble())
        nut = json["nut"].toDouble();
}

void Transparent::write(QJsonObject &json) const
{
    QJsonArray auxArray;
    auxArray.append(Kt[0]);auxArray.append(Kt[1]);auxArray.append(Kt[2]);
    json["kt"] = auxArray;

    json["nut"] = nut;
}

//! [1]

void Transparent::print(int indentation) const
{
    Material::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "Kt:\t" << Kt[0] << ", "<< Kt[1] << ", "<< Kt[2] << "\n";
    QTextStream(stdout) << indent << "nut:\t" << nut << "\n";

}

