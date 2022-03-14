#include "Cylinder.h"

Cylinder::Cylinder(vec3 cen, vec3 ax, float r, float h, float data) : Object(data) {
    center = cen;
    axis = ax;
    radius = r;
    height = h;
}

Cylinder::Cylinder(float data) : Object(data) {
    center = vec3(0.0, 0.0, 0.0);
    axis = vec3(0.0, 1.0, 0.0);
    radius = 2.0f;
    height = 4.0f;
}

# include <iostream>
bool Cylinder::closestHit(Ray &raig, HitInfo& info) const {
    bool hasHit = false;
    /**
     * https://inmensia.com/articulos/raytracing/cilindroycono.html
     * a = dx’^2 + dz’^2
     * b = 2 * (ox’ * dx’ + oz’ * dz’)
     * c = ox’^2 + oz’^2 – 1
     * Ecuaciones utilizadas para ver si hay colisión con superfície curvada
     **/
    vec3 rayDir = raig.getDirection();
    float a = pow(rayDir.x, 2) + pow(rayDir.z, 2);
    float b = 2*(raig.getOrigin().x*rayDir.x + raig.getOrigin().z*rayDir.z);
    float c = pow(raig.getOrigin().x, 2) + pow(raig.getOrigin().z, 2) - 1;
    float discriminant = b*b - 4*a*c;

    // Si a es 0 o discriminante negativo no existen soluciones, por tanto,
    // no hay intersección

    if(a < DBL_EPSILON || discriminant < 0)
        return false;

    /**
     * Dos posibles soluciones para t si determinante > 0 y una solución para determinante = 0
     * t0′ = (-b + SQRT(b^2 – 4 * a * c) ) / (2 * a)
     * t1′ = (-b – SQRT(b^2 – 4 * a * c) ) / (2 * a)
     **/
    float t0 = (-b + sqrt(discriminant)) / (2 * a);
    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float temp = (t0 <= t1) ? t0 : t1;

    if((t0 > 0 || t1 > 0)){
        // Nos quedamos con la intersección más cercana
        if(temp <= raig.getTmax() && temp >= raig.getTmin()) {
            float height = raig.getOrigin().y + temp*raig.getDirection().y;
            if (height > 0 && height < this->height)
                hasHit = true;
        }
    }

    if(hasHit) {
        info.t = temp;
        info.p = raig.pointAtParameter(temp);
        info.normal = (info.p - this->center) / this->radius;
        info.mat_ptr = material.get();
    }

    return hasHit;
}

bool Cylinder::hasHit (const Ray& raig) const {

    return false;
}

void Cylinder::aplicaTG(shared_ptr<TG> t) {

}

void Cylinder::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("radius") && json["radius"].isDouble()) {
        radius = json["radius"].toDouble();
    }

    if (json.contains("h") && json["h"].isDouble()) {
        height = json["h"].toDouble();
    }

    if (json.contains("axis") && json["axis"].isArray()) {
        QJsonArray auxVec = json["axis"].toArray();
        center[0] = auxVec[0].toDouble();
        center[1] = auxVec[1].toDouble();
        center[2] = auxVec[2].toDouble();
    }

    if (json.contains("center") && json["center"].isArray()) {
        QJsonArray auxVec = json["center"].toArray();
        center[0] = auxVec[0].toDouble();
        center[1] = auxVec[1].toDouble();
        center[2] = auxVec[2].toDouble();
    }
}


//! [1]
void Cylinder::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(center[0]);auxArray.append(center[1]);auxArray.append(center[2]);
    json["center"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(axis[0]);auxArray2.append(axis[1]);auxArray2.append(axis[2]);
    json["axis"] = auxArray2;

    json["h"] = height;

    json["radius"] = radius;
}
//! [1]

void Cylinder::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "radius:\t" << radius<< "\n";
    QTextStream(stdout) << indent << "h:\t" << height<< "\n";
    QTextStream(stdout) << indent << "center:\t" << center[0] << ", "<< center[1] << ", "<< center[2] << "\n";
    QTextStream(stdout) << indent << "axis:\t" << axis[0] << ", "<< axis[1] << ", "<< axis[2] << "\n";

}
