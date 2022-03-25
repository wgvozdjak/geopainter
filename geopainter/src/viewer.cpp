#include "pch.h"
#include "include/geopainter.h"
#include "gatl/ga3e.hpp"

#include <math.h>

namespace gp = geopainter;

using namespace ga3e;

gp::Viewer::Viewer()
{
	x_ = 2.0;
	y_ = 2.0;
	z_ = -7.75;

	plane_point_1_ = { 0, 0, 0 };
	plane_point_2_ = { 1, 0, 0 };
	plane_point_3_ = { 0, 1, 0 };
}

std::tuple<double, double, double> gp::Viewer::rotateLocation(
	std::tuple<double, double, double> point,
	std::tuple<double, double, double> axis_vector,
	double angle
)
{
	double x = std::get<0>(axis_vector);
	double y = std::get<1>(axis_vector);
	double z = std::get<2>(axis_vector);

	double norm = rnorm(x * e1 + y * e2 + z * e3);
	x /= norm;
	y /= norm;
	z /= norm;
	auto axis = x * e1 + y * e2 + z * e3;

	auto pseudoscalar = e1 * e2 * e3;
	auto exponent = axis * pseudoscalar;

	auto left_multiply = cos(-1 * angle / 2) + exponent * sin(-1 * angle / 2);
	auto right_multiply = cos(angle / 2) + exponent * sin(angle / 2);

	auto current = std::get<0>(point) * e1 + std::get<1>(point) * e2 + std::get<2>(point) * e3;
	auto result = left_multiply * current * right_multiply;

	auto result_itr = result.values().begin();
	double result_x = *result_itr;
	result_itr++;
	double result_y = *result_itr;
	result_itr++;
	double result_z = *result_itr;

	return { result_x, result_y, result_z };
}

void gp::Viewer::translate(double dx, double dy, double dz)
{
	x_ += dx;
	y_ += dy;
	z_ += dz;

	std::get<0>(plane_point_1_) += dx;
	std::get<1>(plane_point_1_) += dy;
	std::get<2>(plane_point_1_) += dz;

	std::get<0>(plane_point_2_) += dx;
	std::get<1>(plane_point_2_) += dy;
	std::get<2>(plane_point_2_) += dz;

	std::get<0>(plane_point_3_) += dx;
	std::get<1>(plane_point_3_) += dy;
	std::get<2>(plane_point_3_) += dz;
}

void gp::Viewer::rotate(std::tuple<double, double, double> axis_vector, double angle)
{
	std::tuple<double, double, double> plane_point_1 = plane_point_1_;
	std::tuple<double, double, double> plane_point_2 = plane_point_2_;
	std::tuple<double, double, double> plane_point_3 = plane_point_3_;

	std::get<0>(plane_point_1) = std::get<0>(plane_point_1) - x_;
	std::get<1>(plane_point_1) = std::get<1>(plane_point_1) - y_;
	std::get<2>(plane_point_1) = std::get<2>(plane_point_1) - z_;

	std::get<0>(plane_point_2) = std::get<0>(plane_point_2) - x_;
	std::get<1>(plane_point_2) = std::get<1>(plane_point_2) - y_;
	std::get<2>(plane_point_2) = std::get<2>(plane_point_2) - z_;

	std::get<0>(plane_point_3) = std::get<0>(plane_point_3) - x_;
	std::get<1>(plane_point_3) = std::get<1>(plane_point_3) - y_;
	std::get<2>(plane_point_3) = std::get<2>(plane_point_3) - z_;

	plane_point_1 = this->rotateLocation(plane_point_1, axis_vector, angle);
	plane_point_2 = this->rotateLocation(plane_point_2, axis_vector, angle);
	plane_point_3 = this->rotateLocation(plane_point_3, axis_vector, angle);

	std::get<0>(plane_point_1) = std::get<0>(plane_point_1) + x_;
	std::get<1>(plane_point_1) = std::get<1>(plane_point_1) + y_;
	std::get<2>(plane_point_1) = std::get<2>(plane_point_1) + z_;

	std::get<0>(plane_point_2) = std::get<0>(plane_point_2) + x_;
	std::get<1>(plane_point_2) = std::get<1>(plane_point_2) + y_;
	std::get<2>(plane_point_2) = std::get<2>(plane_point_2) + z_;

	std::get<0>(plane_point_3) = std::get<0>(plane_point_3) + x_;
	std::get<1>(plane_point_3) = std::get<1>(plane_point_3) + y_;
	std::get<2>(plane_point_3) = std::get<2>(plane_point_3) + z_;

	plane_point_1_ = plane_point_1;
	plane_point_2_ = plane_point_2;
	plane_point_3_ = plane_point_3;
}

