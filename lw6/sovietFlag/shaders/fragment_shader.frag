bool LocatedInCanvas(vec2 point, vec2 rectVertexes[4])
{
	int size = 4;
	bool isLocated = false;
	int j = size - 1;
	for (int i = 0; i < size; i++) {
		if ((rectVertexes[i].y < point.y && rectVertexes[j].y >= point.y || rectVertexes[j].y < point.y && rectVertexes[i].y >= point.y) && 
		(rectVertexes[i].x + (point.y - rectVertexes[i].y) / (rectVertexes[j].y - rectVertexes[i].y) * (rectVertexes[j].x - rectVertexes[i].x) < point.x))
		{
			isLocated = !isLocated;
		}
		j = i;
	}
	return isLocated;
}

bool LocatedInStar(vec2 centerCoord, float smallCircleRadius, float bigCircleRadius, vec2 point)
{
	#define M_PI 3.1415926535897932384626433832795
	vec2 starVertexes[10];

	// up vertex
	starVertexes[0] = vec2(centerCoord.x, centerCoord.y + bigCircleRadius);
	// the subsequent ones are ccw
	starVertexes[1] = vec2(centerCoord.x + smallCircleRadius * cos(126*M_PI/180), centerCoord.y + smallCircleRadius * sin(126*M_PI/180));
	starVertexes[2] = vec2(centerCoord.x + bigCircleRadius * cos(162*M_PI/180), centerCoord.y + bigCircleRadius * sin(162*M_PI/180));
	starVertexes[3] = vec2(centerCoord.x + smallCircleRadius * cos(198*M_PI/180), centerCoord.y + smallCircleRadius * sin(198*M_PI/180));
	starVertexes[4] = vec2(centerCoord.x + bigCircleRadius * cos(234*M_PI/180), centerCoord.y + bigCircleRadius * sin(234*M_PI/180));
	starVertexes[5] = vec2(centerCoord.x, centerCoord.y - smallCircleRadius);
	starVertexes[6] = vec2(centerCoord.x + bigCircleRadius * cos(306*M_PI/180), centerCoord.y + bigCircleRadius * sin(306*M_PI/180));
	starVertexes[7] = vec2(centerCoord.x + smallCircleRadius * cos(342*M_PI/180), centerCoord.y + smallCircleRadius * sin(342*M_PI/180));
	starVertexes[8] = vec2(centerCoord.x + bigCircleRadius * cos(18*M_PI/180), centerCoord.y + bigCircleRadius * sin(18*M_PI/180));
	starVertexes[9] = vec2(centerCoord.x + smallCircleRadius * cos(54*M_PI/180), centerCoord.y + smallCircleRadius * sin(54*M_PI/180));
	int size = 10;
	bool isLocated = false;
	int j = size - 1;
	for (int i = 0; i < size; i++) {
		if ((starVertexes[i].y < point.y && starVertexes[j].y >= point.y || starVertexes[j].y < point.y && starVertexes[i].y >= point.y) && 
		(starVertexes[i].x + (point.y - starVertexes[i].y) / (starVertexes[j].y - starVertexes[i].y) * (starVertexes[j].x - starVertexes[i].x) < point.x))
		{
			isLocated = !isLocated;
		}
		j = i;
	}
	return isLocated;
}

