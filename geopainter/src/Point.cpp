#include "pch.h"
#include "include/geopainter.h"
#include "gatl/ga3e.hpp"

#include <math.h>

namespace gp = geopainter;

using namespace ga3e;

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
	double norm = rnorm(x * e1 + y * e2 + z * e3);
	x /= norm;
	y /= norm;
	z /= norm;
	auto axis = x * e1 + y * e2 + z * e3;

	auto pseudoscalar = e1 * e2 * e3;
	auto exponent = axis * pseudoscalar;

	auto left_multiply = cos(-1 * angle / 2) + exponent * sin(-1 * angle / 2);
	auto right_multiply = cos(angle / 2) + exponent * sin(angle / 2);

	auto current = x_ * e1 + y_ * e2 + z_ * e3;
	auto result = left_multiply * current * right_multiply;

	auto result_itr = result.values().begin();
	double result_x = *result_itr;
	result_itr++;
	double result_y = *result_itr;
	result_itr++;
	double result_z = *result_itr;

	x_ = result_x;
	y_ = result_y;
	z_ = result_z;
}

void gp::Point::dilate(double scale_factor)
{
	throw "geopainter::Point::dilate(double scale_factor) has not been implemented yet.";
}

// TODO: decide if these are needed
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

void gp::Point::show(CanvasDrawingSession^ current_drawing_session)
{
	// project point into 2D
	std::pair<double, double> projected_point = display_->projectLocation(x_, y_, z_);

	// draw projected point to screen
	display_->showPoint(projected_point.first, projected_point.second, current_drawing_session);
}

std::tuple<double, double, double> gp::Point::getLocation()
{
	return { x_, y_, z_ };
}
