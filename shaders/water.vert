#version 330 core
in vec3 vertex;
in vec3 normal;
in vec2 textCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 outNormal;
out vec4 screenCoords;

out vec2 outTextCoord;

void main()
{
	outTextCoord = textCoord;

    vec4 t = (projection * view * model  * vec4(vertex, 1.0));
    gl_Position = t;

	screenCoords = t;
}  