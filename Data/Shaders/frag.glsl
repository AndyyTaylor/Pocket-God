#version 410

in vec2 ex_UV;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightPosition_worldspace;

out vec4 frag_Color;

uniform sampler2D tex;

void main()
{
	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);

	float cosTheta = clamp(dot(n, l), 0, 1);
	float distance = length(LightPosition_worldspace - Position_worldspace);

	vec4 LightColor = vec4(1.0, 1.0, 1.0, 1.0);
	float LightPower = 3000000;

	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E, R), 0, 1);

    vec4 ex_Color = texture(tex, ex_UV).rgba;
    // vec4 ex_Color = vec4(0.0, 1.0, 0.0, 1.0);

	vec3 ambientColor = vec3(0.5, 0.5, 0.5) * ex_Color.xyz;
	frag_Color = vec4(ambientColor, 0.0)  // Ambient lighting
				 + ex_Color * LightColor * LightPower * cosTheta / (distance*distance); // Diffuse lighting
				 + ex_Color * LightColor * LightPower * pow(cosAlpha, 5) / (distance*distance); // Specular lighting
    frag_Color.a = 1;   // FIX // Lol, can't remember what went wrong here
	//frag_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
