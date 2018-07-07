#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blend;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x * -1.0, TexCoord.y)), blend);
	//FragColor = vec4(lightColor * objectColor, 1.0) * mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x * -1.0, TexCoord.y)), blend);
	FragColor = vec4(lightColor * objectColor, 1.0);
}
