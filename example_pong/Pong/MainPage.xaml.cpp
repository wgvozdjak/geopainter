//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "include/geopainter.h"

#include <chrono>
#include <thread>
#include "debugapi.h"

#include <iostream>
#include "wchar.h"
#include "winuser.h"

using namespace Pong;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace Windows::System;
using namespace Windows::UI;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;

using namespace geopainter;
namespace gp = geopainter;

using namespace std;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

void LogMessage(Object^ parameter)
{
    auto paraString = parameter->ToString();
    auto formattedText = std::wstring(paraString->Data()).append(L"\r\n");
    OutputDebugString(formattedText.c_str());
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void MainPage::CoreWindow_KeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args)
{
    auto virtualKey = args->VirtualKey;

    double speed = 0.02;

    double x_dist = 0;
    double y_dist = 0;
    double z_dist = 0;

    // TODO: check if viewer is NULL. 
    auto viewerLocation = viewer->getLocation();
    auto viewer_x = get<0>(viewerLocation);

    auto viewingPlane = viewer->getViewingPlane();
    auto p1 = get<0>(viewingPlane); // center
    auto p2 = get<1>(viewingPlane); // on x-axis
    auto p3 = get<2>(viewingPlane); // on y-axis
    auto directionXAxis = tuple<double, double, double>(get<0>(p2) - get<0>(p1), get<1>(p2) - get<1>(p1), get<2>(p2) - get<2>(p1));

    auto rotationAxis = tuple<double, double, double>(get<0>(directionXAxis) + 0.5, get<1>(directionXAxis) + 0.5, get<2>(directionXAxis) + 1);

    switch (virtualKey)
    {
        case VirtualKey::Left:
            x_dist = -speed;
            break;
        case VirtualKey::Right:
            x_dist = speed;
            break;
        case VirtualKey::Up:
            y_dist = -speed;
            break;
        case VirtualKey::Down:
            y_dist = speed;
            break;
        case VirtualKey::W:
            viewer->rotate({ 0.5, 0.5, 1 }, rotationAxis, -1);
            break;
        case VirtualKey::A:
            viewer->rotate({ 0.5, 0.5, 1 }, { 0.5, 1.5, 1 }, 1);
            break;
        case VirtualKey::S:
            viewer->rotate({ 0.5, 0.5, 1 }, rotationAxis, 1);
            break;
        case VirtualKey::D:
            viewer->rotate({ 0.5, 0.5, 1 }, { 0.5, 1.5, 1 }, -1);
            break;
    }

    tuple<double, double, double> first_vertex = paddle_vertices[0]->getLocation();
    tuple<double, double, double> last_vertex = paddle_vertices[3]->getLocation();
    if (get<0>(first_vertex) + x_dist < 0)
    {
        x_dist = 0 - get<0>(first_vertex);
    }
    else if (get<0>(last_vertex) + x_dist > 1)
    {
        x_dist = 1 - get<0>(last_vertex);
    }

    if (get<1>(first_vertex) + y_dist < 0)
    {
        y_dist = 0 - get<1>(first_vertex);
    }
    else if (get<1>(last_vertex) + y_dist > 1)
    {
        y_dist = 1 - get<1>(last_vertex);
    }

    for (int i = 0; i < paddle_vertices.size(); i++)
    {
        paddle_vertices[i]->translate(x_dist, y_dist, z_dist);
    }
}

void MainPage::control_Loaded(Windows::UI::Xaml::RoutedEventHandler^ sender,
    Windows::UI::Xaml::RoutedEventArgs^ args)
{
    //LogMessage("in control_Loaded");
    Windows::UI::Xaml::Window::Current->CoreWindow->KeyDown += 
        ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^>(
            this, 
            &Pong::MainPage::CoreWindow_KeyDown);
    //Windows::UI::Core::CoreWindow::GetForCurrentThread()->KeyDown
        //add += CoreWindow_KeyUp;
}

