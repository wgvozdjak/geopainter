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

		Display(CanvasDrawingSession^ drawing_session);
		// TODO: Viewer getViewer()
		Point* createPoint(double x, double y, double z);
		Line* createLine(Point* p1, Point* p2);
		// TODO: Polygon createPolygon(vector<Point> vertices)
		// TODO: Bag createBag(vector<Shape> shapes)
		// TODO: void deleteShape(Shape shape)
		// TODO: void deleteAll()
		void flip();
		// TODO: void setWindowSize(int width, int height)
		// TODO: void setBackgroundColor(Color color)

		// TODO: find a way to not expose this to the user
		std::pair<double, double> projectLocation(double x, double y, double z);
		void showPoint(double x, double y);
		void showLine(std::pair<double, double> first_endpoint, std::pair<double, double> second_endpoint);

	private:
		void addShape(Shape* shape);
		void removeShape(Shape* shape);

		CanvasDrawingSession^ drawing_session_;
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
		virtual void show() = 0;

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

	protected:
		void show();

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

	protected:
		void show();

	private:
		Point* p1_;
		Point* p2_;

		Line(Display* display, Point* p1, Point* p2);
	};
}

#endif
