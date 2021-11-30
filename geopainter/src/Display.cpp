#include "pch.h"

#include "display.h"
#include "point.h"

namespace gp = geopainter;

gp::Display::Display(CanvasDrawingSession^ drawing_session)
{
	drawing_session_ = drawing_session;
}

gp::Point* gp::Display::createPoint(double x, double y, double z)
{
	gp::Point* point = new gp::Point(this, x, y, z);
	return point;
}
