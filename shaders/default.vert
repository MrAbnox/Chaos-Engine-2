#version 330 core
layout (location = 0) in vec3 vertex;
in vec3 colorIn;

out vec3 colorOut;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	colorOut = colorIn;
	
   vec4 pos = projection * view * model * vec4(vertex, 1.0);

   gl_Position = pos.xyww;
}  