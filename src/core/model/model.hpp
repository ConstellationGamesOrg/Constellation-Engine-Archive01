#ifndef MODEL_HPP
#define MODEL_HPP

#include <glad/glad.hpp> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../graphics/graphics.hpp"
#include "mesh.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

namespace CE {
    namespace core {
        unsigned int TextureFromFile(const char* path, const std::string& directory, bool flipTexture, bool gamma = false);

        class Model {
        public:
            // Model data
            std::vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
            std::vector<Mesh>    meshes;
            std::string directory;
            bool flipTexture;
            bool gammaCorrection;

            // Constructor, expects a filepath to a 3D model.
            Model(std::string const& path, bool flipTexture = false, bool gamma = false);

            // Draws the model, and thus all its meshes
            void Draw(CE::core::Shader& shader);

        private:
            // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
            void loadModel(std::string const& path);

            // Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
            void processNode(aiNode* node, const aiScene* scene);

            Mesh processMesh(aiMesh* mesh, const aiScene* scene);

            // Checks all material textures of a given type and loads the textures if they're not loaded yet.
            // The required info is returned as a Texture struct.
            std::vector<CE::core::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
        };
    }
}

#endif // MODEL_HPP