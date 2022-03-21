#include "Triangle.h"

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, float data) : Object(data) {
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->normal = calculateNormal();
}

Triangle::Triangle(float data) : Object(data) {
    this->v1 = vec3(0.0, 0.0, 0.0);
    this->v2 = vec3(1.0, 0.0, 0.0);
    this->v3 = vec3(0.5, 1.0, 0.0);
    this->normal = calculateNormal();
}
bool Triangle::closestHit(Ray &raig, HitInfo& info) const {
    vec3 direction = normalize(raig.getDirection());
    float dirXnorm = dot(direction, this->normal);

    if(dirXnorm != 0){
        float t = dot(v1 - raig.getOrigin(), this->normal) / dirXnorm;

        if(t < raig.getTmax() && raig.getTmin() < t){
            vec3 hitPoint = raig.getOrigin() + t * direction;

            if(dot(cross(hitPoint - v1, v2 - v1), this->normal) > 0 ||
                    dot(cross(hitPoint - v2, v3 -v2), this->normal) > 0 ||
                    dot(cross(hitPoint - v3, v1 -v3), this->normal) > 0) {
                return false;
            }

            info.p = hitPoint;
            if(dirXnorm < 0){
                info.normal = this->normal;
            }else{
                info.normal = -this->normal;
            }
            info.mat_ptr = material.get();
            info.t = t;
            return true;
        }
    }

    return false;
}

bool Triangle::hasHit (const Ray& raig) const {
    vec3 direction = normalize(raig.getDirection());
    float dirXnorm = dot(direction, this->normal);

    if(dirXnorm != 0){
        float t = dot(v1 - raig.getOrigin(), this->normal) / dirXnorm;

        if(t < raig.getTmax() && raig.getTmin() < t){
            vec3 hitPoint = raig.getOrigin() + t * direction;

            if(dot(cross(hitPoint - v1, v2 - v1), this->normal) > 0 ||
                    dot(cross(hitPoint - v2, v3 -v2), this->normal) > 0 ||
                    dot(cross(hitPoint - v3, v1 -v3), this->normal) > 0) {
                return false;
            }
            return true;
        }
    }

    return false;
}

void Triangle::aplicaTG(shared_ptr<TG> t) {

}

void Triangle::read (const QJsonObject &json) {
    Object::read(json);

    if (json.contains("p1") && json["p1"].isArray()) {
        QJsonArray auxVec = json["p1"].toArray();
        v1[0] = auxVec[0].toDouble();
        v1[1] = auxVec[1].toDouble();
        v1[2] = auxVec[2].toDouble();
    }

    if (json.contains("p2") && json["p2"].isArray()) {
        QJsonArray auxVec = json["p2"].toArray();
        v2[0] = auxVec[0].toDouble();
        v2[1] = auxVec[1].toDouble();
        v2[2] = auxVec[2].toDouble();
    }

    if (json.contains("p2") && json["p2"].isArray()) {
        QJsonArray auxVec = json["p2"].toArray();
        v3[0] = auxVec[0].toDouble();
        v3[1] = auxVec[1].toDouble();
        v3[2] = auxVec[2].toDouble();
    }
}


//! [1]
void Triangle::write(QJsonObject &json) const {
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(v1[0]);auxArray.append(v1[1]);auxArray.append(v1[2]);
    json["p1"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(v2[0]);auxArray2.append(v2[1]);auxArray2.append(v2[2]);
    json["p2"] = auxArray2;

    QJsonArray auxArray3;
    auxArray3.append(v3[0]);auxArray3.append(v3[1]);auxArray3.append(v3[2]);
    json["p3"] = auxArray3;
}
//! [1]

void Triangle::print(int indentation) const {
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "p1:\t" << v1[0] << ", " << v1[1] << ", " << v1[2] << "\n";
    QTextStream(stdout) << indent << "p2:\t" << v2[0] << ", "<< v2[1] << ", "<< v2[2] << "\n";
    QTextStream(stdout) << indent << "p3:\t" << v3[0] << ", "<< v3[1] << ", "<< v3[2] << "\n";

}

vec3 Triangle::calculateNormal() const {
    // N = ( (V2 – V1) x (V3 – V1) ) / | (V2 – V1) x (V3 – V1) |
    return normalize(cross(v2-v1, v3-v1));
}
