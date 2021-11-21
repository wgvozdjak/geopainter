#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <vector>

namespace geopainter
{
	class Shape;
	class Point;

	class Display
	{
	public:
		// TODO: Display();
		// TODO: Viewer getViewer()
		Point* createPoint(double x, double y, double z);
		// TODO: Line createLine(Point p1, Point p2)
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

#endif
