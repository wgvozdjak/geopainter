#include "pch.h"
#include "include/geopainter.h"
#include "gatl/ga4e.hpp"

#include <Microsoft.Graphics.Canvas.native.h>

namespace gp = geopainter;

using namespace ga4e;
using namespace Microsoft::Graphics::Canvas;

/*gp::Display::Display(CanvasDrawingSession^ drawing_session)
{
	drawing_session_ = drawing_session;
	gp::Viewer viewer_;

	// TODO: use this for flipping
	// http://microsoft.github.io/Win2D/WinUI2/html/Offscreen.htm
	//CanvasDevice^ device = CanvasDevice::GetSharedDevice();
	CanvasDevice^ device = drawing_session_->Device;
	device_ = device;
}*/

gp::Display::Display()
{
	gp::Viewer viewer_;
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

std::pair<double, double> gp::Display::projectLocation(double x, double y, double z)
{
	// --- PROJECT POINT (x, y, z) IN 4D ---
	// get location of viewer/focus
	std::tuple<double, double, double> viewer_location = viewer_.getLocation();

	// initialize geometric algebra objects: point to be projected, points on plane, and viewer/focus
	auto point_to_project = e1 * x + e2 * y + e3 * z + e4;

	auto z_displacement = -0.75 * e3;

	auto plane_point_one = e4 + z_displacement;
	auto plane_point_two = e4 + e1 + z_displacement;
	auto plane_point_three = e4 + e2 + z_displacement;

	auto focus = e1 * std::get<0>(viewer_location) + e2 * std::get<1>(viewer_location) + e3 * std::get<2>(viewer_location) + e4;

	// find display plane: outer product of three points on plane
	//auto plane = op(op(plane_point_one, plane_point_two), plane_point_three);
	auto plane = plane_point_one ^ plane_point_two ^ plane_point_three;

	// find line between focus on point to be projected: outer product of focus and point
	auto line = focus ^ point_to_project;

	// intersect plane and line
	auto intersection = rp(plane, line);

	// scale intersection down so that the coefficient of extra coordinate (of e4) is zero
	// intersection | e4 is equal to the coefficient of e4
	auto scaled_intersection = intersection / (intersection | e4);
	
	// --- COMPUTE 2D COORDINATES TO BE USED IN DRAWING FROM 4D COORDINATES ---
	auto point_relative_to_origin = scaled_intersection - plane_point_one;

	auto plane_point_two_vector = plane_point_two - plane_point_one;
	auto plane_point_three_vector = plane_point_three - plane_point_one;

	auto point_x_projection = igp(point_relative_to_origin | plane_point_two_vector, plane_point_two_vector);
	auto point_y_projection = igp(point_relative_to_origin | plane_point_three_vector, plane_point_three_vector);

	double x_coordinate = rnorm(point_x_projection);
	double y_coordinate = rnorm(point_y_projection);

	return { x_coordinate * 300, y_coordinate * 300 };
}

void gp::Display::showPoint(double x, double y, CanvasDrawingSession^ current_drawing_session)
{
	current_drawing_session->DrawCircle(x, y, 1, Windows::UI::Colors::Red, 1);
}

void gp::Display::showLine(std::pair<double, double> first_endpoint, std::pair<double, double> second_endpoint, CanvasDrawingSession^ current_drawing_session)
{
	current_drawing_session->DrawLine(first_endpoint.first, first_endpoint.second, second_endpoint.first, second_endpoint.second, Windows::UI::Colors::Black, 1);
}

// TODO: current implementation does not flip two displays, instead just draws everything to the current display
void gp::Display::flip(CanvasDrawingSession^ drawing_session)
{
	//CanvasRenderTarget^ offscreen = ref new CanvasRenderTarget(device_, 1000, 750, drawing_session_->Dpi);
	//CanvasDrawingSession^ current_drawing_session = offscreen->CreateDrawingSession();

	//current_drawing_session->Clear(Windows::UI::Colors::White);
	for (gp::Shape* shape : list_of_shapes_)
	{
		shape->show(drawing_session);
	}

	//current_drawing_session->DrawCircle(100, 100, 100, Windows::UI::Colors::Red, 100);

	//drawing_session_->DrawImage(offscreen);
	//delete current_drawing_session;
}
