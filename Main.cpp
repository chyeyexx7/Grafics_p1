#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv) {

    cout << "Init..." <<endl;
    Q_INIT_RESOURCE(resources);

    // Línia que controla els fitxers a carregar per l'aplicació.
    // Es donen d'alta prèviament a la carpeta de resources del projecte
    // Cal que aquí no hi posis extensió (directament anirà a buscar el fitxer amb extensió .json

    // Exemple d'escena virtual carregada des de json:
    auto controller = make_shared<Controller>(Serializable::Json, "://resources/meshExample", "://resources/setupRenderOneSphere");
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/twoSpheres", "://resources/setupRenderTwoSpheres");
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/spheresLambertianes", "://resources/setupRenderSpheres");
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/oneCylinder", "://resources/setupRenderSpheres");
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/figuresLambertian", "://resources/setupRenderFiguresLambertian");
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/cornell_box_geometry_phong", "://resources/cornell_box_config_vis_phong");
    // Exemple d'escena de dades carregada des de json:
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/data0", "://resources/setupRenderTwoSpheres");

    controller->start(argc, argv);

    return(0);
}
