#version 410

uniform mat4 viewMat;
uniform sampler2D tex;

in VertexData
{
	vec3 fragCoord;
	vec3 normal;
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

void main()
{
	vec3 texColor = texture(tex, vertexData.texCoord).rgb;
	fragColor = vec4(texColor, 1.0);
}
