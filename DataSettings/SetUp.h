#ifndef SETUP_H
#define SETUP_H

#include "Serializable.h"
#include <QCborMap>
#include <QCborValue>
#include <QFile>

#include "glm/glm.hpp"
#include "Rendering/Camera.h"
#include "Factories/RayTracingFactory.h"
#include "Factories/LightFactory.h"

class SetUp : public Serializable
{
public:
    SetUp();

    QString                         getOutputFile();
    RayTracingFactory::RENDER_TYPES getRenderType();
    shared_ptr<Camera>              getCamera();
    vec3                            getGlobalLight();
    std::vector<shared_ptr<Light>>  getLights();
    bool                            getBackground();
    vec3                            getTopBackground();
    vec3                            getDownBackground();
    int                             getMAXDEPTH();

    void setOutpuFile(QString name);
    void setRenderType(RayTracingFactory::RENDER_TYPES type);
    void setCamera(shared_ptr<Camera> cam);
    void setGlobalLight(vec3 globalLight);
    void setLights(std::vector<shared_ptr<Light>> lights);
    void setBackground(bool back);
    void setTopBackground(vec3 color);
    void setDownBackground(vec3 color);

    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void print(int indentation) const;

    bool load(Serializable::SaveFormat saveFormat, QString nameFile);
    bool save(Serializable::SaveFormat saveFormat, QString nameFile) const;

    virtual ~SetUp() {};


private:
    RayTracingFactory::RENDER_TYPES renderingType;
    QString outputFile;
    // Camera
    shared_ptr<Camera> camera;
    // Vector de llums de l'escena
    std::vector<shared_ptr<Light>> lights;
    // Llum global
    vec3 globalLight;
    // Conte si s'ha de tenir en compte el background o no en els rajos secundaris en
    // cas de no fer hit amb l'escena
    bool background = false;
    // colors top i bottom de  fons
    vec3 topBackground;
    vec3 downBackground;

    // màxim nombre de rajos recursius incloent el primari
    int   MAXDEPTH;
};

#endif // SETUP_H
