#version 460 core

layout (location = 0) in vec4 aPos;

uniform mat4 projMatrix;


void main()
{
	gl_Position = projMatrix * aPos;
}

