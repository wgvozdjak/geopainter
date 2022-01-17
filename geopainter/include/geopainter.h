#ifndef GEOPAINTER_H_
#define GEOPAINTER_H_

#include <unordered_set>
#include <Microsoft.Graphics.Canvas.native.h>

#ifdef GEOPAINTER_EXPORTS
#define GEOPAINTER_API __declspec(dllexport)
#else
#define GEOPAINTER_API __declspec(dllimport)
#endif

#undef min
#undef max

using namespace Microsoft::Graphics::Canvas;

namespace geopainter
{
	class Viewer;
	class Display;
	class Shape;
	class Point;
	class Line;

	class GEOPAINTER_API Viewer
	{
		friend class Display;

	public:
	private:
		Viewer();

		std::tuple<double, double, double> getLocation();

		double x_;
		double y_;
		double z_;
	};

	class GEOPAINTER_API Display
	{
	public:
		friend class Shape;

		// Creates a new Display attached to a CanvasDrawingSession object
		//Display(CanvasDrawingSession^ drawing_session);
		Display();
		// TODO: Viewer getViewer()

		// Returns a pointer to a new Point object at coordinates (x, y, z)
		Point* createPoint(double x, double y, double z);

		// Returns a pointer to a new Line object with endpoints at *p1 and *p2
		Line* createLine(Point* p1, Point* p2);

		// TODO: Polygon createPolygon(vector<Point> vertices)
		// TODO: Bag createBag(vector<Shape> shapes)
		// TODO: void deleteShape(Shape shape)
		// TODO: void deleteAll()

		// TODO: find better word for buffer
		// Draws all objects in the buffer to to screen
		void flip(CanvasDrawingSession^ drawing_session);

		// TODO: void setWindowSize(int width, int height)
		// TODO: void setBackgroundColor(Color color)

		// TODO: find a way to not expose this to the user
		std::pair<double, double> projectLocation(double x, double y, double z);
		void showPoint(double x, double y, CanvasDrawingSession^ current_drawing_session);
		void showLine(std::pair<double, double> first_endpoint, std::pair<double, double> second_endpoint, CanvasDrawingSession^ current_drawing_session);

	private:
		void addShape(Shape* shape);
		void removeShape(Shape* shape);

		std::unordered_set<Shape*> list_of_shapes_;
		Viewer viewer_;
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

		// TODO: revisit visibility of this
		virtual void show(CanvasDrawingSession^ current_drawing_session) = 0;

	protected:
		Display* display_;
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

		// TODO: decide if this is the best way
		double getX();
		double getY();
		double getZ();

		void show(CanvasDrawingSession^ current_drawing_session);

	private:
		double x_;
		double y_;
		double z_;

		Point(Display* display, double x, double y, double z);
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

		void show(CanvasDrawingSession^ current_drawing_session);

	private:
		Point* p1_;
		Point* p2_;

		Line(Display* display, Point* p1, Point* p2);
	};
}

#endif
