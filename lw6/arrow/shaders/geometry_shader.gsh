#version 150

layout(lines) in;
layout(line_strip) out;
layout(max_vertices = 5) out;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4(-0.5, 0.5, 0, 0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4(-0.5, -0.5, 0, 0);
    EmitVertex();

    EndPrimitive();
}