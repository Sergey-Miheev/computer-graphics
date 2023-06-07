#version 150

layout(lines) in;
layout(line_strip) out;
layout(max_vertices = 5) out;

in mat4 modelViewMatrix[];
in mat4 projectionMatrix[];

vec2 CalculateVectorCoords(float angle, float vecAngle, float size)
{
    float angleRadians = radians(angle) + vecAngle;
    return vec2(size * cos(angleRadians), size * sin(angleRadians));
}

void main()
{
    float arrowEndLenght = distance(gl_in[0].gl_Position, gl_in[1].gl_Position);
    float arrowSize = arrowEndLenght / 4;
    const float rightAngle = 165;
    const float leftAngle = 195;

    vec2 vecX = vec2(1, 0);
    vec2 vecArrow = normalize(gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy);

    float dotProductBetweenVecAndAbscissa = dot(vecX, vecArrow);

    float angleBetweenVecAndAbscissa = acos(dotProductBetweenVecAndAbscissa);

    if (gl_in[1].gl_Position.y < gl_in[0].gl_Position.y)
    {
        angleBetweenVecAndAbscissa = -angleBetweenVecAndAbscissa;
    }

    vec2 rightEdgeCoordinate = CalculateVectorCoords(rightAngle, angleBetweenVecAndAbscissa, arrowSize);
    vec2 leftEdgeCoordinate = CalculateVectorCoords(leftAngle, angleBetweenVecAndAbscissa, arrowSize);

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * (gl_in[1].gl_Position + vec4(leftEdgeCoordinate, 0, 0));
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = projectionMatrix[0] * modelViewMatrix[0] * (gl_in[1].gl_Position + vec4(rightEdgeCoordinate, 0, 0));
    EmitVertex();

    EndPrimitive();
}