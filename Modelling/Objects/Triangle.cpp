#include "Triangle.h"

Triangle::Triangle(vec3 v1,vec3 v2, vec3 v3, float data)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    vertexs = std::vector<vec3>();
    vertexs.push_back(this->v1);
    vertexs.push_back(this->v2);
    vertexs.push_back(this->v3);
    normal = normalize(cross(this->v2 - this->v1, this->v3 - this->v1));
}

Triangle::Triangle(vec3 cord,float r, float d)
{
    this->v1 = vec3(1,0,0);
    this->v2 = vec3(0,1,0);
    this->v3 = vec3(0,0,1);
    vertexs = std::vector<vec3>();
    vertexs.push_back(this->v1);
    vertexs.push_back(this->v2);
    vertexs.push_back(this->v3);
    normal = normalize(cross(this->v2 - this->v1, this->v3 - this->v1));
    //this->aplicaTG(new Translate(cord));
}

bool Triangle::closestHit(Ray &r, HitInfo &info) const {
    vec3 direction = normalize(r.getDirection());
    float dirXnorm = dot(direction, this->normal);

    if(dirXnorm != 0){
        float t = dot(v1 - r.getOrigin(), this->normal) / dirXnorm;

        if(t < r.getTmax() && r.getTmin() < t){
            vec3 hitPoint = r.getOrigin() + t * direction;

            if(dot(cross(hitPoint - v1, v2 - v1), this->normal) > 0) {
                return false;
            }
            if(dot(cross(hitPoint - v2, v3 -v2), this->normal) > 0) {
                return false;
            }
            if(dot(cross(hitPoint - v3, v1 -v3), this->normal) > 0) {
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

    return true;
}

bool Triangle::hasHit(const Ray& r) const
{
    return false;
}

void Triangle::aplicaTG(shared_ptr<TG> tg) {
    if(dynamic_pointer_cast<TranslateTG>(tg)) {
        //Per ara només es preveuen translacions
        vec4 t1(this->v1, 1.0);
        vec4 t2(this->v2, 1.0);
        vec4 t3(this->v3, 1.0);

        t1 = tg->getTG() * t1;
        t2 = tg->getTG() * t2;
        t3 = tg->getTG() * t3;

        this->v1.x = t1.x; this->v1.y = t1.y; this->v1.z = t1.z;
        this->v2.x = t2.x; this->v2.y = t2.y; this->v2.z = t2.z;
        this->v3.x = t3.x; this->v3.y = t3.y; this->v3.z = t3.z;
    }
}

void Triangle::read(const QJsonObject &json) {

    Object::read(json);

    if(json.contains("p1") && json["p1"].isArray()) {
        QJsonArray auxVec = json["p1"].toArray();

        this->v1[0] = auxVec[0].toDouble();
        this->v1[1] = auxVec[1].toDouble();
        this->v1[2] = auxVec[2].toDouble();
    }
    if(json.contains("p2") && json["p2"].isArray()) {
        QJsonArray auxVec = json["p2"].toArray();

        this->v2[0] = auxVec[0].toDouble();
        this->v2[1] = auxVec[1].toDouble();
        this->v2[2] = auxVec[2].toDouble();
    }
    if(json.contains("p3") && json["p3"].isArray()) {
        QJsonArray auxVec = json["p3"].toArray();

        this->v3[0] = auxVec[0].toDouble();
        this->v3[1] = auxVec[1].toDouble();
        this->v3[2] = auxVec[2].toDouble();
    }

    vertexs = std::vector<vec3>();
    vertexs.push_back(this->v1);
    vertexs.push_back(this->v2);
    vertexs.push_back(this->v3);

    this->normal = this->updateNormal();
}

void Triangle::write(QJsonObject &json) const {

    Object::write(json);

    QJsonArray auxArrayP1, auxArrayP2, auxArrayP3;

    auxArrayP1.append(v1[0]); auxArrayP1.append(v1[1]); auxArrayP1.append(v1[2]);
    auxArrayP2.append(v2[0]); auxArrayP2.append(v2[1]); auxArrayP2.append(v2[2]);
    auxArrayP3.append(v3[0]); auxArrayP3.append(v3[1]); auxArrayP3.append(v3[2]);

    json["p1"] = auxArrayP1;
    json["p2"] = auxArrayP2;
    json["p3"] = auxArrayP3;
}

void Triangle::print(int indentation) const {

    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "p1: \t" << v1[0] << ", "
                        << v1[1] << ", " << v1[2] << "\n";
    QTextStream(stdout) << indent << "p2: \t" << v2[0] << ", "
                        << v2[1] << ", " << v2[2] << "\n";
    QTextStream(stdout) << indent << "p3: \t" << v3[0] << ", "
                        << v3[1] << ", " << v3[2] << "\n";
}

vec3 Triangle::updateNormal() const{
    vec3 normal, A(v2-v1), B(v3-v1);
    normal = cross(A, B);
    return normalize(normal);
}

Triangle::~Triangle()
{

}
