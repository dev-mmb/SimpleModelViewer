#version 330

out vec4 color;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

struct DirectionalLight {
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct Material {
	float specularIntensity;
	float shine;
	float value;
};

uniform sampler2D tex;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 viewPosition;

void main()
{
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;

	float diffuseFactor = max(dot(normalize(normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	if (diffuseFactor > 0.0f) {
		vec3 viewDirection = normalize(viewPosition - fragPos);
		vec3 reflectDirection = normalize(reflect(directionalLight.direction, normalize(normal)));
		float specularFactor = dot(viewDirection, reflectDirection);

		if (specularFactor > 0.0f) {
			specularFactor = pow(specularFactor, material.shine);
			specularColor = vec4(directionalLight.color * material.specularIntensity * specularFactor, 1.0f);
		}
	}

    color = texture(tex, texCoord) * (ambientColor + diffuseColor + specularColor) * material.value;
}