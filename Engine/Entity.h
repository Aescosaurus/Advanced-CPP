#pragma once

#include <vector>
#include "Vec2.h"

class Entity
{
public:
	Entity( std::vector<Vec2> model )
		:
		model( model )
	{}

	void SetPos( const Vec2& newPos )
	{
		pos = newPos;
	}
	void TranslateBy( const Vec2& move )
	{
		pos += move;
	}
	void SetScale( float s )
	{
		scale = s;
	}

	const Vec2& GetPos() const
	{
		return( pos );
	}
	float GetScale() const
	{
		return( scale );
	}
	std::vector<Vec2> GetPolyline() const
	{
		auto poly = model;
		for( auto& v : poly )
		{
			v *= scale;
			v += pos;
		}
		return( poly );
	}
private:
	float scale = 1.0f;
	Vec2 pos = Vec2::Zero();
	std::vector<Vec2> model;
};