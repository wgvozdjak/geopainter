#include "pch.h"

//#include "display.h"
//#include "point.h"
#include "include/geopainter.h"

namespace gp = geopainter;

gp::Display::Display(CanvasDrawingSession^ drawing_session)
{
	drawing_session_ = drawing_session;
}

gp::Point* gp::Display::createPoint(double x, double y, double z)
{
	gp::Point* point = new gp::Point(this, x, y, z);
	return point;
}

void gp::Display::addShape(gp::Shape* shape)
{
	list_of_shapes_.insert(shape);
}

void gp::Display::removeShape(gp::Shape* shape)
{
	list_of_shapes_.erase(shape);
}


// temporary functions to test drawing
void gp::Display::immediatelyDisplayShape(gp::Point* point)
{
	drawing_session_->DrawCircle(point->getX(), point->getY(), 1, Windows::UI::Colors::Red, 1);
}

void gp::Display::drawAllShapes()
{
	
}
