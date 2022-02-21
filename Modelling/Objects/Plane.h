#pragma once

#include "Object.h"
#include "Modelling/Animation.h"
#include "Modelling/TG/TranslateTG.h"
#include "glm/gtx/constants.hpp"


class Plane: public Object{
public:
    Plane() {};
    Plane(vec3 normal, vec3 pass_point, float v);

    Plane(vec3 normal, float d, float v);

    virtual ~Plane(){}
    virtual bool closestHit(Ray &r, HitInfo &info) const override;
    virtual bool hasHit(const Ray &r) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;


    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 normal;
    vec3 point;
private:

};


