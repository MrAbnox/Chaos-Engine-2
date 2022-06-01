#version 460 
in vec3 vertex;
in vec3 normal;
in vec2 textCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 outNormal;
out vec2 outTextCoord;

void main()
{
	outTextCoord = textCoord;

   gl_Position = projection * view * model  * vec4(vertex, 1.0);
}  