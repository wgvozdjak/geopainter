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
	// TODO: FIGURE OUT IMPLEMENTATION OF THIS
	throw "geopainter::Line::move(double x, double y, double z) has not been implemented yet.";
}

void gp::Line::rotate(std::tuple<double, double, double> axis_vector, double angle)
{
	p1_->rotate(axis_vector, angle);
	p2_->rotate(axis_vector, angle);
}

void gp::Line::rotate(std::tuple<double, double, double> axis_point_1, std::tuple<double, double, double> axis_point_2, double angle)
{
	p1_->rotate(axis_point_1, axis_point_2, angle);
	p2_->rotate(axis_point_1, axis_point_2, angle);
}

void gp::Line::dilate(double scale_factor)
{
	throw "geopainter::Line::dilate(double scale_factor) has not been implemented yet.";
}

void gp::Line::show(CanvasDrawingSession^ current_drawing_session)
{
	// project endpoints into 2D
	std::pair<double, double> projected_first_endpoint = display_->projectLocation(p1_->getX(), p1_->getY(), p1_->getZ());
	std::pair<double, double> projected_second_endpoint = display_->projectLocation(p2_->getX(), p2_->getY(), p2_->getZ());

	// draw projected point onto screen
	display_->showLine(projected_first_endpoint, projected_second_endpoint, color_, current_drawing_session);
}

std::pair<std::tuple<double, double, double>, std::tuple<double, double, double>> gp::Line::getLocation()
{
	std::tuple<double, double, double> first_endpoint = p1_->getLocation();
	std::tuple<double, double, double> second_endpoint = p2_->getLocation();

	return { first_endpoint, second_endpoint };
}
