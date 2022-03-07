#include "triangle.h"

Triangle::Triangle()
{

}

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->normal = normalize(glm::cross((v2–v1), (v3–v1)));
}

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, float data):Object(data)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->normal = normalize(glm::cross((v2–v1), (v3–v1)));
}

Triangle::~Triangle()
{

}

bool Sphere::closestHit(Ray &raig, HitInfo& info) const {



    return false;
}

bool Sphere::hasHit (const Ray& raig) const {
    vec3 oc = raig.getOrigin() - center;
    float a = dot(raig.getDirection(), raig.getDirection());
    float b = dot(oc, raig.getDirection());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < raig.getTmax() && temp > raig.getTmin()) {
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < raig.getTmax() && temp > raig.getTmin()) {
            return true;
        }
    }
    return false;
}

void Sphere::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
}

void Sphere::read (const QJsonObject &json)
{
    Object::read(json);
    QJsonArray auxVec;

    if (json.contains("p1") && json["p1"].isArray()) {
        auxVec = json["p1"].isArray();
        p1[0] = auxVec[0].toDouble();
        p1[1] = auxVec[1].toDouble();
        p1[2] = auxVec[2].toDouble();
    }
    if (json.contains("p2") && json["p2"].isArray()) {
        auxVec = json["p2"].isArray();
        p2[0] = auxVec[0].toDouble();
        p2[1] = auxVec[1].toDouble();
        p2[2] = auxVec[2].toDouble();
    }
    if (json.contains("p3") && json["p3"].isArray()) {
        auxVec = json["p3"].isArray();
        p3[0] = auxVec[0].toDouble();
        p3[1] = auxVec[1].toDouble();
        p3[2] = auxVec[2].toDouble();
    }
}


//! [1]
void Sphere::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(center[0]);auxArray.append(center[1]);auxArray.append(center[2]);
    json["center"] = auxArray;

    json["radius"] = radius;
    QJsonArray p1;
    p1.append(v1[0]);p1.append(v1[1]);p1.append(v1[2]);
    json["p1"] = p1;
    QJsonArray p2;
    p2.append(v2[0]);p2.append(v2[1]);p1.append(v2[2]);
    json["p2"] = p2;
    QJsonArray p3;
    p3.append(v3[0]);p3.append(v3[1]);p1.append(v3[2]);
    json["p3"] = p3;
}
//! [1]

void Sphere::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "point 1:\t[" << v1[0] << ", "<< v1[1] << ", "<< v1[2] << "]\n";
    QTextStream(stdout) << indent << "point 2:\t[" << v2[0] << ", "<< v2[1] << ", "<< v2[2] << "]\n";
    QTextStream(stdout) << indent << "point 3:\t[" << v3[0] << ", "<< v3[1] << ", "<< v3[2] << "]\n";
}