bool LocatedInHammer(vec2 startCoord, vec2 point)
{
	vec2 hammerVertexes[8];

	// bottom of the hammer base
	hammerVertexes[0] = vec2(startCoord.x, startCoord.y);
	// the subsequent ones are ccw
	hammerVertexes[1] = vec2(startCoord.x - 0.05, startCoord.y - 0.04);
	hammerVertexes[2] = vec2(startCoord.x - 0.1, startCoord.y + 0.02);
	hammerVertexes[3] = vec2(startCoord.x + 0.02, startCoord.y + 0.11);
	hammerVertexes[4] = vec2(startCoord.x + 0.1, startCoord.y + 0.07);
	hammerVertexes[5] = vec2(startCoord.x + 0.03, startCoord.y + 0.02);
	hammerVertexes[6] = vec2(startCoord.x + 0.33, startCoord.y - 0.26);
	hammerVertexes[7] = vec2(startCoord.x + 0.3, startCoord.y - 0.29);

	int size = 8;
	bool isLocated = false;
	int j = size - 1;
	for (int i = 0; i < size; i++) {
		if ((hammerVertexes[i].y < point.y && hammerVertexes[j].y >= point.y || hammerVertexes[j].y < point.y && hammerVertexes[i].y >= point.y) && 
		(hammerVertexes[i].x + (point.y - hammerVertexes[i].y) / (hammerVertexes[j].y - hammerVertexes[i].y) * (hammerVertexes[j].x - hammerVertexes[i].x) < point.x))
		{
			isLocated = !isLocated;
		}
		j = i;
	}
	return isLocated;
}

bool LocatedInSickle(vec2 centerCoords, float angle, vec2 point, float a, float b)
{
	#define M_PI 3.1415926535897932384626433832795

	angle = angle * M_PI / 180;

    float p = (pow(cos(angle)*(point.x - centerCoords.x) + sin(angle)*(point.y - centerCoords.y), 2) / pow(a, 2))
            + (pow(sin(angle)*(point.x - centerCoords.x) - cos(angle)*(point.y - centerCoords.y), 2) / pow(b, 2));
 
    return p <= 1;
}

bool LocatedOutsideHandle(vec2 centerCoords, vec2 point, float a, float b)
{
    const int size = 5;
	vec2 rectVertexes[size];
	// down left
	rectVertexes[0] = vec2(centerCoords.x - b, centerCoords.y - b);
	// the subsequent ones are ccw
	rectVertexes[1] = vec2(centerCoords.x - 0.74*b, centerCoords.y - 0.95*b);
	rectVertexes[2] = vec2(centerCoords.x - 0.57*b, centerCoords.y - 0.7*b);
	rectVertexes[3] = vec2(centerCoords.x - 0.33*b, centerCoords.y + 0.4*a);
	rectVertexes[4] = vec2(centerCoords.x - 2*b, centerCoords.y + 0.4*a);

	bool isLocated = false;
	int j = size - 1;

	for (int i = 0; i < size; i++) {
		if ((rectVertexes[i].y < point.y && rectVertexes[j].y >= point.y || rectVertexes[j].y < point.y && rectVertexes[i].y >= point.y) && 
		(rectVertexes[i].x + (point.y - rectVertexes[i].y) / (rectVertexes[j].y - rectVertexes[i].y) * 
		(rectVertexes[j].x - rectVertexes[i].x) < point.x))
		{
			isLocated = !isLocated;
		}
		j = i;
	}
	return isLocated;
}

bool LocatedInSickleHandle(vec2 centerCoords, vec2 point, float a, float b)
{
    const int size = 6;
	vec2 rectVertexes[size];
	rectVertexes[0] = vec2(centerCoords.x - b*0.80, centerCoords.y - 0.6*b);
	rectVertexes[1] = vec2(centerCoords.x - b*0.76, centerCoords.y - 0.54*b);
	rectVertexes[2] = vec2(centerCoords.x - b*0.64, centerCoords.y - 0.8*b);
	rectVertexes[3] = vec2(centerCoords.x - b*0.68, centerCoords.y - 0.84*b);
	rectVertexes[4] = vec2(centerCoords.x - b*1.15, centerCoords.y - b*1.25);
	rectVertexes[5] = vec2(centerCoords.x - b*1.32, centerCoords.y - b*1.22);

	bool isLocated = false;
	int j = size - 1;

	for (int i = 0; i < size; i++) {
		if ((rectVertexes[i].y < point.y && rectVertexes[j].y >= point.y || rectVertexes[j].y < point.y && rectVertexes[i].y >= point.y) && 
		(rectVertexes[i].x + (point.y - rectVertexes[i].y) / (rectVertexes[j].y - rectVertexes[i].y) * (rectVertexes[j].x - rectVertexes[i].x) < point.x))
		{
			isLocated = !isLocated;
		}
		j = i;
	}

	//vec2 ellipseCenter = vec2(centerCoords.x - b*1.32, centerCoords.y - b*1.22);
	vec2 ellipseCenter = vec2(centerCoords.x - 0.22, centerCoords.y - 0.22);
	float aSmall = 0.06;
	float bSmall = 0.03;
	float angle = 228.0;

	return (isLocated || LocatedInSickle(ellipseCenter, angle, point, aSmall, bSmall));
}

