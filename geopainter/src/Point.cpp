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

void gp::Point::translate(double dx, double dy, double dz)
{
	x_ += dx;
	y_ += dy;
	z_ += dz;
}

void gp::Point::move(double x, double y, double z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

void gp::Point::rotate(double x, double y, double z, double angle)
{
	throw "geopainter::Point::rotate(double x, double y, double z, double angle) has not been implemented yet.";
}

void gp::Point::dilate(double scale_factor)
{
	throw "geopainter::Point::dilate(double scale_factor) has not been implemented yet.";
}
