#include "Cylinder.h"

Cylinder::Cylinder(vec3 cen, vec3 ax, float r, float h, float data) : Object(data) {
    center = cen;
    axis = ax;
    radius = r;
    this->h = h;
}

Cylinder::Cylinder(float data) : Object(data) {
    center = vec3(0.0, 0.0, 0.0);
    axis = vec3(0.0, 1.0, 0.0);
    radius = 2.0f;
    h = 4.0f;
}

# include <iostream>
bool Cylinder::closestHit(Ray &raig, HitInfo& info) const {
    /**
     * https://inmensia.com/articulos/raytracing/cilindroycono.html
     * a = dx’^2 + dz’^2
     * b = 2 * (ox’ * dx’ + oz’ * dz’)
     * c = ox’^2 + oz’^2 – 1
     * Ecuaciones utilizadas para ver si hay colisión con superfície curvada
     **/
    int hasHit = 0;
    float temp, closest = std::numeric_limits<float>::max();

    vec3 rayDir = raig.getDirection();
    vec3 oc = raig.getOrigin() - center;

    /**
     * Dos posibles soluciones para t si discriminante > 0 y una solución para discriminante = 0
     * t0′ = (-b + SQRT(b^2 – 4 * a * c) ) / (2 * a)
     * t1′ = (-b – SQRT(b^2 – 4 * a * c) ) / (2 * a)
     * Que puede ser simplificado como:
     * b = 2 * k, con k = ox’ * dx’ + oz’ * dz’
     * t0′ = (-k + SQRT(k^2 – a * c) ) / a
     * t1′ = (-k – SQRT(k^2 – a * c) ) / a
     **/
    float a = pow(rayDir.x, 2) + pow(rayDir.z, 2);
    // b = 2*k
    float k = rayDir.x*(oc.x) + rayDir.z*oc.z;
    float c = pow(oc.x, 2) + pow(oc.z, 2) - pow(radius, 2);
    float discriminant = k*k - a*c;

    // Si a es 0 o discriminante negativo no existen soluciones, por tanto,
    // no hay intersección
    if(a != 0 || discriminant > 0) {
        // De las dos posibles soluciones, nos quedamos con la intersección más cercana
        // que esté dentro del rango de las alturas del cilindro
        temp = (-k + sqrt(discriminant)) / a;
        if(temp < raig.getTmax() && temp > raig.getTmin()) {
            float height = raig.pointAtParameter(temp).y;
            // Si el punto está dentro del cilindro (altura)
            if (height >= center.y && height <= (center.y + h)) {
                hasHit = 1;
                closest = temp;
            }
        }

        temp = (-k - sqrt(discriminant)) / a;
        if(temp < closest && temp < raig.getTmax() && temp > raig.getTmin()) {
            float height = raig.pointAtParameter(temp).y;
            // Si el punto está dentro del cilindro (altura)
            if (height >= center.y && height <=(center.y + h)) {
                hasHit = 1;
                closest = temp;
            }
        }
    }

    /**
     * Procedemos a mirar si hay intersección
     **/
    // Tapa superior
    temp =  (-oc.y + h) / (rayDir.y);
    float x = raig.pointAtParameter(temp).x;
    float z = raig.pointAtParameter(temp).z;

    if (temp < closest && temp < raig.getTmax() && temp > raig.getTmin() && pow(x - center.x, 2) + pow(z - center.z, 2) <= pow(radius, 2)) {
      hasHit = 2;
      closest = temp;
    }
    // Tapa inferior
    temp =  (-oc.y) / rayDir.y;
    x = raig.pointAtParameter(temp).x;
    z = raig.pointAtParameter(temp).z;

    if (temp < closest && temp < raig.getTmax() && temp > raig.getTmin() && pow(x - center.x, 2) + pow(z - center.z, 2) <= pow(radius, 2)) {
      hasHit = 3;
      closest = temp;
    }

    // Miramos si ha habido intersección entre la superfície curvada o las tapas
    if (hasHit) {
      info.t = closest;
      info.p = raig.pointAtParameter(info.t);
      info.mat_ptr = material.get();
      switch(hasHit) {
        case 1:
          info.normal = normalize(vec3(info.p.x - center.x, 0, info.p.z - center.z);
          break;
      case 2:
          info.normal = vec3(0.0, 1.0, 0.0);
          cout << "top: " << info.p.y << endl;
          break;
      case 3:
          info.normal = vec3(0.0, -1.0, 0.0);
          cout << "bottom: " << info.p.y << endl;
          break;
      default:
          break;
      }
    }

    return hasHit != 0;
}

bool Cylinder::hasHit (const Ray& raig) const {
    int hasHit = 0;
    /**
     * https://inmensia.com/articulos/raytracing/cilindroycono.html
     * a = dx’^2 + dz’^2
     * b = 2 * (ox’ * dx’ + oz’ * dz’)
     * c = ox’^2 + oz’^2 – 1
     * Ecuaciones utilizadas para ver si hay colisión con superfície curvada
     **/
    vec3 rayDir = normalize(raig.getDirection());
    float aux1 = raig.getOrigin().x - center.x;
    float aux2 = raig.getOrigin().z - center.z;

    float a = pow(rayDir.x, 2) + pow(rayDir.z, 2);
    // b = 2*k
    float k = rayDir.x*aux1 + rayDir.z*aux2;
    float c = pow(aux1, 2) + pow(aux2, 2) - pow(radius, 2);
    float discriminant = k*k - a*c;

    // Si a es 0 o discriminante negativo no existen soluciones, por tanto,
    // no hay intersección

    if(a < DBL_EPSILON || discriminant < 0)
        return false;

    /**
     * Dos posibles soluciones para t si discriminante > 0 y una solución para discriminante = 0
     * t0′ = (-b + SQRT(b^2 – 4 * a * c) ) / (2 * a)
     * t1′ = (-b – SQRT(b^2 – 4 * a * c) ) / (2 * a)
     * Que puede ser simplificado como:
     * b = 2 * k, con k = ox’ * dx’ + oz’ * dz’
     * t0′ = (-k + SQRT(k^2 – a * c) ) / a
     * t1′ = (-k – SQRT(k^2 – a * c) ) / a
     **/

    float t0 = (-k + sqrt(discriminant)) / a;
    float t1 = (-k - sqrt(discriminant)) / a;
    float temp;
    // Nos quedamos con la intersección más cercana
    if(discriminant == 0) {
        temp = t1;
    } else {
        temp = (t0 < t1) ? t0 : t1;
    }

    // Miramos si estamos dentro del rango
    if(temp < raig.getTmax() && temp >=raig.getTmin()) {
        float height = raig.getOrigin().y + temp*rayDir.y;
        // Si el punto está dentro del cilindro (altura)
        if (height >= center.y && height <= (center.y + h)) {
            return true;
        }
    }

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
        h = json["h"].toDouble();
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

    json["h"] = h;

    json["radius"] = radius;
}
//! [1]

void Cylinder::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "radius:\t" << radius<< "\n";
    QTextStream(stdout) << indent << "h:\t" << h<< "\n";
    QTextStream(stdout) << indent << "center:\t" << center[0] << ", "<< center[1] << ", "<< center[2] << "\n";
    QTextStream(stdout) << indent << "axis:\t" << axis[0] << ", "<< axis[1] << ", "<< axis[2] << "\n";

}
