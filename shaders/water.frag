#version 330 core
out vec4 FragColor;

in vec3 outNormal;
in vec2 outTextCoord;

uniform sampler2D depthBuffer;

void main()
{
	vec3 waterColor = vec3(0.0f,0.0f,1.0f);
	vec3 foamColor = vec3(1.0f,1.0f,1.0f);
	
	float depth = texture(depthBuffer, outTextCoord).x;
	//depth = depth * 2 - 1;

	float depthDiff = depth - gl_FragDepth;
	if(depthDiff > 0.2f )
	{
		FragColor = vec4(waterColor, 1.0f);
	}
	else
	{
		FragColor = vec4(foamColor, 1.0f);
	}
//	vec3 color = mix(foamColor, waterColor, smoothstep(-0.5f, 0.2f, depthDiff));
//	FragColor = vec4(color, 1.0f);
}