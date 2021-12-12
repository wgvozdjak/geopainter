#include "pch.h"

//#include "display.h"
//#include "shape.h"

#include "include/geopainter.h"


namespace gp = geopainter;

void gp::Shape::draw()
{
	display_->addShape(this);
}

void gp::Shape::erase()
{
	display_->removeShape(this);
}
