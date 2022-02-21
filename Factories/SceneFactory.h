#pragma once

#include <string.h>
#include <QString>

#include <QCborMap>
#include <QCborValue>
#include "DataSettings/Serializable.h"
#include "Modelling/Scene.h"
#include "ObjectFactory.h"


class SceneFactory: public Serializable
{
public:
    typedef enum
    {
           VIRTUALWORLD,
           REALDATA,
           TEMPORALVW,
           TEMPORALDATA
    } SCENE_TYPES;

    SceneFactory() {};
    virtual ~SceneFactory() {};

    virtual shared_ptr<Scene> createScene()=0;
    virtual shared_ptr<Scene> createScene(Serializable::SaveFormat saveFormat, QString nomFitxer)=0;

    static SCENE_TYPES getSceneFactoryType( QString name);
    QString            getNameType(SCENE_TYPES t) const;

protected:
    shared_ptr<Scene> scene;
    SCENE_TYPES currentType;

};


