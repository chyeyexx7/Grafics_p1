#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Modelling/Animation.h"
#include "Modelling/TG/TranslateTG.h"

class Triangle: public Object
{
public:
    Triangle();
    Triangle(vec3 v1, vec3 v2, vec3 v3);
    Triangle(vec3 v1, vec3 v2, vec3 v3, float data);
    virtual ~Triangle();

    virtual bool closestHit(Ray& r, HitInfo& info) const override;
    virtual bool hasHit(const Ray& r) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

private:
    vec3 v1;
    vec3 v2;
    vec3 v3;
    vec3 normal;
};

#endif // TRIANGLE_H