MainPage::MainPage()
{
    InitializeComponent();

    viewer = display.getViewer();

    auto room_000 = display.createPoint(0, 0, 0);
    auto room_100 = display.createPoint(1, 0, 0);
    auto room_001 = display.createPoint(0, 1, 0);
    auto room_101 = display.createPoint(1, 1, 0);

    auto room_020 = display.createPoint(0, 0, 2);
    auto room_120 = display.createPoint(1, 0, 2);
    auto room_021 = display.createPoint(0, 1, 2);
    auto room_121 = display.createPoint(1, 1, 2);

    auto room_line_1 = display.createLine(room_000, room_100);
    auto room_line_2 = display.createLine(room_000, room_001);
    auto room_line_3 = display.createLine(room_100, room_101);
    auto room_line_4 = display.createLine(room_001, room_101);

    auto room_line_5 = display.createLine(room_020, room_120);
    auto room_line_6 = display.createLine(room_020, room_021);
    auto room_line_7 = display.createLine(room_120, room_121);
    auto room_line_8 = display.createLine(room_021, room_121);

    auto room_line_9 = display.createLine(room_000, room_020);
    auto room_line_10 = display.createLine(room_001, room_021);
    auto room_line_11 = display.createLine(room_100, room_120);
    auto room_line_12 = display.createLine(room_101, room_121);

    room_vertices.push_back(room_000);
    room_vertices.push_back(room_001);
    room_vertices.push_back(room_100);
    room_vertices.push_back(room_101);

    room_vertices.push_back(room_020);
    room_vertices.push_back(room_021);
    room_vertices.push_back(room_120);
    room_vertices.push_back(room_121);

    room_edges.push_back(room_line_1);
    room_edges.push_back(room_line_2);
    room_edges.push_back(room_line_3);
    room_edges.push_back(room_line_4);
    room_edges.push_back(room_line_5);
    room_edges.push_back(room_line_6);
    room_edges.push_back(room_line_7);
    room_edges.push_back(room_line_8);
    room_edges.push_back(room_line_9);
    room_edges.push_back(room_line_10);
    room_edges.push_back(room_line_11);
    room_edges.push_back(room_line_12);


    auto paddle_point_1 = display.createPoint(0.5 - paddle_side_length / 2, 0.5 - paddle_side_length / 2, 0);
    auto paddle_point_2 = display.createPoint(0.5 + paddle_side_length / 2, 0.5 - paddle_side_length / 2, 0);
    auto paddle_point_3 = display.createPoint(0.5 - paddle_side_length / 2, 0.5 + paddle_side_length / 2, 0);
    auto paddle_point_4 = display.createPoint(0.5 + paddle_side_length / 2, 0.5 + paddle_side_length / 2, 0);

    auto paddle_edge_1 = display.createLine(paddle_point_1, paddle_point_2);
    auto paddle_edge_2 = display.createLine(paddle_point_1, paddle_point_3);
    auto paddle_edge_3 = display.createLine(paddle_point_2, paddle_point_4);
    auto paddle_edge_4 = display.createLine(paddle_point_3, paddle_point_4);

    paddle_vertices.push_back(paddle_point_1);
    paddle_vertices.push_back(paddle_point_2);
    paddle_vertices.push_back(paddle_point_3);
    paddle_vertices.push_back(paddle_point_4);

    paddle_edges.push_back(paddle_edge_1);
    paddle_edges.push_back(paddle_edge_2);
    paddle_edges.push_back(paddle_edge_3);
    paddle_edges.push_back(paddle_edge_4);

    auto ball_point_1 = display.createPoint(0.5 - paddle_side_length / 4, 0.5 - paddle_side_length / 2, 0);
    auto ball_point_2 = display.createPoint(0.5 - paddle_side_length / 4, 0.5 + paddle_side_length / 2, 0);

    auto ball_point_3 = display.createPoint(0.5, 0.5 - paddle_side_length / 2, 0);
    auto ball_point_4 = display.createPoint(0.5, 0.5 + paddle_side_length / 2, 0);

    auto ball_point_5 = display.createPoint(0.5 + paddle_side_length / 4, 0.5 - paddle_side_length / 2, 0);
    auto ball_point_6 = display.createPoint(0.5 + paddle_side_length / 4, 0.5 + paddle_side_length / 2, 0);

    auto hor_line_1 = display.createLine(ball_point_1, ball_point_2);
    auto hor_line_2 = display.createLine(ball_point_3, ball_point_4);
    auto hor_line_3 = display.createLine(ball_point_5, ball_point_6);

    auto ball_point_7 = display.createPoint(0.5 - paddle_side_length / 2, 0.5 - paddle_side_length / 4, 0);
    auto ball_point_8 = display.createPoint(0.5 + paddle_side_length / 2, 0.5 - paddle_side_length / 4, 0);

    auto ball_point_9 = display.createPoint(0.5 - paddle_side_length / 2, 0.5, 0);
    auto ball_point_10 = display.createPoint(0.5 + paddle_side_length / 2, 0.5, 0);
    
    auto ball_point_11 = display.createPoint(0.5 - paddle_side_length / 2, 0.5 + paddle_side_length / 4, 0);
    auto ball_point_12 = display.createPoint(0.5 + paddle_side_length / 2, 0.5 + paddle_side_length / 4, 0);

    auto vert_line_1 = display.createLine(ball_point_7, ball_point_8);
    auto vert_line_2 = display.createLine(ball_point_9, ball_point_10);
    auto vert_line_3 = display.createLine(ball_point_11, ball_point_12);

    paddle_edges.push_back(hor_line_1);
    paddle_edges.push_back(hor_line_2);
    paddle_edges.push_back(hor_line_3);
    paddle_edges.push_back(vert_line_1);
    paddle_edges.push_back(vert_line_2);
    paddle_edges.push_back(vert_line_3);

    paddle_vertices.push_back(ball_point_1);
    paddle_vertices.push_back(ball_point_2);
    paddle_vertices.push_back(ball_point_3);
    paddle_vertices.push_back(ball_point_4);
    paddle_vertices.push_back(ball_point_5);
    paddle_vertices.push_back(ball_point_6);
    paddle_vertices.push_back(ball_point_7);
    paddle_vertices.push_back(ball_point_8);
    paddle_vertices.push_back(ball_point_9);
    paddle_vertices.push_back(ball_point_10);
    paddle_vertices.push_back(ball_point_11);
    paddle_vertices.push_back(ball_point_12);


    auto ball_000 = display.createPoint(0.5 - ball_side_length / 2, 0.5 - ball_side_length / 2, 1 - ball_side_length / 2);
    auto ball_100 = display.createPoint(0.5 + ball_side_length / 2, 0.5 - ball_side_length / 2, 1 - ball_side_length / 2);
    auto ball_001 = display.createPoint(0.5 - ball_side_length / 2, 0.5 + ball_side_length / 2, 1 - ball_side_length / 2);
    auto ball_101 = display.createPoint(0.5 + ball_side_length / 2, 0.5 + ball_side_length / 2, 1 - ball_side_length / 2);

    auto ball_020 = display.createPoint(0.5 - ball_side_length / 2, 0.5 - ball_side_length / 2, 1 + ball_side_length / 2);
    auto ball_120 = display.createPoint(0.5 + ball_side_length / 2, 0.5 - ball_side_length / 2, 1 + ball_side_length / 2);
    auto ball_021 = display.createPoint(0.5 - ball_side_length / 2, 0.5 + ball_side_length / 2, 1 + ball_side_length / 2);
    auto ball_121 = display.createPoint(0.5 + ball_side_length / 2, 0.5 + ball_side_length / 2, 1 + ball_side_length / 2);

    auto ball_line_1 = display.createLine(ball_000, ball_100);
    auto ball_line_2 = display.createLine(ball_000, ball_001);
    auto ball_line_3 = display.createLine(ball_100, ball_101);
    auto ball_line_4 = display.createLine(ball_001, ball_101);

    auto ball_line_5 = display.createLine(ball_020, ball_120);
    auto ball_line_6 = display.createLine(ball_020, ball_021);
    auto ball_line_7 = display.createLine(ball_120, ball_121);
    auto ball_line_8 = display.createLine(ball_021, ball_121);

    auto ball_line_9 = display.createLine(ball_000, ball_020);
    auto ball_line_10 = display.createLine(ball_001, ball_021);
    auto ball_line_11 = display.createLine(ball_100, ball_120);
    auto ball_line_12 = display.createLine(ball_101, ball_121);

    ball_vertices.push_back(ball_000);
    ball_vertices.push_back(ball_001);
    ball_vertices.push_back(ball_100);
    ball_vertices.push_back(ball_101);

    ball_vertices.push_back(ball_020);
    ball_vertices.push_back(ball_021);
    ball_vertices.push_back(ball_120);
    ball_vertices.push_back(ball_121);

    ball_edges.push_back(ball_line_1);
    ball_edges.push_back(ball_line_2);
    ball_edges.push_back(ball_line_3);
    ball_edges.push_back(ball_line_4);
    ball_edges.push_back(ball_line_5);
    ball_edges.push_back(ball_line_6);
    ball_edges.push_back(ball_line_7);
    ball_edges.push_back(ball_line_8);
    ball_edges.push_back(ball_line_9);
    ball_edges.push_back(ball_line_10);
    ball_edges.push_back(ball_line_11);
    ball_edges.push_back(ball_line_12);
    

    for (int i = 0; i < paddle_edges.size(); i++)
    {
        paddle_edges[i]->setColor(&gp::Color(255, 0, 0));
    }

    for (int i = 0; i < ball_edges.size(); i++)
    {
        ball_edges[i]->setColor(&gp::Color(0, 0, 255));
    }

    viewer->translate(-0.5, -0.5, -0.5);
    viewer->translate(3, -0.2, 1);

    viewer->rotate({ 0, 1, 0 }, -90);
    viewer->rotate({ 0, 0, 1 }, -10);
}

