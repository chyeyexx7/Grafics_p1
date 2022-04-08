#include "Controller.h"

Controller::Controller(Serializable::SaveFormat format, QString dataFileName, QString configVis)
{
    //
    // ETAPA 1: Carrega l'escena a visualitzar
    // cas a. A partir de dades virtuals (ja siguin construïdes pel programa o objectes .obj)
    // cas b. A partir de dades geolocalitzades (necessiten un mapeig addicional de les dades a gizmos)

    // S'obté el tipus de factory a utilitzar segons el tipus d'escena (cas a o cas b)
    // definit en el fitxer json de l'escena (veure el camp "typeScene")

    auto factory = AbstractFactoryScenes::getInstance().getSceneFactory(format, dataFileName);
    shared_ptr<Scene> scene = factory->createScene(format, dataFileName);

    // ETAPA 2: Configuració de la visualització
    // a. Definició de la càmera
    // b. Definició del viewport
    // c. Set up de l'escena
    auto visualSetup = make_shared<SetUp>();
    if (visualSetup->load(format, configVis) ) {
        visualSetup->print(0);

        scene->setBackground(visualSetup->getBackground());
        scene->setMAXDEPTH(visualSetup->getMAXDEPTH());

        scene->setTopBackground(visualSetup->getTopBackground());
        scene->setDownBackground(visualSetup->getDownBackground());

        // TODO: Fase 2: Afegim les llums de l'escena
        scene->setGlobalLight(visualSetup->getGlobalLight());
        scene->setLights(visualSetup->getLights());

        // ETAPA 3: Inicialitzacio del Rendering
        // usa un Factory Method per a construir el tipus de render
        render = RayTracingFactory::getInstance()->getRender(visualSetup->getRenderType(), visualSetup->getOutputFile());
        render->setScene(scene);
        render->setCamera(visualSetup->getCamera());

    }
}

void Controller::start(int argc, char **argv) {
    // ETAPA 2: Activació del Rendering
    render->startRendering(argc, argv);
}