// TODO: avoid duplicated code
void gp::Viewer::rotate(std::tuple<double, double, double> axis_point_1, std::tuple<double, double, double> axis_point_2, double angle)
{
	double viewer_x = x_;
	double viewer_y = y_;
	double viewer_z = z_;

	std::tuple<double, double, double> plane_point_1 = plane_point_1_;
	std::tuple<double, double, double> plane_point_2 = plane_point_2_;
	std::tuple<double, double, double> plane_point_3 = plane_point_3_;

	double axis_point_1_x = std::get<0>(axis_point_1);
	double axis_point_1_y = std::get<1>(axis_point_1);
	double axis_point_1_z = std::get<2>(axis_point_1);

	std::get<0>(axis_point_2) = std::get<0>(axis_point_2) - axis_point_1_x;
	std::get<1>(axis_point_2) = std::get<1>(axis_point_2) - axis_point_1_y;
	std::get<2>(axis_point_2) = std::get<2>(axis_point_2) - axis_point_1_z;

	viewer_x -= axis_point_1_x;
	viewer_y -= axis_point_1_y;
	viewer_z -= axis_point_1_z;

	std::get<0>(plane_point_1) = std::get<0>(plane_point_1) - axis_point_1_x;
	std::get<1>(plane_point_1) = std::get<1>(plane_point_1) - axis_point_1_y;
	std::get<2>(plane_point_1) = std::get<2>(plane_point_1) - axis_point_1_z;

	std::get<0>(plane_point_2) = std::get<0>(plane_point_2) - axis_point_1_x;
	std::get<1>(plane_point_2) = std::get<1>(plane_point_2) - axis_point_1_y;
	std::get<2>(plane_point_2) = std::get<2>(plane_point_2) - axis_point_1_z;

	std::get<0>(plane_point_3) = std::get<0>(plane_point_3) - axis_point_1_x;
	std::get<1>(plane_point_3) = std::get<1>(plane_point_3) - axis_point_1_y;
	std::get<2>(plane_point_3) = std::get<2>(plane_point_3) - axis_point_1_z;

	plane_point_1 = this->rotateLocation(plane_point_1, axis_point_2, angle);
	plane_point_2 = this->rotateLocation(plane_point_2, axis_point_2, angle);
	plane_point_3 = this->rotateLocation(plane_point_3, axis_point_2, angle);
	std::tuple<double, double, double> new_viewer_loc = this->rotateLocation({ viewer_x, viewer_y, viewer_z }, axis_point_2, angle);

	viewer_x = std::get<0>(new_viewer_loc);
	viewer_y = std::get<1>(new_viewer_loc);
	viewer_z = std::get<2>(new_viewer_loc);

	viewer_x += axis_point_1_x;
	viewer_y += axis_point_1_y;
	viewer_z += axis_point_1_z;

	std::get<0>(plane_point_1) = std::get<0>(plane_point_1) + axis_point_1_x;
	std::get<1>(plane_point_1) = std::get<1>(plane_point_1) + axis_point_1_y;
	std::get<2>(plane_point_1) = std::get<2>(plane_point_1) + axis_point_1_z;

	std::get<0>(plane_point_2) = std::get<0>(plane_point_2) + axis_point_1_x;
	std::get<1>(plane_point_2) = std::get<1>(plane_point_2) + axis_point_1_y;
	std::get<2>(plane_point_2) = std::get<2>(plane_point_2) + axis_point_1_z;

	std::get<0>(plane_point_3) = std::get<0>(plane_point_3) + axis_point_1_x;
	std::get<1>(plane_point_3) = std::get<1>(plane_point_3) + axis_point_1_y;
	std::get<2>(plane_point_3) = std::get<2>(plane_point_3) + axis_point_1_z;

	plane_point_1_ = plane_point_1;
	plane_point_2_ = plane_point_2;
	plane_point_3_ = plane_point_3;

	x_ = viewer_x;
	y_ = viewer_y;
	z_ = viewer_z;
}

std::tuple<double, double, double> gp::Viewer::getLocation()
{
	std::tuple<double, double, double> location = { x_, y_, z_ };
	return location;
}

std::tuple<
	std::tuple<double, double, double>,
	std::tuple<double, double, double>,
	std::tuple<double, double, double>
> gp::Viewer::getViewingPlane()
{
	return { plane_point_1_, plane_point_2_, plane_point_3_ };
}
