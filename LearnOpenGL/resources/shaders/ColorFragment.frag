#version 330 core
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform Material material; 
uniform Light light;

void main()
{
	vec3 diffuseTex = vec3(texture(material.diffuse, TexCoords));
	vec3 specularTex = vec3(texture(material.specular, TexCoords));

	// ambient
	vec3 ambient = light.ambient * diffuseTex;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * diffuseTex) * light.diffuse;

	// specular
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (specularTex * spec) * light.specular;

	vec3 result = (ambient + diffuse + specular);
	FragColor = vec4(result, 1.0);
}
