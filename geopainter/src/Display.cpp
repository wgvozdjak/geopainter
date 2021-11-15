#include <src/Display.h>

namespace gp = geopainter;

gp::Point* gp::Display::createPoint(double x, double y, double z)
{
	gp::Point* point = new gp::Point();
	return point;
}