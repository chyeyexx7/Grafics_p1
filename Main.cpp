#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv) {

    cout << "Init..." <<endl;
    Q_INIT_RESOURCE(resources);

    // Línia que controla els fitxers a carregar per l'aplicació.
    // Es donen d'alta prèviament a la carpeta de resources del projecte
    // Cal que aquí no hi posis extensió (directament anirà a buscar el fitxer amb extensió .json

    // Exemple d'escena virtual carregada des de json:
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/oneSphere", "://resources/setupRenderOneSphere"); //Una esfera
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/twoSpheres", "://resources/setupRenderOneSphere");  //dues esferes
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/cornell_box_geometry", "://resources/cornell_box_config_vis");  //mes esferes
    auto controller = make_shared<Controller>(Serializable::Json, "://resources/data10", "://resources/setupDataBCNOneValue");  //mes esferes
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/cube", "://resources/setupRenderOneSphere");  //mes esferes
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/data0", "://resources/setupRenderOneSphere");  //data0

    // Exemple d'escena de dades carregada des de json:
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/data0", "://resources/setupRenderTwoSpheres");

    //EN DADESBCNONEVALUE HEMOS CAMBIADO EL VALOR DE LA LINEA 35, DEBERIA SER METAL

    controller->start(argc, argv);

    return(0);
}