void MainPage::CanvasControl_Draw(CanvasAnimatedControl^ sender, CanvasAnimatedDrawEventArgs^ args)
{
    for (int i = 0; i < room_edges.size(); i++)
    {
        room_edges[i]->draw();
    }

    for (int i = 0; i < paddle_edges.size(); i++)
    {
        paddle_edges[i]->draw();
    }

    if (!lost)
    {
        tuple<double, double, double> first_vertex = ball_vertices[0]->getLocation();
        tuple<double, double, double> last_vertex = ball_vertices[7]->getLocation();

        if (get<2>(first_vertex) + ball_z_velocity < 0)
        {
            double face_x_center = (get<0>(first_vertex) + get<0>(last_vertex)) / 2;
            double face_y_center = (get<1>(first_vertex) + get<1>(last_vertex)) / 2;

            tuple<double, double, double> paddle_first = paddle_vertices[0]->getLocation();
            tuple<double, double, double> paddle_second = paddle_vertices[3]->getLocation();

            if ((face_x_center + ball_side_length / 2) > get<0>(paddle_first) && (face_x_center - ball_side_length / 2) < get<0>(paddle_second) &&
                (face_y_center + ball_side_length / 2) > get<1>(paddle_first) && (face_y_center - ball_side_length / 2) < get<1>(paddle_second))
            {
                ball_z_velocity *= -1;
                score++;

                ball_x_velocity += sgn(ball_x_velocity) * 0.003;
                ball_y_velocity += sgn(ball_y_velocity) * 0.003;
                ball_z_velocity += sgn(ball_z_velocity) * 0.003;
            }
            else
            {
                lost = true;
                last_translation = true;
            }

        }
        else if (get<2>(last_vertex) + ball_z_velocity > 2)
        {
            ball_z_velocity *= -1;

            ball_x_velocity += sgn(ball_x_velocity) * 0.003;
            ball_y_velocity += sgn(ball_y_velocity) * 0.003;
            ball_z_velocity += sgn(ball_z_velocity) * 0.003;
        }

        if (get<0>(first_vertex) + ball_x_velocity < 0)
        {
            ball_x_velocity *= -1;
        }
        else if (get<0>(last_vertex) + ball_x_velocity > 1)
        {
            ball_x_velocity *= -1;
        }

        if (get<1>(first_vertex) + ball_y_velocity < 0)
        {
            ball_y_velocity *= -1;
        }
        else if (get<1>(last_vertex) + ball_y_velocity > 1)
        {
            ball_y_velocity *= -1;
        }
    }

    
    if (!lost || last_translation)
    {
        for (int i = 0; i < ball_vertices.size(); i++)
        {
            ball_vertices[i]->translate(ball_x_velocity, ball_y_velocity, ball_z_velocity);
        }

        if (last_translation)
        {
            last_translation = false;
        }
    }

    for (int i = 0; i < ball_edges.size(); i++)
    {
        ball_edges[i]->draw();
    }

    display.flip(args->DrawingSession);

    if (score > high_score)
    {
        high_score = score;
    }

    args->DrawingSession->DrawText("Score: " + score, 15, 15, Windows::UI::Colors::Black);
    args->DrawingSession->DrawText("High Score: " + high_score, 15, 40, Windows::UI::Colors::Black);
}

