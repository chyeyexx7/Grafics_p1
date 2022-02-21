#pragma once

#include "Rendering/RayTracingGLU.h"
#include "Rendering/RayTracingPPM.h"
#include "Rendering/RayTracingTemps.h"

class RayTracingFactory
{
    static RayTracingFactory* instance;
    RayTracingFactory();

public:
    typedef enum  {
        ONLINE, IMAGE, TEMPORAL
    } RENDER_TYPES;

    static RayTracingFactory *getInstance() {
          if (instance==nullptr)
              instance = new RayTracingFactory();
          return instance;
    }
    shared_ptr<RayTracing> getRender(RENDER_TYPES t, QString filename);
    ~RayTracingFactory() {
    }
    RENDER_TYPES   getIndexType (shared_ptr<RayTracing> m);
    RENDER_TYPES   getRenderType( QString name);
    QString        getNameType(RENDER_TYPES  t);

};

