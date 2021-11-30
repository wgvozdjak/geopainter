#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include "shape.h"

namespace geopainter
{
	class Display;

	class Point : public Shape
	{
		friend class Display;

	public:
		void translate(double dx, double dy, double dz);
		void move(double x, double y, double z);
		void rotate(double x, double y, double z, double angle);
		void dilate(double scale_factor);
		// TODO: void setColor(color);
		// TODO: Color getColor();

	private:
		double x_;
		double y_;
		double z_;

		Point(Display* display, double x, double y, double z);
	};
}

#endif
