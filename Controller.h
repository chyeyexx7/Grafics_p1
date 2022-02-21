#pragma once

#include <QString>

#include "Factories/AbstractFactoryScenes.h"
#include "Factories/SceneFactory.h"
#include "Factories/RayTracingFactory.h"

#include "DataSettings/SetUp.h"
#include "DataSettings/InfoMapping.h"

class Controller
{
    shared_ptr<RayTracing> render;

public:
    Controller(Serializable::SaveFormat format, QString dataFileName, QString configVis);
    void start(int argc, char **argv);

};
