// Check if the point p is on the left side of the line p0p1
bool PointIsOnTheLeft(vec2 p0, vec2 p1, vec2 p)
{
	vec2 p0p1 = p1 - p0;
	// find the orthogonal vector to p0p1
	vec2 n = vec2(-p0p1.y, p0p1.x);

	// Find the dot product between n and (p - p0)
	return dot(p - p0, n) > 0.0;
}

bool PointIsInsideRectangle(vec2 p0, vec2 p1, vec2 p2, vec2 p3, vec2 p)
{
	return
		PointIsOnTheLeft(p0, p1, p) &&
		PointIsOnTheLeft(p1, p2, p) &&
		PointIsOnTheLeft(p2, p3, p) &&
		PointIsOnTheLeft(p3, p0, p);
}

void DrawRectangle(vec2 point, vec2 rectVertexes[])
{
	int size = 4;
	bool result = false;
	int j = size - 1;
	for (int i = 0; i < size; i++) {
		if ( (rectVertexes[i].y < point.y && rectVertexes[j].y >= point.y || rectVertexes[j].y < point.y && rectVertexes[i].y >= point.y) &&
         (rectVertexes[i].x + (point.y - rectVertexes[i].y) / (rectVertexes[j].y - rectVertexes[i].y) * (rectVertexes[j].x - rectVertexes[i].x) < point.X) )
        result = !result;
		j = i;
	}

	if (result)
	{
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else
	{
		// determine whether the texture coordinate 
		// is within a black or white check
		gl_FragColor = 1.0;
	}
}

void main()
{
	vec2 pos = gl_TexCoord[0].xy;

	vec2 p0 = vec2(0.2, 1.0);
	vec2 p1 = vec2(3.8, 1.0);
	vec2 p2 = vec2(3.8, 3.0);
	vec2 p3 = vec2(0.2, 3.0);

	vec2 rectVertexes[](vec2(0.2, 1.0), vec2(3.8, 1.0), vec2(3.8, 3.0), vec2(0.2, 3.0));

	DrawRectangle(pos, rectVertexes);

	p0 = vec2(0.0, 1.0);
	p1 = vec2(4.0, 1.0);
	p2 = vec2(4.0, 3.0);
	p3 = vec2(0.0, 3.0);
}