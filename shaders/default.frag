#version 330 core
out vec4 FragColor;

in vec3 outNormal;
in vec2 outTextCoord;

uniform sampler2D  textureImage1;

void main()
{
   FragColor = texture(textureImage1, outTextCoord);
}