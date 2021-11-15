#pragma once

#include <include/geopainter.h>

namespace geopainter
{
	class Point : public Shape
	{
	public:
		void draw();
		void erase();
		void translate(double dx, double dy, double dz);
		void move(double x, double y, double z);
		void rotate(double x, double y, double z, double angle);
		void dilate(double scale_factor);
		// TODO: void setColor(color);
		// TODO: Color getColor();

	/*private:
		int x;
		int y;
		int z;*/
	};
}