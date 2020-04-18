#pragma once

#include <vector>
#include "Vec2.h"
#include "Graphics.h"

class Drawable
{
public:
	Drawable( std::vector<Vec2> model,Color c )
		:
		model( std::move( model ) ),
		c( c )
	{}

	void Render( Graphics& gfx )
	{
		for( auto& v : model )
		{
			v.x *= scale.x;
			v.y *= scale.y;
			v += translation;
		}
		gfx.DrawClosedPolyline( model,c );
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
	std::vector<Vec2> model;
	Vec2 translation = Vec2::Zero();
	Vec2 scale = Vec2::One();
};