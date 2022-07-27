#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 aNormal;
in vec4 vPos;

uniform sampler2D texture_diffuse1;

uniform vec3 lightPos;

void main() {
	// Ambient light
	vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);

	// Diffused light
	vec3 toLightDir = normalize(vec3(vPos) - lightPos);
	vec3 diffuseColour = vec3(1.f, 1.f, 1.f);
	float diffuse = clamp(dot(toLightDir, aNormal), 0, 1);
	vec3 diffuseFinal = diffuseColour * diffuse;

	FragColor = texture(texture_diffuse1, TexCoords) * (vec4(ambientLight, 1.f) + vec4(diffuseFinal, 1.f));
}
