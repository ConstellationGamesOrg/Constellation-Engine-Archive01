// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#include "graphics.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.hpp>

namespace CE {
	namespace core {
		int Graphics::create() {
			if (!glfwInit()) {
				// Failed to initialize GLFW
				return -1;
			}

			// Set the OpenGL version
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

			// Use only modern OpenGL functions
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

			return 0;
		}
		int Graphics::create(int versionMajor, int versionMinor) {
			if (!glfwInit()) {
				// Failed to initialize GLFW
				return -1;
			}

			// Set the OpenGL version
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);

			// Use only modern OpenGL functions
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

			return 0;
		}

		Object::Object(std::vector<float> vertices, bool normal, bool texture) {
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);

			// VBO
			// Copy our vertices array in a buffer for OpenGL to use
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), &vertices.front(), GL_STATIC_DRAW); // https://stackoverflow.com/questions/7173494/vbos-with-stdvector
			// GL_STATIC_DRAW: Data will be modified once and used many times
			// GL_DYNAMIC_DRAW: Data will be modified repeatedly and used many times
			// GL_STREAM_DRAW: Data will be modified once and used at most a few times


			// VAO
			// Bind the Vertex Array Object first, then set vertex buffer(s), and then configure vertex attributes(s)
			glBindVertexArray(VAO);

			// Then set our vertex attributes pointers
			if (normal == true && texture == true)
			{
				// Position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// Normal attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);
				// Texture attribute
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);
			}
			else if (normal == true)
			{
				// Position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// Normal attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);
			}
			else if (texture == true)
			{
				// Position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// Texture attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);
			}
			

			// Unbind VAO (It's always a good thing to unbind any buffer/array to prevent strange bugs)
			glBindVertexArray(0);
		}

		// Constructor generates the shader on the fly
		// ------------------------------------------------------------------------
		Shader::Shader(const char* vertexPath, const char* fragmentPath) {
			// 1. Retrieve the vertex/fragment source code from filePath
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;
			// Ensure ifstream objects can throw exceptions:
			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try {
				// Open files
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				std::stringstream vShaderStream, fShaderStream;
				// Read file's buffer contents into streams
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();
				// Close file handlers
				vShaderFile.close();
				fShaderFile.close();
				// Convert stream into string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			}
			catch (std::ifstream::failure& e) {
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;

				std::cout << "Assuming file passed, not file path...\n" << "\n -- --------------------------------------------------- -- " << std::endl;
				vertexCode = vertexPath;
				fragmentCode = fragmentPath;
			}
			const char* vShaderCode = vertexCode.c_str();
			const char* fShaderCode = fragmentCode.c_str();
			// 2. Compile shaders
			unsigned int vertex, fragment;
			// Vertex shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);
			checkCompileErrors(vertex, "VERTEX");
			// Fragment shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			checkCompileErrors(fragment, "FRAGMENT");
			// Shader program
			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);
			checkCompileErrors(ID, "PROGRAM");
			// Delete the shaders as they're linked into our program now and no longer necessary
			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}

		Shader::~Shader()
		{
			glDeleteProgram(ID);
		}



		// Activate the shader
		// ------------------------------------------------------------------------
		void Shader::use() const {
			glUseProgram(ID);
		}



		// Utility uniform functions
		// ------------------------------------------------------------------------
		void Shader::setBool(const std::string& name, bool value) const {
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
		}
		// ------------------------------------------------------------------------
		void Shader::setInt(const std::string& name, int value) const {
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}
		// ------------------------------------------------------------------------
		void Shader::setFloat(const std::string& name, float value) const {
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}
		// ------------------------------------------------------------------------
		void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
			glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		void Shader::setVec2(const std::string& name, float x, float y) const {
			glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
		}
		// ------------------------------------------------------------------------
		void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		void Shader::setVec3(const std::string& name, float x, float y, float z) const {
			glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
		}
		// ------------------------------------------------------------------------
		void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
			glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
			glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
		}
		// ------------------------------------------------------------------------
		void Shader::setMat2(const std::string& name, const glm::mat2& mat) const {
			glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
			glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}



		// Utility function for checking shader compilation/linking errors.
		// ------------------------------------------------------------------------
		void Shader::checkCompileErrors(unsigned int shader, std::string type) {
			int success;
			char infoLog[1024];
			if (type != "PROGRAM") {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
				}
			}
			else {
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
				}
			}
		}

		void Texture::loadTexture(const char* path) {
			stbi_set_flip_vertically_on_load(true);
			unsigned int textureID;
			glGenTextures(1, &textureID);

			int width, height, nrComponents;
			unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
			if (data) {
				GLenum format;
				if (nrComponents == 1)
					format = GL_RED;
				else if (nrComponents == 3)
					format = GL_RGB;
				else if (nrComponents == 4)
					format = GL_RGBA;

				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_image_free(data);
			}
			else {
				std::cout << "Texture failed to load at path: " << path << std::endl;
				stbi_image_free(data);
			}
		}

		void Object::translate(glm::vec3 newPosition) {
			model = glm::translate(model, position = newPosition);
		}

		void Object::translate(glm::vec3 newPosition, float deltaTime) {
			float velocity = movementSpeed * deltaTime;
			model = glm::translate(model, position += newPosition * velocity);
		}

		void Object::rotate(float angle, glm::vec3 axis) {
			model = glm::rotate(model, glm::radians(angle), axis);
		}

		void Object::set(CE::core::Shader* shader) {
			shader->setMat4("model", model);
			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
		}

		void Object::draw() {
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		Object::~Object()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
	}
}