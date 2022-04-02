#ifndef MATERIALTEXTURE_H
#define MATERIALTEXTURE_H

#include "Material.h"
#include "Texture.h"
#

class MaterialTexture: public Material
{
public:
    MaterialTexture();

private:
    shared_ptr<Texture> texture;
};

#endif // MATERIALTEXTURE_H
