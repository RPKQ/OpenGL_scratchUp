#version 410

uniform mat4 viewMat;
uniform sampler2D tex;
uniform int useTex;

in VertexData
{
	vec3 fragCoord;
	vec3 normal;
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

void main()
{
	const vec3 grey = vec3(0.8, 0.8, 0.8); 
	vec3 texColor = texture(tex, vertexData.texCoord).rgb;

	vec3 result = (useTex == 1)? texColor : grey;
	fragColor = vec4(result, 1.0);
}
