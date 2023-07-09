#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 a_Color;

uniform mat4 u_MVP;

out vec4 v_Color;

void main()
{
	v_Color = vec4(a_Color.x, a_Color.y, a_Color.z, 1.0);
	gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1.0);
};