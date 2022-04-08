#include "FittedPlane.h"

FittedPlane::FittedPlane() : Plane(){
}

FittedPlane::FittedPlane(vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d) : Plane(normal, pass_point, d){
    this->minpoint = pass_min;
    this->maxpoint = pass_max;
}

#include <iostream>
bool FittedPlane::closestHit(Ray &r, HitInfo &info) const{
    // Miramos si hay intersección con el plano
    if (Plane::closestHit(r, info)){
        // Miramos si el punto está dentro del rango
        if (info.p.x <= maxpoint.x && info.p.x >= minpoint.x && info.p.z <= maxpoint.y && info.p.z >= minpoint.y){
            // Si el material es MaterialTextura, añadiremos vec2 uv
            if (dynamic_cast<MaterialTextura*>(material.get())) {
                float u = (info.p.x - minpoint.x) / (maxpoint.x - minpoint.x);
                float v = (info.p.z - minpoint.y) / (maxpoint.y - minpoint.y);
                info.uv = vec2(u, v);
            }
            return true;
        }
    }
    return false;
}

void FittedPlane::aplicaTG(shared_ptr<TG> t){
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        //movem el punt de pas del pla
        vec4 c(point, 1.0);
        c = t->getTG() * c;
        point.x = c.x; point.y = c.y; point.z = c.z;
    }
    if (dynamic_pointer_cast<ScaleTG>(t)){
        //consideramos la y del minpoint y maxpoint como la componente z, usamos un vec2 para definir la xmin/max y zmin/max.
        vec4 cmin(minpoint.x, 1.0, minpoint.y, 1.0);
        vec4 cmax(maxpoint.x, 1.0, maxpoint.y, 1.0);
        cmin = t->getTG() * cmin;
        cmax = t->getTG() * cmax;
        minpoint.x *= cmin.x; minpoint.y *= cmin.z;
        maxpoint.x *= cmax.x; maxpoint.y *= cmax.z;
    }
}/*"type": "FITTEDPLANE",
   "normal": [0.0, 1.0, 0.0],
   "point": [0.0, 0.5, 0.0],
   "pmin": [-5.0, -5.0],
   "pmax": [5.0, 5.0],
   "material": {
       "type": "lambertian",
       "ka": [0.2, 0.2, 0.2],
       "kd": [0.7,0.6,0.5],
       "ks": [0.7, 0.7, 0.7],
       "shininess": 10.0,
       "textureFile": "://resources/map.png"
    }*/


void FittedPlane::read (const QJsonObject &json)
{
    Plane::read(json);

    if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        minpoint[0] = auxVec[0].toDouble();
        minpoint[1] = auxVec[1].toDouble();
    }
    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        maxpoint[0] = auxVec[0].toDouble();
        maxpoint[1] = auxVec[1].toDouble();
    }
}

void FittedPlane::write(QJsonObject &json) const {
    Plane::write(json);

    QJsonArray auxArray;
    auxArray.append(minpoint[0]);auxArray.append(minpoint[1]);
    json["pmin"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(maxpoint[0]);auxArray2.append(maxpoint[1]);
    json["pmax"] = auxArray2;
}

void FittedPlane::print(int indentation) const {
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "pmin:\t"<< minpoint[0] << " " << minpoint[1] << endl;
    QTextStream(stdout) << indent << "pmax:\t"<< maxpoint[0] << " " << maxpoint[1] << endl;
}
