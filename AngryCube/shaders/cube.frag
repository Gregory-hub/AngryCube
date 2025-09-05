#version 460 core

out vec4 outFragColor;

uniform vec4 vertexColor;


void main()
{
	outFragColor = vertexColor;
}

