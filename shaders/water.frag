#version 330 core
out vec4 FragColor;

in vec3 outNormal;
in vec2 outTextCoord;
in vec4 screenCoords;

uniform mat4 projection;
uniform sampler2D depthBuffer;

void main()
{
	vec3 waterColor = vec3(0.0f,0.37f,0.72f);
	vec3 foamColor = vec3(1.0f,1.0f,1.0f);

	mat4 invProj = inverse(projection);

	vec4 t = screenCoords / screenCoords.w;
	vec4 fragDepth = (invProj * t);

	float depth = texture(depthBuffer, t.xy * 0.5 + 0.5).x;
	depth = depth * 2 - 1;

	t.z = depth;

	vec4 textureDepth = (invProj * t);

	float depthDiff = length(textureDepth.xyz / textureDepth.w) - length(fragDepth.xyz / fragDepth.w);

	if(depthDiff < 0)
		discard;


	vec3 color = mix(foamColor, waterColor, smoothstep(0.1f, 0.5f, depthDiff));
	float alpha = smoothstep(0, 0.1f, depthDiff);
	FragColor = vec4(color, alpha);
}