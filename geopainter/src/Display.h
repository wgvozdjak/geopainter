#pragma once

#include <vector>

#include <include/geopainter.h>

namespace gp = geopainter;

namespace geopainter
{
	class Display
	{
	public:
		// TODO: Display();
		// TODO: Viewer getViewer()
		gp::Point* createPoint(double x, double y, double z);
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
}
