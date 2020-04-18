#pragma once

#include <vector>
#include "Vec2.h"
#include "Graphics.h"
#include "Drawable.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer( Graphics& gfx )
		:
		gfx( gfx )
	{}
	void Draw( Drawable& drawable ) const
	{
		const auto offset = Vec2{ float( Graphics::ScreenWidth / 2 ),
			float( Graphics::ScreenHeight / 2 ) };
		drawable.Scale( 1.0f,-1.0f );
		drawable.Translate( offset );
		drawable.Render( gfx );
	}
private:
	Graphics& gfx;
};