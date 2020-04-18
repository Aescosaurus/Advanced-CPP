/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Star.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ct( gfx ),
	cam( ct ),
	rng( std::random_device{}() )
{
	// entities.emplace_back( Star::Make( 100.0f,50.0f ),Vec2{ 460.0f,0.0f } );
	// entities.emplace_back( Star::Make( 150.0f,50.0f ),Vec2{ 150.0f,300.0f } );
	// entities.emplace_back( Star::Make( 100.0f,50.0f ),Vec2{ 250.0f,-200.0f } );
	// entities.emplace_back( Star::Make( 150.0f,50.0f ),Vec2{ -250.0f,200.0f } );
	// entities.emplace_back( Star::Make( 100.0f,50.0f ),Vec2{ 0.0f,0.0f } );
	// entities.emplace_back( Star::Make( 200.0f,50.0f ),Vec2{ -150.0f,-300.0f } );
	// entities.emplace_back( Star::Make( 100.0f,50.0f ),Vec2{ 400.0f,300.0f } );
	const auto min = Vec2{ -4000,-2100 };
	const auto max = Vec2{ 4000,2100 };
	for( int i = 0; i < 800; ++i )
	{
		std::uniform_real_distribution<float> xDist{ min.x,max.x };
		std::uniform_real_distribution<float> yDist{ min.y,max.y };
		std::uniform_real_distribution<float> innerDist{ 20.0f,90.0f };
		std::uniform_real_distribution<float> outerDist{ 50.0f,200.0f };
		std::uniform_int_distribution<int> flareDist{ 3,10 };
		std::uniform_int_distribution<int> rDist{ 0,255 };
		std::uniform_int_distribution<int> gDist{ 0,255 };
		std::uniform_int_distribution<int> bDist{ 0,255 };
		const auto pos = Vec2{ xDist( rng ),yDist( rng ) };
		const auto outerSize = outerDist( rng );
		bool valid = true;
		for( const auto& e : entities )
		{
			const auto& poly = e.GetPolyline();
			const auto otherOuter = std::max(
				( poly[0] - e.GetPos() ).GetLength(),
				( poly[1] - e.GetPos() ).GetLength() );
			if( ( pos - e.GetPos() ).GetLength() < outerSize + otherOuter )
			{
				valid = false;
			}
		}
		if( valid )
		{
			entities.emplace_back( Entity{ Star::Make(
				outerSize,innerDist( rng ),
				flareDist( rng ) ),pos,
				Colors::MakeRGB( rDist( rng ),gDist( rng ),bDist( rng ) ) } );
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float speed = 3.0f;
	// if( wnd.kbd.KeyIsPressed( VK_UP ) ) cam.MoveBy( Vec2::Up() * speed );
	// if( wnd.kbd.KeyIsPressed( VK_DOWN ) ) cam.MoveBy( Vec2::Down() * speed );
	// if( wnd.kbd.KeyIsPressed( VK_LEFT ) ) cam.MoveBy( Vec2::Left() * speed );
	// if( wnd.kbd.KeyIsPressed( VK_RIGHT ) ) cam.MoveBy( Vec2::Right() * speed );

	while( !wnd.mouse.IsEmpty() )
	{
		const auto e = wnd.mouse.Read();
		if( e.GetType() == Mouse::Event::Type::WheelUp )
		{
			cam.SetScale( cam.GetScale() * 1.05f );
		}
		else if( e.GetType() == Mouse::Event::Type::WheelDown )
		{
			cam.SetScale( cam.GetScale() * 0.95f );
		}
	}
	if( wnd.mouse.LeftIsPressed() )
	{
		auto diff = Vec2( wnd.mouse.GetPos() - oldMousePos );
		diff.x *= -1;
		cam.MoveBy( diff / cam.GetScale() );
	}
	oldMousePos = wnd.mouse.GetPos();

	for( auto& e : entities )
	{
		e.Update();
	}
}

void Game::ComposeFrame()
{
	for( const auto& entity : entities )
	{
		cam.Draw( entity.GetDrawable() );
	}
}
