#pragma once

#include "glm/glm.hpp"

#include "Serializable.h"
#include "Factories/ObjectFactory.h"
#include "Factories/MaterialFactory.h"
#include "Modelling/Materials/ColorMapStatic.h"

class PropertyInfo : public Serializable
{
public:
    PropertyInfo();
    virtual ~PropertyInfo() {};
    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 getPuntBase(shared_ptr<Object> base, vec2 puntReal);

    QString name;
    ObjectFactory::OBJECT_TYPES gyzmo;
    float minValue;
    float maxValue;
    shared_ptr<Material> material;
    ColorMapStatic::COLOR_MAP_TYPES colorMapType;

};
