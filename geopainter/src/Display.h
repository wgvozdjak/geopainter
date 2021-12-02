#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <unordered_set>
#include <Microsoft.Graphics.Canvas.native.h>

using namespace Microsoft::Graphics::Canvas;

namespace geopainter
{
	class Shape;
	class Point;

	class Display
	{
	public:
		friend class Shape;

		Display(CanvasDrawingSession^ drawing_session);
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

		// temporary helper function to test drawing
		void drawAllShapes();

	private:
		void addShape(Shape* shape);
		void removeShape(Shape* shape);

		CanvasDrawingSession^ drawing_session_;
		std::unordered_set<Shape*> list_of_shapes_;

		// temporary functions to test drawing
		void immediatelyDisplayShape(Point* point);
	};
}

#endif
