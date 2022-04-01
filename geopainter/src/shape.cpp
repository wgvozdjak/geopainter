#include "pch.h"
#include "include/geopainter.h"

namespace gp = geopainter;

gp::Shape::Shape()
{
	color_ = new gp::Color(255, 255, 255, 255);
}

gp::Shape::~Shape()
{
	delete color_;
}

void gp::Shape::draw()
{
	display_->addShape(this);
}

void gp::Shape::erase()
{
	display_->removeShape(this);
}

void gp::Shape::setColor(gp::Color* color)
{
	color_ = new Color(color);
}
