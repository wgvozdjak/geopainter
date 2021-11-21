#include "pch.h"

#include "display.h"
#include "point.h"

namespace gp = geopainter;

gp::Point::Point(gp::Display* display, double x, double y, double z)
{
	display_ = display;
	x_ = x;
	y_ = y;
	z_ = z;
}

void gp::Point::draw()
{
	throw "geopainter::Point::draw() has not been implemented yet.";
}

void gp::Point::erase()
{
	throw "geopainter::Point::erase() has not been implemented yet.";
}

void gp::Point::translate(double dx, double dy, double dz)
{
	throw "geopainter::Point::translate(double dx, double dy, double dz) has not been implemented yet.";
}

void gp::Point::move(double x, double y, double z)
{
	throw "geopainter::Point::move(double x, double y, double z) has not been implemented yet.";
}

void gp::Point::rotate(double x, double y, double z, double angle)
{
	throw "geopainter::Point::rotate(double x, double y, double z, double angle) has not been implemented yet.";
}

void gp::Point::dilate(double scale_factor)
{
	throw "geopainter::Point::dilate(double scale_factor) has not been implemented yet.";
}
