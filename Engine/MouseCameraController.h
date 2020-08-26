#pragma once

#include "Camera.h"
#include "Mouse.h"
#include "ChiliMath.h"
#include "Keyboard.h"

class MouseCameraController
{
public:
	MouseCameraController( Mouse& mouse,const Keyboard& kbd,Camera& cam )
		:
		mouse( mouse ),
		cam( cam ),
		kbd( kbd )
	{}

	void Update( float dt )
	{
		if( kbd.KeyIsPressed( 'Q' ) )
		{
			cam.SetAngle( cam.GetAngle() - rotSpeed * dt );
		}
		if( kbd.KeyIsPressed( 'E' ) )
		{
			cam.SetAngle( cam.GetAngle() + rotSpeed * dt );
		}

		while( !mouse.IsEmpty() )
		{
			const auto e = mouse.Read();
			switch( e.GetType() )
			{
			case Mouse::Event::Type::LPress:
				engaged = true;
				lastPos = Vec2( e.GetPos() );
				break;
			case Mouse::Event::Type::LRelease:
				engaged = false;
				break;
			case Mouse::Event::Type::WheelUp:
				cam.SetScale( cam.GetScale() * zoomFactor );
				break;
			case Mouse::Event::Type::WheelDown:
				cam.SetScale( cam.GetScale() / zoomFactor );
				break;
			}
		}

		if( engaged )
		{
			const auto curPos = Vec2( mouse.GetPos() );
			auto delta = curPos - lastPos;
			delta.x = -delta.x;

			delta.Rotate( -cam.GetAngle() );
			cam.MoveBy( delta / cam.GetScale() );

			lastPos = curPos;
		}
	}
private:
	Mouse& mouse;
	const Keyboard& kbd;
	Camera& cam;
	Vei2 lastPos = Vei2::Zero();
	bool engaged = false;
	static constexpr float zoomFactor = 1.05f;
	static constexpr auto rotSpeed = PI;
};