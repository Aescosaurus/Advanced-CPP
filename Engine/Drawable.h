#pragma once

#include <vector>
#include "Vec2.h"
#include "Graphics.h"
#include "Mat3.h"

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
		gfx.DrawClosedPolyline( *model,transformation,c );
	}

	void ApplyTransformation( const Mat3& transformation )
	{
		this->transformation = transformation * this->transformation;
	}
private:
	Color c;
	const std::vector<Vec2>* model;
	Mat3 transformation = Mat3::Identity();
};