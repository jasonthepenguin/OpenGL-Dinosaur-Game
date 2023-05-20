#include "Skybox.h"


void Skybox::loadCubemap(std::vector<std::string> faces)
{
    TextureFactory tf;
    tf.setTextureType(TextureType::TEXTURE_CUBE_MAP);
    auto texture = tf.createTexture();

    texture->setCubemapFileNames(faces);
    texture->load();
}