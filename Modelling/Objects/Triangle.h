#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Modelling/Animation.h"
#include "Modelling/TG/TranslateTG.h"


class Triangle: public Object
{
public:
    Triangle(vec3 v1,vec3 v2, vec3 v3, float data);
    Triangle(vec3 cord,float r, float d);
    virtual ~Triangle();
    virtual bool closestHit(Ray& r, HitInfo& info) const override;
    virtual bool hasHit(const Ray& r) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

private:
    vec3 updateNormal()const ;
    //EPSILON
    float const EPSILON = 0.001;
    // normal del pla del triangle
    vec3 normal;
    //vector de vertexs del triangle
    std::vector<vec3> vertexs;
    vec3 v1, v2, v3;
};

#endif // TRIANGLE_H
