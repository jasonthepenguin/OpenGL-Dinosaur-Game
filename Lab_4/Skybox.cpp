#include "Skybox.h"



Skybox::Skybox() : m_cubeMapLoaded(false)
{
    skyboxShader = std::make_unique<Shader>("shaders/skybox/skybox_vs.shader", "shaders/skybox/skybox_fs.shader");
}


void Skybox::loadCubemap(std::vector<std::string> faces)
{
    TextureFactory tf;
    tf.setTextureType(TextureType::TEXTURE_CUBE_MAP);
    auto texture = tf.createTexture();

    texture->setCubemapFileNames(faces);
    texture->load();

    m_cubeMapLoaded = true;
}