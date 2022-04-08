#include "Triangle.h"

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, float data) : Object(data) {
    this->p1 = v1;
    this->p2 = v2;
    this->p3 = v3;
    this->normal = calculateNormal();
}

Triangle::Triangle(float data) : Object(data) {
    this->p1 = vec3(0.0, 0.0, 0.0);
    this->p2 = vec3(1.0, 0.0, 0.0);
    this->p3 = vec3(0.5, 1.0, 0.0);
    this->normal = calculateNormal();
}

bool Triangle::closestHit(Ray &raig, HitInfo& info) const {
    vec3 direction = normalize(raig.getDirection());
    float dirXnorm = dot(direction, this->normal);
    if(dirXnorm != 0) {
        float t = dot(p1 - raig.getOrigin(), this->normal) / dirXnorm;

        if(t < raig.getTmax() && raig.getTmin() < t){
            vec3 hitPoint = raig.getOrigin() + t * direction;

            float s1, s2, s3;
            s1 = dot(cross(hitPoint - p1, p2 - p1), this->normal);
            s2 = dot(cross(hitPoint - p2, p3 - p2), this->normal);
            s3 = dot(cross(hitPoint - p3, p1 - p3), this->normal);
            if((s1 < 0 && s2 < 0 && s3 < 0) || (s1 > 0 && s2 > 0 && s3 > 0)) {
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
    }
    return false;
}

bool Triangle::hasHit (const Ray& raig) const {
    vec3 direction = normalize(raig.getDirection());
    float dirXnorm = dot(direction, this->normal);
    if(dirXnorm != 0){
        float t = dot(p1 - raig.getOrigin(), this->normal) / dirXnorm;

        if(t < raig.getTmax() && raig.getTmin() < t){
            vec3 hitPoint = raig.getOrigin() + t * direction;

            float s1, s2, s3;
            s1 = dot(cross(hitPoint - p1, p2 - p1), this->normal);
            s2 = dot(cross(hitPoint - p2, p3 - p2), this->normal);
            s3 = dot(cross(hitPoint - p3, p1 - p3), this->normal);
            if((s1 < 0 && s2 < 0 && s3 < 0) || (s1 > 0 && s2 > 0 && s3 > 0)) {
                return true;
            }
        }
    }

    return false;
}

void Triangle::aplicaTG(shared_ptr<TG> t) {
    vec4 A(p1, 1.0f), B(p2, 1.0f), C(p3, 1.0f);
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        // Transformamos los 3 puntos
        A = t->getTG() * A;
        B = t->getTG() * B;
        C = t->getTG() * C;

        p1.x = A.x; p1.y = A.y; p1.z = A.z;
        p2.x = B.x; p2.y = B.y; p2.z = B.z;
        p3.x = C.x; p3.y = C.y; p3.z = C.z;
    }

    if (dynamic_pointer_cast<ScaleTG>(t)) {
        // Escalamos los tres puntos
        A = t->getTG() * A;
        C = t->getTG() * B;
        B = t->getTG() * C;

        float factorA = p1.x / A.x;
        float factorB = p2.x / B.x;
        float factorC = p3.x / C.x;

        p1.x * factorA; p1.y * factorA; p1.z * factorA;
        p2.x * factorB; p2.y * factorB; p2.z * factorB;
        p3.x * factorC; p3.y * factorC; p3.z * factorC;
    }

}

void Triangle::read (const QJsonObject &json) {
    Object::read(json);

    if (json.contains("p1") && json["p1"].isArray()) {
        QJsonArray auxVec = json["p1"].toArray();
        p1[0] = auxVec[0].toDouble();
        p1[1] = auxVec[1].toDouble();
        p1[2] = auxVec[2].toDouble();
    }

    if (json.contains("p2") && json["p2"].isArray()) {
        QJsonArray auxVec = json["p2"].toArray();
        p2[0] = auxVec[0].toDouble();
        p2[1] = auxVec[1].toDouble();
        p2[2] = auxVec[2].toDouble();
    }

    if (json.contains("p3") && json["p3"].isArray()) {
        QJsonArray auxVec = json["p3"].toArray();
        p3[0] = auxVec[0].toDouble();
        p3[1] = auxVec[1].toDouble();
        p3[2] = auxVec[2].toDouble();
    }

    this->normal = calculateNormal();
}


//! [1]
void Triangle::write(QJsonObject &json) const {
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(p1[0]);auxArray.append(p1[1]);auxArray.append(p1[2]);
    json["p1"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(p2[0]);auxArray2.append(p2[1]);auxArray2.append(p2[2]);
    json["p2"] = auxArray2;

    QJsonArray auxArray3;
    auxArray3.append(p3[0]);auxArray3.append(p3[1]);auxArray3.append(p3[2]);
    json["p3"] = auxArray3;
}
//! [1]

void Triangle::print(int indentation) const {
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "p1:\t" << p1[0] << ", " << p1[1] << ", " << p1[2] << "\n";
    QTextStream(stdout) << indent << "p2:\t" << p2[0] << ", "<< p2[1] << ", "<< p2[2] << "\n";
    QTextStream(stdout) << indent << "p3:\t" << p3[0] << ", "<< p3[1] << ", "<< p3[2] << "\n";

}

vec3 Triangle::calculateNormal() const {
    // N = ( (V2 – V1) x (V3 – V1) ) / | (V2 – V1) x (V3 – V1) |
    return normalize(cross(p2-p1, p3-p1));
}