void FillPoint(vec2 point, vec2 rectVertexes[4], vec2 starCenterCoord, float smallCircleRadius, float bigCircleRadius, 
			   vec2 hammerStartCoord, vec2 biggerEllipseCenter, float biggerEllipseRotateAngle, float biggerLargeSemiaxis, 
			   float biggerSmallSemiaxis, vec2 smallerEllipseCenter, float smallerEllipseRotateAngle, float smallerElargeSemiaxis, 
			   float smallerSmallSemiaxis)
{
	// flag canvas
	if (LocatedInCanvas(point, rectVertexes))
	{
		// red color
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
		// flag star
		if (LocatedInStar(starCenterCoord, smallCircleRadius, bigCircleRadius, point))
		{
			// yellow color
			gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
			if (LocatedInStar(starCenterCoord, smallCircleRadius-0.022, bigCircleRadius-0.022, point))
			{
				// red color of internal star
				gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
			}
		}
		else if (LocatedInSickle(biggerEllipseCenter, biggerEllipseRotateAngle, point, biggerLargeSemiaxis, biggerSmallSemiaxis) ||
				 LocatedInSickleHandle(biggerEllipseCenter, point, biggerLargeSemiaxis, biggerSmallSemiaxis))
		{
			// yellow color of external sickle
			gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
			if (LocatedInSickle(smallerEllipseCenter, smallerEllipseRotateAngle, point, smallerElargeSemiaxis, smallerSmallSemiaxis) ||
				LocatedOutsideHandle(smallerEllipseCenter, point, smallerElargeSemiaxis, smallerSmallSemiaxis))
			{
				// red color of internal sickle
				gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
			}

			
		}
		if (LocatedInHammer(hammerStartCoord, point))
		{
			// yellow color of hammer
			gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
		}
	}
	else
	{
		// white color
		gl_FragColor = 1.0;
	}
}

void main()
{
	vec2 pos = gl_TexCoord[0].xy;

	vec2 canvasVertexes[4];
	canvasVertexes[0] = vec2(0.2, 1.0);
	canvasVertexes[1] = vec2(3.8, 1.0);
	canvasVertexes[2] = vec2(3.8, 3.0);
	canvasVertexes[3] = vec2(0.2, 3.0);

	// info about star
	float smallCircleRadius = 0.05;
	float bigCircleRadius = 0.14;
	vec2 starCenterCoord = vec2(1.7, 2.64);

	// info about hammer
	vec2 hammerStartCoord = vec2(0.62, 2.3);

	// info about bigger ellipse
	//float biggerLargeSemiaxis = 0.24, biggerSmallSemiaxis = 0.18, biggerllipseRotateAngle = 128.0;
	float biggerLargeSemiaxis = 0.26, biggerSmallSemiaxis = 0.20, biggerllipseRotateAngle = 128.0;
	vec2 biggerEllipseCenter = vec2(0.7, 2.25);

	// info about smaller ellipse
	float smallerLargeSemiaxis = 0.24, smallerSmallSemiaxis = 0.17, smallerllipseRotateAngle = 125.0;
	vec2 smallerEllipseCenter = vec2(0.67, 2.27);

	FillPoint(pos, canvasVertexes, starCenterCoord, smallCircleRadius, bigCircleRadius, hammerStartCoord, 
			  biggerEllipseCenter, biggerllipseRotateAngle, biggerLargeSemiaxis, biggerSmallSemiaxis, smallerEllipseCenter, 
			  smallerllipseRotateAngle, smallerLargeSemiaxis, smallerSmallSemiaxis );
}