#include "Scene.h"
#include <iostream>
Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}

// TODO: Fase ***
// Constructora a utilitzar quan s'inicialitza una escena amb un pla base o
// una esfera base
Scene::Scene(shared_ptr<Object> fp)
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}

/*
** TODO: FASE 1:
** Metode que testeja la interseccio contra tots els objectes de l'escena i retorna
** la que està més aprop del punt origen del raig
** Si un objecte es intersecat pel raig, el parametre  de tipus HitInfo conte
** la informació sobre la interseccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/

bool Scene::closestHit(Ray &raig, HitInfo& info) const {
    // TODO FASE 0 i FASE 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig.
    bool returnStatement = false;
    HitInfo newInfo;
    float closest_Hit = std::numeric_limits<float>::max();


    for(int i = 0; i < objects.size(); i++) {
        if(objects[i]->closestHit(raig, newInfo) and closest_Hit > newInfo.t) {
            closest_Hit = newInfo.t;
            info = newInfo;
            returnStatement = true;
        }
    }
    return returnStatement;
}
/*
** TODO: FASE 2:
** Metode que testeja la interseccio contra tots els objectes de l'escena i retorna
** true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hasHit (const Ray& raig) const {
    // Iteramos sobre todos los objetos para ver si hay intersección
    for (int i = 0; i < this->objects.size(); i++) {
        if (this->objects.at(i)->hasHit(raig)) {
           return true;
        }
    }
    return false;
}

// OPCIONAL:
// FASE 3: Mètode que retorna totes les interseccions que es troben al llarg del raig
//    virtual bool allHits(const Ray& r, vector<shared_ptr<HitInfo> infos) const { }



/*
** TODO: Funcio RayColor es la funcio recursiva del RayTracing.
** FASE 0 per a fer el degradat del fons
** FASE 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte
** TODO: Fase 2 de l'enunciat per incloure el shading (Blinn-Phong  i ombres)
** TODO: Fase 2 per a tractar reflexions i transparències
**
*/
#include <iostream>
vec3 Scene::RayColor (vec3 lookFrom, Ray &ray, int depth) {
    vec3 color;
    vec3 ray2;

    ray2 = normalize(ray.getDirection());
    // TODO: A canviar el càlcul del color en les diferents fases (via el mètode de shading)

    // Set color if we hit an object
    HitInfo info;
    if (this->closestHit(ray, info)) {
        //color = info.mat_ptr->Kd;             //FASE 0 material esfera
        //color = (info.normal + 1.0f)/ 2.0f;   //FASE 0 normal esfera
        //color = vec3(1,1,1) * (info.t/2.0f);    //FASE 0 distancia esfera
        color = this->shading(info, lookFrom);
        if (depth < MAXDEPTH) {
            Ray ref;
            info.mat_ptr->getOneScatteredRay(ray, info, ref);
            color += info.mat_ptr->getAttenuation(ray, info) * RayColor(lookFrom, ref, depth+1);
        }
    }
    // If we didn't hit any object, set color of the background
    else {
        float height = 0.5*(ray2.y +1);
        color = this->colorDown*(1-height) + this->colorTop*height;
    }

    return color;
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

void Scene::setBackground(bool background) {
    backgroundInRecurvise = background;
}

void Scene::setMAXDEPTH(int depth) {
    MAXDEPTH = depth;
}

void Scene::setDownBackground(vec3 color) {
    colorDown = color;
}

void Scene::setTopBackground(vec3 color) {
    colorTop = color;
}

/*
** TODO: Funcio shading es la funcio que calcula la il.luminació en un punt.
** FASE 0: Càlcul de la il.luminació segons la distànica del punt a l'observador
** FASE 1: Càlcul de la il.luminació en un punt (Blinn-Phong i ombres)
*/
vec3 Scene::shading(HitInfo& info, vec3 lookFrom) {
    vec3 ca = vec3(0, 0, 0);
    vec3 cd = vec3(0, 0, 0);
    vec3 cs = vec3(0, 0, 0);
    vec3 I = vec3(0, 0, 0);
    vec3 L, V, H;

    float attenuation, shadowFactor;

    /* Blinn-Phong
     * Itotal = Ia_Global * Ka + sum( atenuación * factorSombra * (difusa + especular) + ambiente
     */
    I += globalLight * info.mat_ptr->Ka;
    for (int i = 0; i < lights.size(); i++) {
        attenuation = 0.5 + 0.01*pow(lights[i]->distanceToLight(info.p), 2);
        //attenuation = lights[i]->attenuation(info.p);
        // Posición de luz
        L = lights[i]->vectorL(info.p);
        // Vector visión
        V = normalize(lookFrom-info.p);
        // H = (L + V ) / |(L + V)|
        H = normalize(L + V);
        shadowFactor = this->computeShadow(lights[i], info.p);
        // Componente ambiente
        ca = info.mat_ptr->Ka * lights[i]->getIa();
        // Componente difusa
        cd = info.mat_ptr->Kd * lights[i]->getId() * fmax(dot(L, info.normal), 0.0f);
        //Componente especular
        cs = info.mat_ptr->Ks * lights[i]->getIs() * pow(fmaxf(dot(info.normal, H), 0.0f), info.mat_ptr->shininess);

        I += shadowFactor / attenuation * (cd + cs) + ca;
    }
    return I;
}

/*
** TODO: Funcio RayColor es la funcio recursiva del RayTracing.
** FASE 1: Càlcul de la il.luminació en un punt (Blinn-Phong i ombres)
*/
float Scene::computeShadow(shared_ptr<Light> light, vec3 point) {
    float shadowFactor = 1.0f;
    Ray shadowRay(point, light->vectorL(point), 0.01f, light->distanceToLight(point));

    // Comprobamos si la luz llega a esta posición
    if (this->hasHit(shadowRay)) {
        shadowFactor = 0.0f;
    }

    return shadowFactor;
}

/*
 * TODO: FASE 2
 * incloure les llums a l'escena i la il.luminacio global
 * void setLights(std::vector<shared_ptr<Light>> lights) {}
 * void setGlobalLight(vec3 light);
 */

void Scene::setLights(std::vector<shared_ptr<Light>> lights) {
    this->lights = lights;
}

void Scene::setGlobalLight(vec3 light) {
    this->globalLight = light;
}




