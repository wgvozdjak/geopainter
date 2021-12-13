#include "pch.h"
#include "include/geopainter.h"

namespace gp = geopainter;

gp::Line::Line(Display* display, Point* p1, Point* p2)
{
	display_ = display;
	p1_ = p1;
	p2_ = p2;
}

void gp::Line::translate(double dx, double dy, double dz)
{
	p1_->translate(dx, dy, dz);
	p2_->translate(dx, dy, dz);
}

void gp::Line::move(double x, double y, double z)
{
	// FIGURE OUT IMPLEMENTATION OF THIS
	throw "geopainter::Line::move(double x, double y, double z) has not been implemented yet.";
}

void gp::Line::rotate(double x, double y, double z, double angle)
{
	throw "geopainter::Line::rotate(double x, double y, double z, double angle) has not been implemented yet.";
}

void gp::Line::dilate(double scale_factor)
{
	throw "geopainter::Line::dilate(double scale_factor) has not been implemented yet.";
}
