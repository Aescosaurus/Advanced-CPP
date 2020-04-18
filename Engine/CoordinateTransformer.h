#pragma once

#include <vector>
#include "Vec2.h"
#include "Graphics.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer( Graphics& gfx )
		:
		gfx( gfx )
	{}
	void DrawClosedPolyline( std::vector<Vec2> poly,Color c )
	{
		const auto offset = Vec2{ float( Graphics::ScreenWidth / 2 ),
			float( Graphics::ScreenHeight / 2 ) };
		for( auto& v : poly )
		{
			v.y *= -1;
			v += offset;
		}
		gfx.DrawClosedPolyline( poly,c );
	}
private:
	Graphics& gfx;
};