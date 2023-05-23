#include "Skybox.h"



Skybox::Skybox() : m_cubeMapLoaded(false)
{

    // Setting up the shader
    skyboxShader = std::make_unique<Shader>("shaders/skybox/skybox_vs.shader", "shaders/skybox/skybox_fs.shader");
    skyboxShader->use();
    skyboxShader->setInt("skybox", 0);

    // Skybox vertices
    skyboxVertices = { -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f }; // 36 vertices here 

    // Set up vertex data VBO, VAO
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), skyboxVertices.data(), GL_STATIC_DRAW);

    // Current Frame Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    skyboxVertices.clear();

}


void Skybox::loadCubemap(std::vector<std::string> faces)
{
    TextureFactory tf;
    tf.setTextureType(TextureType::TEXTURE_CUBE_MAP);
   // auto texture = tf.createTexture();
    texture = tf.createTexture();

   // std::cout << "THE TEXTURE TYPE IS : " << texture->getTextureType() << std::endl;

    texture->setCubemapFileNames(faces);
    texture->load();

    m_cubeMapLoaded = true;
}





void Skybox::Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection)
{
    // remove the translation section of transformation matrices by taking the upper-left 3x3 matrix of the 4x4 matrix. 
    //We can achieve this by converting the view matrix to a 3x3 matrix (removing translation) and converting it back to a 4x4 matrix:
    glm::mat4 newView = glm::mat4(glm::mat3(view)); // if getting issues, then caller of this function can do same operation but on cameras view mat


    skyboxShader->use();
    
    skyboxShader->setMat4("view", newView);
    skyboxShader->setMat4("projection", projection);

    glm::mat4 model = glm::mat4(1.0f);
    skyboxShader->setMat4("model", model);


    glBindVertexArray(VAO);
        glDepthMask(GL_FALSE);
        texture->bindTexture(0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
    glBindVertexArray(0);
        






}