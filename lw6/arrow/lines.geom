#version 150

layout(lines) in;
layout(line_strip) out;
layout(max_vertices = 6) out;

in mat4 modelViewMatrix[];
in mat4 projectionMatrix[];

void main()
{

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * (gl_in[1].gl_Position + vec4(-0.5, -0.5, 0, 0));
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * (gl_in[1].gl_Position + vec4(-0.5, 0.5, 0, 0));
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * (gl_in[1].gl_Position + vec4(-0.2, -0.5, 0, 0));
    EmitVertex();

    EndPrimitive();
}