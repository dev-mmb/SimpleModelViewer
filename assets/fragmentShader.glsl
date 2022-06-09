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

struct PointLight {
	vec3 pos;
	float constant;
	float linear;
	float quadratic;
	vec3 color;
};

struct Material {
	float specularIntensity;
	float shine;
};

uniform sampler2D tex;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 viewPosition;
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec4 calcDirLight(DirectionalLight light, vec3 n); 
vec4 calcPointLight(PointLight light, vec3 n, vec3 fPos);  

void main()
{
	vec4 result = calcDirLight(directionalLight, normal);
	
	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		result += calcPointLight(pointLights[i], normal, fragPos);
	}

    color = texture(tex, texCoord) * result;
}

vec4 calcLight(vec3 color, vec3 direction, float ambientIntensity, float diffuseIntensity, float specularIntensity, vec3 normal, float shine) 
{
	vec4 ambientColor = vec4(color, 1.0f) * ambientIntensity;
		float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
		vec4 diffuseColor = vec4(color, 1.0f) * diffuseIntensity * diffuseFactor;
		vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

		if (diffuseFactor > 0.0f) {
			vec3 viewDirection = normalize(viewPosition - fragPos);
			vec3 reflectDirection = normalize(reflect(direction, normalize(normal)));
			float specularFactor = dot(viewDirection, reflectDirection);

			if (specularFactor > 0.0f) {
				specularFactor = pow(specularFactor, shine);
				specularColor = vec4(color * specularIntensity * specularFactor, 1.0f);
			}
		}
		return (ambientColor + diffuseColor + specularColor);
}

vec4 calcDirLight(DirectionalLight light, vec3 n) 
{
	return calcLight(light.color, light.direction, light.ambientIntensity, light.diffuseIntensity, material.specularIntensity, n, material.shine);
}

vec4 calcPointLight(PointLight light, vec3 n, vec3 fPos)
{
    vec3 direction = fPos - light.pos;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 color = calcLight(light.color, direction, 1, 1, 1, n, material.shine);
	float attenuation = ( light.quadratic * distance * distance) + (light.linear * distance) + light.constant;
	return (color / attenuation);
} 