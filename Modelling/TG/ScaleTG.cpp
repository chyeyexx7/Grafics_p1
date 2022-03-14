#include "ScaleTG.h"

ScaleTG::ScaleTG(glm::vec3 scale): scalation(scale){
    matTG = glm::scale(glm::mat4(1.0f), scale);
}
ScaleTG::ScaleTG(float scale)
{
    escala = scale;
    matTG = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
}

ScaleTG::~ScaleTG()
{

}
