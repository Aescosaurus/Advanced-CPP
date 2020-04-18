#pragma once

#include <vector>
#include "Vec2.h"
#include "Graphics.h"

class Drawable
{
public:
	Drawable( const std::vector<Vec2>& model,Color c )
		:
		model( model ),
		c( c )
	{}

	void Render( Graphics& gfx )
	{
		auto temp = model;
		bool draw = false;
		for( auto& v : temp )
		{
			v.x *= scale.x;
			v.y *= scale.y;
			v += translation;
			if( v.x >= 0 && v.x < Graphics::ScreenWidth ||
				v.y >= 0 && v.y < Graphics::ScreenHeight )
			{
				draw = true;
			}
		}
		if( draw ) gfx.DrawClosedPolyline( temp,c );
	}

	void Translate( const Vec2& translation )
	{
		this->translation += translation;
	}
	void Scale( float scale )
	{
		this->scale *= scale;
		translation *= scale;
	}
	void Scale( float xScale,float yScale )
	{
		scale.x *= xScale;
		scale.y *= yScale;
		translation.x *= xScale;
		translation.y *= yScale;
	}
private:
	Color c;
	const std::vector<Vec2>& model;
	Vec2 translation = Vec2::Zero();
	Vec2 scale = Vec2::One();
};