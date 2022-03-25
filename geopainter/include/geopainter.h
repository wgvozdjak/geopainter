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
		// Translates the viewer's x-coordinate by dx, y-coordinate by dy, and z-coordinate by dz
		void translate(double dx, double dy, double dz);

		// Rotates the viewer by angle counterclockwise around the line through the viewer and viewer plus axis_vector
		void rotate(std::tuple<double, double, double> axis_vector, double angle);

		// Rotates the viewer by angle counterclockwise around the line through axis_point_1 and axis_point_2
		void rotate(std::tuple<double, double, double> axis_point_1, std::tuple<double, double, double> axis_point_2, double angle);


		std::tuple<double, double, double> getLocation();

		std::tuple<
			std::tuple<double, double, double>,
			std::tuple<double, double, double>,
			std::tuple<double, double, double>
		> getViewingPlane();
	private:
		// Creates a new Viewer object
		Viewer();

		// Returns the location of the Viewer as an std::tuple
		//std::tuple<double, double, double> getLocation();

		// Returns points defining viewing plane as an std::tuple
		// TODO: should this be split into multiple methods, or is there just a better way to do this in general?
		/*std::tuple<
			std::tuple<double, double, double>,
			std::tuple<double, double, double>,
			std::tuple<double, double, double>
		> getViewingPlane();*/

		// Rotates point around axis through axis and origin by angle
		std::tuple<double, double, double> rotateLocation(
			std::tuple<double, double, double> point, 
			std::tuple<double, double, double> axis_vector, 
			double angle
		);

		// Current coordinates of the Viewer
		double x_;
		double y_;
		double z_;

		std::tuple<double, double, double> plane_point_1_;
		std::tuple<double, double, double> plane_point_2_;
		std::tuple<double, double, double> plane_point_3_;
	};

	class GEOPAINTER_API Display
	{
	public:
		friend class Shape;

		// Creates a new Display object
		Display();

		// Returns a pointer to the Viewer object associated with the Display
		Viewer* getViewer();

		// Returns a pointer to a new Point object at coordinates (x, y, z)
		Point* createPoint(double x, double y, double z);

		// Returns a pointer to a new Line object with endpoints at *p1 and *p2
		Line* createLine(Point* p1, Point* p2);

		// TODO: Polygon createPolygon(vector<Point> vertices)
		// TODO: Bag createBag(vector<Shape> shapes)

		// Removes the shape from the buffer and deletes the shape
		void deleteShape(Shape* shape);

		// Removes all shapes from the buffer and deletes all shapes
		void deleteAll();

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
		// Adds the pointer to a shape to the buffer
		void addShape(Shape* shape);

		// Removes the pointer to a shape from the buffer
		void removeShape(Shape* shape);

		std::unordered_set<Shape*> list_of_shapes_;
		Viewer* viewer_;
	};

	class GEOPAINTER_API Shape
	{
	public:
		void draw();
		void erase();
		virtual void translate(double dx, double dy, double dz) = 0;
		virtual void move(double x, double y, double z) = 0;
		virtual void rotate(std::tuple<double, double, double>, double angle) = 0;
		virtual void rotate(std::tuple<double, double, double> axis_point_1, std::tuple<double, double, double> axis_point_2, double angle) = 0;
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
		void rotate(std::tuple<double, double, double>, double angle);
		void rotate(std::tuple<double, double, double> axis_point_1, std::tuple<double, double, double> axis_point_2, double angle);
		void dilate(double scale_factor);
		// TODO: void setColor(color);
		// TODO: Color getColor();

		// TODO: decide if this is the best way
		double getX();
		double getY();
		double getZ();

		void show(CanvasDrawingSession^ current_drawing_session);

		// TODO: determine if this is the best way to allow the user to get the location of a Point
		std::tuple<double, double, double> getLocation();

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
		void rotate(std::tuple<double, double, double>, double angle);
		void rotate(std::tuple<double, double, double> axis_point_1, std::tuple<double, double, double> axis_point_2, double angle);
		void dilate(double scale_factor);
		// TODO: void setColor(color);
		// TODO: Color getColor();

		// TODO: determine if this is the best way to allow the user to get the location of a Line
		std::pair<std::tuple<double, double, double>, std::tuple<double, double, double>> getLocation();

		void show(CanvasDrawingSession^ current_drawing_session);

	private:
		Point* p1_;
		Point* p2_;

		Line(Display* display, Point* p1, Point* p2);
	};
}

#endif
