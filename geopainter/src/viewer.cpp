#include "pch.h"
#include "include/geopainter.h"

namespace gp = geopainter;

gp::Viewer::Viewer()
{
	x_ = 2.0;
	y_ = 2.0;
	z_ = -7.75;
}

std::tuple<double, double, double> gp::Viewer::getLocation()
{
	std::tuple<double, double, double> location = { x_, y_, z_ };
	return location;
}
