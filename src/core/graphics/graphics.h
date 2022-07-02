#ifndef GRAPHICSH
#define GRAPHICSH

// CE
#include "../../util/util.h"

// Thirdparty
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct core_graphics_settings {
	int verMajor;
	int verMinor;
};

struct core_graphics_obj {
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	struct core_graphics_texture* texture;
};

struct core_graphics_shader {
	unsigned int ID;
};

struct core_graphics_texture {
	unsigned int ID;
};

// Functions
int core_graphics_setGlVer(struct core_graphics_settings* graphicsSettings, int verMajor, int verMinor);
int core_graphics_graphicsSettings(struct core_graphics_settings* graphicsSettings);

int core_graphics_createObj(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj, float vertices[], int verticesSize, unsigned int indices[], int indicesSize, char* vertPath, char* fragPath);
int core_graphics_render(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj);
int core_graphics_cleanup(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj);

void core_graphics_shader_create(struct core_graphics_shader* shaderObj, char* vertPath, char* fragPath);
void core_graphics_shader_use(struct core_graphics_shader* shaderObj);

void core_graphics_shader_setBool(char* name, bool value);
void core_graphics_shader_setInt(char* name, int value);
void core_graphics_shader_setFloat(char* name, float value);

void core_graphics_texture_create(struct core_graphics_texture* textureObj, char* filePath, int width, int height, int nrChannels, int hasAlpha);
void core_graphics_texture_apply(struct core_graphics_obj* graphicsObj, struct core_graphics_texture* textureObj);

#endif
