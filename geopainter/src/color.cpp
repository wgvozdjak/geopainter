#include "pch.h"
#include "include/geopainter.h"

namespace gp = geopainter;

gp::Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	red_ = red;
	green_ = green;
	blue_ = blue;
	alpha_ = alpha;
	
	// TODO: decide whether this is necessary
	// winui_color_ = Windows::UI::ColorHelper::FromArgb(alpha, red, green, blue);
}

gp::Color::Color(gp::Color* color)
{
	red_ = color->red_;
	green_ = color->green_;
	blue_ = color->blue_;
	alpha_ = color->alpha_;
}

std::tuple<unsigned char, unsigned char, unsigned char, unsigned char> gp::Color::getRGBAHex()
{
	return { red_, green_, blue_, alpha_ };
}
