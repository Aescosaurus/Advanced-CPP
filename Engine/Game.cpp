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
#include "Mat3.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ct( gfx ),
	cam( ct ),
	camCtrl( wnd.mouse,wnd.kbd,cam )
{
	std::mt19937 rng{ std::random_device{}() };
	std::uniform_real_distribution<float> xDist{ -worldWidth / 2,worldWidth / 2 };
	std::uniform_real_distribution<float> yDist{ -worldHeight / 2,worldHeight / 2 };
	std::normal_distribution<float> radDist{ meanStarRadius,devStarRadius };
	std::normal_distribution<float> ratDist{ meanInnerRatio,devInnerRatio };
	std::normal_distribution<float> flareDist( meanFlares,devFlares );
	const Color colors[] = { Colors::Blue,Colors::Cyan,Colors::Green,
		Colors::Magenta,Colors::Red,Colors::Yellow };
	std::uniform_int_distribution<size_t> colorSampler( 0,std::end( colors ) - std::begin( colors ) );
	std::normal_distribution<float> colorFreqDist{ meanColorFreq,devColorFreq };
	std::uniform_real_distribution<float> phaseDist( 0.0f,2.0f * 3.14159f );
	std::normal_distribution<float> radiusAmplitudeDist( meanRadiusAmplitude,devRadiusAmplitude );
	std::normal_distribution<float> radiusFreqDist( meanRadiusFreq,devRadiusFreq );
	std::uniform_real_distribution<float> rotSpeedDist( minRotSpeed,maxRotSpeed );
	while( stars.size() < nStars )
	{
		const auto rad = std::clamp( radDist( rng ),minStarRadius,maxStarRadius );
		const float radiusAmplitude = std::clamp( radiusAmplitudeDist( rng ),minRadiusAmplitude,maxRadiusAmplitude );
		const float maxRad = rad * ( 1.0f + radiusAmplitude );
		const Vec2 pos = { xDist( rng ),yDist( rng ) };
		if( std::any_of( stars.begin(),stars.end(),[&]( const StarBro& sb )
		{ return( ( sb.GetPos() - pos ).GetLength() < maxRad + sb.GetMaxRadius() ); } ) )
		{
			continue;
		}

		const auto rat = std::clamp( ratDist( rng ),minInnerRatio,maxInnerRatio );
		const Color c = colors[colorSampler( rng )];
		const int nFlares = std::clamp( int( flareDist( rng ) ),minFlares,maxFlares );
		const float colorFreq = std::clamp( colorFreqDist( rng ),minColorFreq,maxColorFreq );
		const float colorPhase = phaseDist( rng );
		const float radiusFreq = radiusFreqDist( rng );
		const float radiusPhase = phaseDist( rng );
		const float rotSpeed = rotSpeedDist( rng );
		stars.emplace_back( pos,rad,rat,nFlares,c,colorFreq,colorPhase,
			radiusAmplitude,radiusFreq,radiusPhase,rotSpeed );
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
	const float dt = ft.Mark();

	camCtrl.Update( dt );

	for( auto& s : stars )
	{
		s.Update( dt );
	}
}

void Game::ComposeFrame()
{
	const auto vp = cam.GetViewportRect();
	for( const auto& s : stars )
	{
		if( s.GetBoundingRect().IsOverlappingWith( vp ) )
		{
			cam.Draw( s.GetDrawable() );
		}
	}
}
