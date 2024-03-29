#include "pch.h"
#include "include/geopainter.h"
#include "gatl/ga4e.hpp"

#include <Microsoft.Graphics.Canvas.native.h>

#include <cmath>
#include "debugapi.h"

namespace gp = geopainter;

using namespace Platform;
using namespace ga4e;
using namespace Microsoft::Graphics::Canvas;

void LogMessage(Object^ parameter)
{
	auto paraString = parameter->ToString();
	auto formattedText = std::wstring(paraString->Data()).append(L"\r\n");
	OutputDebugString(formattedText.c_str());
}

gp::Display::Display()
{
	viewer_ = new Viewer();
}

gp::Viewer* gp::Display::getViewer()
{
	return viewer_;
}

gp::Point* gp::Display::createPoint(double x, double y, double z)
{
	gp::Point* point = new gp::Point(this, x, y, z);
	return point;
}

gp::Line* gp::Display::createLine(gp::Point* p1, gp::Point* p2)
{
	gp::Line* line = new gp::Line(this, p1, p2);
	return line;
}

void gp::Display::addShape(gp::Shape* shape)
{
	list_of_shapes_.insert(shape);
}

void gp::Display::removeShape(gp::Shape* shape)
{
	list_of_shapes_.erase(shape);
}

void gp::Display::deleteShape(gp::Shape* shape)
{
	removeShape(shape);
	delete shape;
}

void gp::Display::deleteAll()
{
	for (gp::Shape* shape : list_of_shapes_)
	{
		delete shape;
	}
	list_of_shapes_.clear();
}

std::pair<double, double> gp::Display::projectLocation(double x, double y, double z)
{
	// get location of viewing plane into a more usable format
	std::tuple<
		std::tuple<double, double, double>,
		std::tuple<double, double, double>,
		std::tuple<double, double, double>
	> viewing_plane = viewer_->getViewingPlane();

	std::tuple<double, double, double> plane_point_1 = std::get<0>(viewing_plane);
	std::tuple<double, double, double> plane_point_2 = std::get<1>(viewing_plane);
	std::tuple<double, double, double> plane_point_3 = std::get<2>(viewing_plane);

	// --- PROJECT POINT (x, y, z) IN 4D ---
	// get location of viewer/focus
	std::tuple<double, double, double> viewer_location = viewer_->getLocation();

	// initialize geometric algebra objects: point to be projected, points on plane, and viewer/focus
	auto point_to_project = e1 * x + e2 * y + e3 * z + e4;

	// TODO: double check whether this is the right way to go about this
	//auto z_displacement = -0.75 * e3;

	auto plane_origin =
		e4 +
		e1 * std::get<0>(plane_point_1) +
		e2 * std::get<1>(plane_point_1) +
		e3 * std::get<2>(plane_point_1);
	auto plane_direction_one =
		e4 +
		e1 * std::get<0>(plane_point_2) +
		e2 * std::get<1>(plane_point_2) +
		e3 * std::get<2>(plane_point_2);
	auto plane_direction_two =
		e4 +
		e1 * std::get<0>(plane_point_3) +
		e2 * std::get<1>(plane_point_3) +
		e3 * std::get<2>(plane_point_3);

	auto focus = e1 * std::get<0>(viewer_location) + 
				 e2 * std::get<1>(viewer_location) + 
				 e3 * std::get<2>(viewer_location) + 
				 e4;

	// find display plane: outer product of three points on plane
	auto plane = plane_origin ^ plane_direction_one ^ plane_direction_two;

	// find line between focus on point to be projected: outer product of focus and point
	auto line = focus ^ point_to_project;

	// intersect plane and line
	auto intersection = rp(plane, line);

	// scale intersection down so that the coefficient of extra coordinate (of e4) is one
	// intersection | e4 is equal to the coefficient of e4
	auto scaled_intersection = intersection / (intersection | e4);

	// check if point is behind viewer (if point is behind viewer, then dot product
	auto vector_to_point_to_project = point_to_project - focus;
	auto vector_to_scaled_intersection = scaled_intersection - focus;

	double dot_product = vector_to_point_to_project | vector_to_scaled_intersection;
	if (dot_product < 0)
	{
		// the point is behind the viewer, return pair of nans
		return { nan(""), nan("") };
	}
	
	// --- COMPUTE 2D COORDINATES TO BE USED IN DRAWING FROM 4D COORDINATES ---
	auto point_relative_to_origin = scaled_intersection - plane_origin;

	auto plane_direction_one_vector = plane_direction_one - plane_origin;
	auto plane_direction_two_vector = plane_direction_two - plane_origin;

	auto point_x_projection = igp(point_relative_to_origin | plane_direction_one_vector, plane_direction_one_vector);
	auto point_y_projection = igp(point_relative_to_origin | plane_direction_two_vector, plane_direction_two_vector);

	double x_coordinate = point_x_projection | plane_direction_one_vector;
	double y_coordinate = point_y_projection | plane_direction_two_vector;

	// used to be 300
	int factor = 1500;

	// center everything so (0, 0) is at center of sceen when in fullscreen on surface book
	double x_center = 750;
	double y_center = 465;

	double return_x_coordinate = x_coordinate * factor + x_center;
	double return_y_coordinate = y_coordinate * factor + y_center;
	//LogMessage(return_x_coordinate + ", " + return_y_coordinate);
	return { return_x_coordinate, return_y_coordinate };
}

void gp::Display::showPoint(double x, double y, Color* color, CanvasDrawingSession^ current_drawing_session)
{
	std::tuple<unsigned char, unsigned char, unsigned char, unsigned char> color_tuple = color->getRGBAHex();
	unsigned char red = std::get<0>(color_tuple);
	unsigned char green = std::get<1>(color_tuple);
	unsigned char blue = std::get<2>(color_tuple);
	unsigned char alpha = std::get<3>(color_tuple);

	Windows::UI::Color winui_color = Windows::UI::ColorHelper::FromArgb(alpha, red, green, blue);

	current_drawing_session->DrawCircle(x, y, 1, winui_color, 1);
}

void gp::Display::showLine(std::pair<double, double> first_endpoint, std::pair<double, double> second_endpoint, Color* color, CanvasDrawingSession^ current_drawing_session)
{
	std::tuple<unsigned char, unsigned char, unsigned char, unsigned char> color_tuple = color->getRGBAHex();
	unsigned char red = std::get<0>(color_tuple);
	unsigned char green = std::get<1>(color_tuple);
	unsigned char blue = std::get<2>(color_tuple);
	unsigned char alpha = std::get<3>(color_tuple);

	Windows::UI::Color winui_color = Windows::UI::ColorHelper::FromArgb(alpha, red, green, blue);
	current_drawing_session->DrawLine(first_endpoint.first, first_endpoint.second, second_endpoint.first, second_endpoint.second, winui_color, 1);
}

void gp::Display::flip(CanvasDrawingSession^ drawing_session)
{
	// loop through list_of_shapes_ and show each one
	for (gp::Shape* shape : list_of_shapes_)
	{
		shape->show(drawing_session);
	}
}
