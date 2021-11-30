#include "pch.h"

#include "display.h"
#include "shape.h"

namespace gp = geopainter;

void gp::Shape::draw()
{
	display_->list_of_shapes_.insert(*this);
}

void gp::Shape::erase()
{
	display_->list_of_shapes_.erase(*this);
}
