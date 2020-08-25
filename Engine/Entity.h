#pragma once

#include <vector>
#include "Vec2.h"
#include "Drawable.h"

class Entity
{
public:
	Entity( std::vector<Vec2> model,
		const Vei2& pos = Vei2::Zero(),
		Color c = Colors::Yellow )
		:
		model( model ),
		pos( pos ),
		c( c )
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
	void SetAngle( float a )
	{
		angle = a;
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
	Drawable GetDrawable() const
	{
		Drawable d{ model,c };
		d.Scale( scale );
		d.Rotate( angle );
		d.Translate( pos );
		return( d );
	}
	void SetColor( Color c )
	{
		this->c = c;
	}
	float GetAngle()
	{
		return( angle );
	}
private:
	Color c;
	float scale = 1.0f;
	float angle = 0.0f;
	Vec2 pos = Vec2::Zero();
	std::vector<Vec2> model;
};