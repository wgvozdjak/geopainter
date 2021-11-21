#ifndef SHAPE_H_
#define SHAPE_H_

namespace geopainter
{
	class Display;

	class Shape
	{
	public:
		virtual void draw() = 0;
		virtual void erase() = 0;
		virtual void translate(double dx, double dy, double dz) = 0;
		virtual void move(double x, double y, double z) = 0;
		virtual void rotate(double x, double y, double z, double angle) = 0;
		virtual void dilate(double scale_factor) = 0;
		// TODO: virtual void setColor(color) = 0;
		// TODO: virtual Color getColor() = 0;

	protected:
		Display* display_;
	};
}

#endif
