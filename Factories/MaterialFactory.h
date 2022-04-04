#pragma once

#include "Modelling/Materials/Material.h"
#include "Modelling/Materials/Lambertian.h"
#include "Modelling/Materials/Metal.h"


class MaterialFactory
{
    MaterialFactory(){};
public:
    typedef enum  MATERIAL_TYPES{
        LAMBERTIAN,
        METAL,
        TRANSPARENT,
        MATERIALTEXTURA,
    } MATERIAL_TYPES;

    static MaterialFactory& getInstance() {
        static MaterialFactory instance;
        return instance;
    }

    shared_ptr<Material> createMaterial(MATERIAL_TYPES t);
    shared_ptr<Material> createMaterial(vec3 a, vec3 d, vec3 s, float beta, float opacity, MATERIAL_TYPES t);
    MATERIAL_TYPES getIndexType (shared_ptr<Material> m);
    MATERIAL_TYPES getMaterialType( QString name);
    QString        getNameType(MATERIAL_TYPES  t);

};
