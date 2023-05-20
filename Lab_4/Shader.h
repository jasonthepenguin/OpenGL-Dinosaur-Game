#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
    unsigned int ID;

        /***********************************************************
         * @brief : Shader Constructor
         * @brief : A constructor for the shader class
         * 
         * @param :
         **********************************************************/
        
    Shader(const char* vertexPath, const char* fragmentPath);
    void setUpShaderProgram(unsigned int vertex, unsigned int shader);


        // activate the shader
        // ------------------------------------------------------------------------
    void use();
        // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 val);
    void setVec3(const std::string& name, float v1, float v2, float v3);


private:
        // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif