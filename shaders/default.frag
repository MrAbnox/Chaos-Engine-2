#version 330 core
out vec4 FragColor;
in vec3 colorOut;

out vec3 temp;

void main()
{
	temp = vec3(1.0f, 0.0f ,0.0f);
   FragColor = vec4(temp, 1.0f);
}