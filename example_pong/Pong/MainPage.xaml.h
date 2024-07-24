//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "include/geopainter.h"
#include <vector>

using namespace geopainter;
using namespace std;

namespace gp = geopainter;

namespace Pong
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

		void CanvasControl_Draw(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender,
			Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);

		void control_Loaded(Windows::UI::Xaml::RoutedEventHandler^ sender,
			Windows::UI::Xaml::RoutedEventArgs^ args);

		void StartNewGame(Windows::UI::Xaml::RoutedEventHandler^ sender,
			Windows::UI::Xaml::RoutedEventArgs^ args);

		void MouseEnter(Windows::UI::Xaml::RoutedEventHandler^ sender,
			Windows::UI::Xaml::RoutedEventArgs^ args);

		void MouseLeave(Windows::UI::Xaml::RoutedEventHandler^ sender,
			Windows::UI::Xaml::RoutedEventArgs^ args);

	private:
		void MainPage::CoreWindow_KeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);

		gp::Display display;
		Viewer* viewer;

		vector<Line*> room_edges;
		vector<gp::Point*> room_vertices;

		double paddle_side_length = 0.3333;

		vector<Line*> paddle_edges;
		vector<gp::Point*> paddle_vertices;

		double ball_side_length = 0.1;

		vector<Line*> ball_edges;
		vector<gp::Point*> ball_vertices;

		double ball_x_velocity = -0.01;
		double ball_y_velocity = -0.01;
		double ball_z_velocity = -0.02;

		// whether the player as lost yet
		bool lost = false;
		
		// boolean to allow one last translation of the ball before the game ends
		// (necessary as otherwise when the lost flag becomes true, the ball is not translated
		// for the last time and the ball isn't touching the wall when the game ends)
		bool last_translation = false;

		int score = 0;
		int high_score = 0;
		
	};
}
