#include "MaterialTextura.h"

MaterialTextura::MaterialTextura(const vec3& color): Material()
{
    Kd = color;
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}

MaterialTextura::~MaterialTextura()
{
}

vec3 MaterialTextura::getDiffuse(vec2 point) const {
    return texture->getColorPixel(point);
}

vec3 MaterialTextura::getAttenuation(const Ray& r_in, const HitInfo& rec) const  {
    return Kd;
}


bool MaterialTextura::getOneScatteredRay(const Ray& r_in, const HitInfo& rec, Ray& r_out) const  {
    return false;
}
bool MaterialTextura::getMultipleScatteredRays(const Ray& r_in, const HitInfo& rec,  std::vector<Ray>& r_out) const  {
    return false;
}


void MaterialTextura::read(const QJsonObject& json) {
    Material::read(json);
    // Leemos el tipo de textura
    if (json.contains("textureFile") && json["textureFile"].isString()) {
        textureName = json["textureFile"].toString();
        texture = make_shared<Texture>(textureName);

    }

}

void MaterialTextura::write(QJsonObject& json) const {
    Material::write(json);
    json["textureFile"] = textureName;
}

void MaterialTextura::print(int indentation) const
{
    Material::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "Texture Name:\t" << textureName << "\n";
}

