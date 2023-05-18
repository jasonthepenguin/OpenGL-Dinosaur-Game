#pragma once

#include "Mesh.h"
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


// replace opengl texture code with texture class
#include "stb_image.h"


/******************************************************************************************************************************************
 * @class   : Model
 * @brief   : A model class which is utiliozed for controlling and drawing assset models
 * 
 * @author  : Jason
 * @date    : April 2023
 * @version : 1.0
 ******************************************************************************************************************************************/
				
class Model
{
    public:

            /*******************************************************************
             * @brief : Model Constructor
             * @brief : Uses the file path of the model
             * 
             * @param : path - file path std::string
             ******************************************************************/

        Model(std::string path);


            /*******************************************************************
             * @brief : Draw Constructor
             * @brief : Used to draw the game object 
             * 
             * @param : Shader - shader
             ******************************************************************/

        void Draw(Shader& shader);

    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<m_Texture> textures_loaded;



            /*******************************************************************
             * @brief : loadModel
             * @brief : is utilized when loading in a game model
             * 
             * @param : path - std::string
             ******************************************************************/

        void loadModel(std::string path);

            /*******************************************************************
             * @brief : processNode
             * @brief : is utilized to process a node within the mesh
             * 
             * @param : node  - aiNode 
             * @param : scene - const aiScene object
             ******************************************************************/

        void processNode(aiNode* node, const aiScene* scene);


            /*******************************************************************
             * @brief : processMesh
             * @brief : is utilized to process a mesh
             * 
             * @param : mesh  - aiMesh* 
             * @param : scene - const aiScene object
             ******************************************************************/

        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        std::vector<m_Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);


            /*******************************************************************
             * @brief : TextureFromFile
             * @brief : is used to read a texture from a file
             * 
             * @param : path      - const char* 
             * @param : directory - const std::string 
             *******************************************************************/

        unsigned int TextureFromFile(const char* path, const std::string& directory);
};