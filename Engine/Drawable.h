#pragma once

#include <vector>
#include "Vec2.h"
#include "Graphics.h"

class Drawable
{
public:
	Drawable( const std::vector<Vec2>& model,Color c )
		:
		model( &model ),
		c( c )
	{}

	void Render( Graphics& gfx )
	{
		gfx.DrawClosedPolyline( *model,translation,scale,angle,c );
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
	void Rotate( float angle )
	{
		this->angle += angle;
		translation.Rotate( angle );
	}
private:
	Color c;
	const std::vector<Vec2>* model;
	float angle = 0.0f;
	Vec2 translation = Vec2::Zero();
	Vec2 scale = Vec2::One();
};