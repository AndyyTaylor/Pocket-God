#version 410

in vec4 ex_Color;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;

out vec4 frag_Color;

void main()
{
	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);

	float cosTheta = clamp(dot(n, l), 0, 1);
	float distance = length(vec3(0.0, 1.0, -1.0) - Position_worldspace);

	vec4 LightColor = vec4(1.0, 1.0, 1.0, 1.0);
	float LightPower = 15;

	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E, R), 0, 1);

	vec3 ambientColor = vec3(0.2, 0.2, 0.2) * ex_Color.xyz;
	frag_Color = vec4(ambientColor, 0.0)  // Ambient lighting
				 + ex_Color * LightColor * LightPower * cosTheta / (distance*distance); // Diffuse lighting
				 + ex_Color * LightColor * LightPower * pow(cosAlpha, 5) / (distance*distance); // Specular lighting
	//frag_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
