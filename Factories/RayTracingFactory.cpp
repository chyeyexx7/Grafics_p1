#include "RayTracingFactory.h"

RayTracingFactory *RayTracingFactory::instance = nullptr;

RayTracingFactory::RayTracingFactory() {

}
shared_ptr<RayTracing> RayTracingFactory::getRender(RENDER_TYPES t, QString filename)
{
    shared_ptr<RayTracing> r;
    switch (t) {
    case ONLINE:
        r =  make_shared<RayTracingGLU>();
        break;
    case IMAGE:
        r = make_shared<RayTracingPPM>();
        r->setOutputFile(filename);
        break;
    case TEMPORAL:
        r = make_shared<RayTracingTemps>();
         r->setOutputFile(filename);
        break;
         }
    return r;
}
RayTracingFactory::RENDER_TYPES RayTracingFactory::getIndexType(shared_ptr<RayTracing> m) {
    if (dynamic_pointer_cast<RayTracingGLU>(m) != nullptr) {
        return RENDER_TYPES::ONLINE;
    } else if (dynamic_pointer_cast<RayTracingPPM>(m) != nullptr) {
        return RENDER_TYPES::IMAGE;
    } else if (dynamic_pointer_cast<RayTracingTemps>(m) != nullptr) {
        return RENDER_TYPES::TEMPORAL;
    }
    return RENDER_TYPES::ONLINE;
}

RayTracingFactory::RENDER_TYPES RayTracingFactory::getRenderType( QString name) {
    if (name=="ONLINE") return RENDER_TYPES::ONLINE;
    else if (name=="IMAGE") return RENDER_TYPES::IMAGE;
    else if (name=="TEMPORAL") return RENDER_TYPES::TEMPORAL;
    else return  RENDER_TYPES::ONLINE;
}

QString RayTracingFactory::getNameType(RayTracingFactory::RENDER_TYPES t)
{
    switch(t) {
    case ONLINE:
        return(QString("ONLINE"));
        break;
    case IMAGE:
        return(QString("IMAGE"));
        break;
    case TEMPORAL:
        return(QString("TEMPORAL"));
        break;
    default:
        return(QString("ONLINE"));
        break;
    }
}

