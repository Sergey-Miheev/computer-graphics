#version 130

out mat4 modelViewMatrix;
out mat4 projectionMatrix;

void main()
{
	gl_Position = gl_Vertex;
	modelViewMatrix = gl_ModelViewMatrix;
	projectionMatrix = gl_ProjectionMatrix;
}