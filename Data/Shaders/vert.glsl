#version 410

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

out vec4 ex_Color;
out vec3 Normal_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 Position_worldspace;
out vec3 EyeDirection_cameraspace;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;

void main()
{
	gl_Position = MVP * vec4(in_Position, 1.0);
	
	Position_worldspace = (M * vec4(in_Position, 1)).xyz;
	
	vec3 vertexPosition_cameraspace = (V * M * vec4(in_Position, 1)).xyz;
	EyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace;
	
	vec3 LightPosition_worldspace = vec3(0, 1, -1);
	vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	Normal_cameraspace = (V * M * vec4(in_Normal, 0)).xyz; // Heads up this totally breaks when scaling the model, ur meant to use the 'inverse transpose' but idk wtf that is :)
				 
	ex_Color = vec4(1.0, 1.0, 1.0, 1.0);
}