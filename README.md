# Geopainter

Geopainter is a C++ DLL for 3D graphics, implementing basic drawing commands and manipulation of objects in space.

Its mathematical computations are performed using geometric algebra, simplifying and (potentially) allowing for faster computations (note that the code in this project is largely unoptimized).

## 1. Contents

1. [Contents](#1-contents)
2. [Dependencies](#2-dependencies)
3. [Installing Geopainter](#3-installing-geopainter)
4. [Documentation](#4-documentation)
5. [Typical Workflow](#5-typical-workflow)
6. [Example Project](#6-example-project)

## 2. Dependencies

Geopainter is dependent on the following programs in addition to C++, which must be installed for Geopainter to be used:

1. [GATL](https://github.com/laffernandes/gatl)
2. [Win2D](https://github.com/microsoft/Win2D?tab=readme-ov-file)

## 3. Installing Geopainter

Installation of Geopainter is carried out as a typical C++ DLL. Once the project is cloned to your local machine, see, for example, [Microsoft Documentation](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170) on instructions on how to use it.

## 4. Documentation

All functionalities are located in the namespace `geopainter`, which is abbreviated as `gp` throughout the documentation. Note that Geopainter uses Cartesian coordinates everywhere, so when something refers to "coordinates" it is implied that they are Cartesian coordinates. All coordinates are also doubles.

Each of the following headers are classes that Geopainter provides.

### Display

Overall drawing board that must be created before any other functionalities are used.

#### Constructors

| Constructor | Description |
| ------- | --------- |
| `Display()` | Creates a new Display object and instantiates and remembers a new `Viewer` object |

#### Methods

| Method | Description |
| ------- | --------- |
| `getViewer()` | Returns the corresponding `Viewer` object |
| `createPoint(double x, double y, double z)` | Returns a new `Point` object at coordinates (x, y, z) |
| `createLine(gp::Point* p1, gp::Point* p2)` | Returns a new `Line` object with endpoints `p1*` and `p2*` |
| `deleteShape(gp::Shape* shape)` | Removes `shape*` from the list of shapes that will be drawn once `flip` is called and deletes the `shape` object |
| `deleteAll()` | Removes all shapes from the list of shapes to be drawn once `flip` is called and deletes all shapes |
| `flip(CanvasDrawingSession^ drawing_session)` | Draws all added shapes on `drawing_session` |

### Viewer

Represents the location in 3D space from which the world is being viewed from. Contains both the coordinates of the location of the Viewer, as well as the location of the "viewing plane," the plane onto which all objects are projected on. The viewing plane is represented as three points who lie on the plane.

#### Constructors

Viewer objects are instantiated when a `Display` object is created and should not be created individually.

#### Methods

| Method | Description |
| ------- | --------- |
| `getLocation()` | Returns the current coordinates of the Viewer as a tuple |
| `getViewingPlane()` | Returns the three tuples corresponding to the points of the viewing plane as a tuple (therefore returns a tuple of tuples) |
| `translate(double dx, double dy, double dz)` | Translates the location of the Viewer by the vector (`dx`, `dy`, `dz`) |
| `rotate(std::tuple<double, double, double> axis_vector, double angle)` | Rotates the location of the Viewer by `angle` radians around line through the origin and parallel to the vector `axis_vector` |
| `rotate(std::tuple<double, double, double> axis_point_1, std::tuple<double, double, double> axis_point_2, double angle)` | Rotates the location of the Viewer by `angle` radians around the line through `axis_point_1` and `axis_point_2` |
| `rotateLocation(std::tuple<double, double, double> point, std::tuple<double, double, double> axis_vector, double angle)` | Rotates the location of the Viewer by `angle` radians around the line through `point` and parallel to the vector `axis_vector` |
|

### Color

Represents one color that can be used to color various objects that are drawn on the screen.

#### Constructors

| Constructor | Description |
| ------- | --------- |
| `Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)` | Creates a new Color object with color corresponding to the RGBA tuple (red, green, blue, alpha) |
| `Color(gp::Color* color)` | Creates a new `Color` object that is a duplicate of `color*` |

#### Methods

| Method | Description |
| ------- | --------- |
| `getRGBAHex()` | Returns a tuple consisting of the red, green, blue, and alpha values of the color in that order |

### Shape

An abstract class representing any shape that can be drawn on the screen.

#### Constructors

An abstract class that should not be instantiated.

#### Methods

| Method | Description |
| ------- | --------- |
| `draw()` | Adds the Shape to the list of objects to be drawn when `Display::flip()` is called |
| `erase()` | Removes the Shape from the list of objects to be drawn when `Display::flip()` is called |
| `translate(double dx, double dy, double dz)` | Translates the Shape by the vector (`dx`, `dy`, `dz`) |
| `move(double dx, double dy, double dz)` | Moves the Shape to the coordinates (`dx`, `dy`, `dz`). Currently only implemented for `Point` objects |
| `rotate(std::tuple<double, double, double> axis_vector, double angle)` | Rotates the Shape by `angle` radians around the line through the origin parallel to the vector `axis_vector` |
| `rotate(std::tuple<double, double, double> axis_point_1, std::tuple<double, double, double> axis_point_2, double angle)` | Rotates the shape by `angle` radians around the line through the points `axis_point_1` and `axis_point_2` |
| `setColor(Color* color)` | Sets the color with which the Shape should be drawn to `color*` |

Note: `dilate` has not yet been implemented.

### Point

Represents a point in 3D space that can be drawn.

#### Constructors

| Constructor | Description |
| ------- | --------- |
| `Point(gp::Display* display, double x, double y, double z)` | Creates a point at coordinates (`x`, `y`, `z`) that can be drawn on the Display `display*` |

#### Methods

`Point` has the following methods in addition to the methods listed under the `Shape` abstract class.

| Method | Description |
| ------- | --------- |
| `getLocation()` | Returns a tuple containing the current coordinates of the Point object |

### Line

Represents a line segment in 3D space that can be drawn.

#### Constructors

| Constructor | Description |
| ------- | --------- |
| `Line(gp::Display* display, gp::Point* p1, gp::Point* p2)` | Creates a line segment with endpoints at `p1*` and `p2*` that can be drawn on the Display `display*` |

#### Methods

`Line` has the following methods in addition to the methods listed under the `Shape` abstract class.

| Method | Description |
| ------- | --------- |
| `getLocation()` | Returns a pair containing two tuples representing the coordinates of the two endpoints of the Line object |

## 5. Typical Workflow

As a brief demonstration of Geopainter, an example workflow of creating and manipulating a 3D image may look as follows:

1. Create a `Display` object and retrieve its corresponding `Viewer` object.
2. Create all necessary Shapes (at the time of writing, all `Point` and `Line` objects) at the necessary locations.
3. Call `draw` on all such Shapes.
4. Call `flip` on the Display object, drawing all those shapes to the screen.
5. Manipulate all Shape objects as necessary, including creating/destroying Shape objects and calling draw/erase on Shape objects, and calling `flip` once every "frame."

## 6. Example Project

An example project using Geopainter is included in the `example_pong` folder, in which a 3D pong game is implemented allowing the user to not only play pong in 3D but also rotate the camera to view the game from different angles.
