#ifndef GEOPAINTER_H_
#define GEOPAINTER_H_

#include <unordered_set>
#include <Microsoft.Graphics.Canvas.native.h>

#ifdef GEOPAINTER_EXPORTS
#define GEOPAINTER_API __declspec(dllexport)
#else
#define GEOPAINTER_API __declspec(dllimport)
#endif

using namespace Microsoft::Graphics::Canvas;

namespace geopainter
{
	class Display;
	class Shape;
	class Point;

	class GEOPAINTER_API Display
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

		// temporary functions to test drawing
		void immediatelyDisplayShape(Point* point);

	private:
		void addShape(Shape* shape);
		void removeShape(Shape* shape);

		CanvasDrawingSession^ drawing_session_;
		std::unordered_set<Shape*> list_of_shapes_;

		
	};

	class GEOPAINTER_API Shape
	{
	public:
		void draw();
		void erase();
		virtual void translate(double dx, double dy, double dz) = 0;
		virtual void move(double x, double y, double z) = 0;
		virtual void rotate(double x, double y, double z, double angle) = 0;
		virtual void dilate(double scale_factor) = 0;
		// TODO: virtual void setColor(color) = 0;
		// TODO: virtual Color getColor() = 0;

	protected:
		Display* display_;

		//virtual void drawShape(CanvasRenderTarget^ render_target) = 0;
	};

	class GEOPAINTER_API Point : public Shape
	{
		friend class Display;

	public:
		void translate(double dx, double dy, double dz);
		void move(double x, double y, double z);
		void rotate(double x, double y, double z, double angle);
		void dilate(double scale_factor);
		// TODO: void setColor(color);
		// TODO: Color getColor();

		// temporary functions to test drawing
		double getX();
		double getY();
		double getZ();

	private:
		double x_;
		double y_;
		double z_;

		Point(Display* display, double x, double y, double z);

		//void drawShape(CanvasRenderTarget^ render_target);
	};

	class GEOPAINTER_API Line : public Shape
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
		Point* p1_;
		Point* p2_;

		Line(Display* display, Point* p1, Point* p2);
	};
}

#endif
