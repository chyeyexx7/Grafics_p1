#include "RayTracing.h"

// Metode raytracing principal

// Aquesta funcio transforma cada pixel a coordenades de mon, construeix el raig,
// envia el raig des de la camera en aquella direccio cridant al metode RayColor
// per acabar pintant la imatge final:

//Precondicio:
// La Scene ha d'estar creada i inicialitzada

// TO DO: Fase 2: A retocar per a aconseguir imatges sense aliasing

void RayTracing::rendering() {
    // Recorregut de cada pixel de la imatge final

    for (int y = cam->viewportY-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < cam->viewportX; x++) {

            vec3 col(0, 0, 0);

            // Antialiasing x10
            for (int i = 0; i < maxNumSamples; i++){
                float u = (float(x) + glm::linearRand(-0.5f, 0.5f)) / float(cam->viewportX);
                float v = (float(y) + glm::linearRand(-0.5f, 0.5f)) / float(cam->viewportY);

                Ray r = cam->getRay(u, v);

                col += scene->RayColor(cam->getLookFrom(), r, 0);
            }
            col /= maxNumSamples;
            // Poner los colores en rango [0,1]
            col = glm::clamp(col, 0, 1);
            // Gamma correction
            col = sqrt(col);
            setPixelColor(col, x, y);
        }
    }
    std::cerr << "\nDone.\n";
}

void RayTracing::exitRender() {

}

// Metode de suport que fa el rendering per a tots els Renders que no usen GLUT
void RayTracing::startRendering(int argc, char **argv) {
    renderingScene();
}

void RayTracing::renderingScene()  {
    initRender(filename.toStdString());
    rendering();
    exitRender();
}

void RayTracing::setCamera(shared_ptr<Camera> c) {
    cam = c;
}
void RayTracing::setScene(shared_ptr<Scene> s) {
    scene = s;
}

void RayTracing::setOutputFile(QString output) {
    filename = output;
}