void MainPage::StartNewGame(Windows::UI::Xaml::RoutedEventHandler^ sender,
    Windows::UI::Xaml::RoutedEventArgs^ args)
{
    score = 0;

    ball_vertices[0]->move(0.5 - ball_side_length / 2, 0.5 - ball_side_length / 2, 1 - ball_side_length / 2);
    ball_vertices[1]->move(0.5 + ball_side_length / 2, 0.5 - ball_side_length / 2, 1 - ball_side_length / 2);
    ball_vertices[2]->move(0.5 - ball_side_length / 2, 0.5 + ball_side_length / 2, 1 - ball_side_length / 2);
    ball_vertices[3]->move(0.5 + ball_side_length / 2, 0.5 + ball_side_length / 2, 1 - ball_side_length / 2);

    ball_vertices[4]->move(0.5 - ball_side_length / 2, 0.5 - ball_side_length / 2, 1 + ball_side_length / 2);
    ball_vertices[5]->move(0.5 + ball_side_length / 2, 0.5 - ball_side_length / 2, 1 + ball_side_length / 2);
    ball_vertices[6]->move(0.5 - ball_side_length / 2, 0.5 + ball_side_length / 2, 1 + ball_side_length / 2);
    ball_vertices[7]->move(0.5 + ball_side_length / 2, 0.5 + ball_side_length / 2, 1 + ball_side_length / 2);

    ball_x_velocity = -0.01;
    ball_y_velocity = -0.01;
    ball_z_velocity = -0.02;

    lost = false;
    last_translation = false;
}

void MainPage::MouseEnter(Windows::UI::Xaml::RoutedEventHandler^ sender,
    Windows::UI::Xaml::RoutedEventArgs^ args)
{
    startNewGame->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Black);
}

void MainPage::MouseLeave(Windows::UI::Xaml::RoutedEventHandler^ sender,
    Windows::UI::Xaml::RoutedEventArgs^ args)
{
    startNewGame->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Black);
}
