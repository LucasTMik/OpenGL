#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_MVP;

out vec4 v_Color;
out float v_TexIndex;
out vec2 v_TexCoord;

void main()
{
	v_TexIndex = a_TexIndex;
	v_TexCoord = a_TexCoord;
	v_Color = vec4(a_Color.x, a_Color.y, a_Color.z, 1.0);
	gl_Position = u_MVP * vec4(position.x, position.y, 0.0, 1.0);
};