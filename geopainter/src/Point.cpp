#include "pch.h"
#include "include/geopainter.h"

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

// temporary functions to test drawing
double gp::Point::getX()
{
	return x_;
}

double gp::Point::getY()
{
	return y_;
}

double gp::Point::getZ()
{
	return z_;
}

void gp::Point::show()
{
	// project point into 2D
	std::pair<double, double> projected_point = display_->projectLocation(x_, y_, z_);

	// draw projected point to screen
	display_->showPoint(projected_point.first, projected_point.second);
}

/*void gp::Point::drawShape(CanvasRenderTarget^ render_target)
{

}*/
