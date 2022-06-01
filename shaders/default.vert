#version 330 core
in vec3 vertex;
//in vec3 normal;
//in vec2 textCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
//	outNormal = normal;
//	outTextCoord = textCoord;

   vec4 pos = projection * view * model * vec4(vertex, 1.0);

   gl_Position = pos.xyww;
}  