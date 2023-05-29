#version 150

layout(lines) in;
layout(line_strip) out;
layout(max_vertices = 5) out;

void main()
{
    if (gl_in[1].gl_Position.y < gl_in[0].gl_Position.y)
    {
        vecAngle = -vecAngle;
    }

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * (gl_in[1].gl_Position + vec4(0.5, 0, 0, 0));
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * (gl_in[1].gl_Position + vec4(rightArrowCoordinate.xy, 0, 0));
    EmitVertex();

    EndPrimitive();
}