#version 410

in vec4 ex_Color;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 Position_worldspace;

out vec4 frag_Color;

void main()
{
	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);
	
	
	float cosTheta = clamp(dot(n, l), 0, 1);
	float distance = length(vec3(0.0, 1.0, -1.0) - Position_worldspace);
	
	vec4 LightColor = vec4(1.0, 1.0, 1.0, 1.0);
	float LightPower = 2;
	
	
	frag_Color = vec4(0.0, 0.0, abs(dot(n, l)), 1.0);
	if (dot(n, l) < 0) frag_Color = vec4(1.0, 0.0, 0.0, 1.0);
	else if (dot(n, l) == 0) frag_Color = vec4(0.0, 1.0, 0.0, 1.0);
	
	vec3 ambientColor = vec3(0.2, 0.2, 0.2) * ex_Color.xyz;
	frag_Color = vec4(ambientColor, 0.0) + ex_Color * LightColor * LightPower * cosTheta / (distance*distance);
	//frag_Color = vec4(1.0, 1.0, 1.0, 1.0);
}