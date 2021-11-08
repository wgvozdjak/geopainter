#pragma once

#include <vector>

namespace geopainter
{
	class Display
	{
	public:
		// TODO: Display();
		// TODO: Viewer getViewer()
		// TODO: Point createPoint(double x, double y, double z)
		// TODO: Lne createLine(Point p1, Point p2)
		// TODO: Polygon createPolygon(vector<Point> vertices)
		// TODO: Bag createBag(vector<Shape> shapes)
		// TODO: void deleteShape(Shape shape)
		// TODO: void deleteAll()
		// TODO: void flip()
		// TODO: void setWindowSize(int width, int height)
		// TODO: void setBackgroundColor(Color color)

	private:
		std::vector<Shape> list_of_shapes;
	};

	class Shape
	{
	public:
		virtual void draw() = 0;
		virtual void erase() = 0;
		virtual void translate() = 0;
		virtual void move() = 0;
		virtual void rotate() = 0;
		virtual void dilate() = 0;
		virtual void setColor() = 0;
		// TODO: virtual Color getColor() = 0;
	};
}
