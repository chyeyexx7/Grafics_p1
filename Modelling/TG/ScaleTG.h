#ifndef SCALE_H
#define SCALE_H
#include "TG.h"
class ScaleTG : public TG
{
public:
    glm::vec3 scalation;
    float escala;
    ScaleTG(glm::vec3 scale);
    ScaleTG(float esc);
    ~ScaleTG();

};
#endif // SCALE_H
