#version 330

layout (location = 0) in vec3 Position;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 perspectMat;

void main()
{
    gl_Position = perspectMat * viewMat * modelMat * vec4(Position, 1.0);
    //gl_Position = viewMat * modelMat * vec4(Position, 1.0);
    //gl_Position = viewMat * vec4(Position, 1.0);
    //gl_Position = modelMat * vec4(Position, 1.0);
    //gl_Position = vec4(Position, 1.0);
}