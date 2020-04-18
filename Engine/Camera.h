#pragma once

#include "CoordinateTransformer.h"

class Camera
{
public:
	Camera( CoordinateTransformer& ct )
		:
		ct( ct )
	{}

	void Draw( Drawable& drawable ) const
	{
		drawable.Translate( -pos );
		drawable.Scale( scale );
		ct.Draw( drawable );
	}

	void MoveBy( const Vec2& amount )
	{
		pos += amount;
	}
	void MoveTo( const Vec2& loc )
	{
		pos = loc;
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
private:
	Vec2 pos = Vec2::Zero();
	float scale = 1.0f;
	CoordinateTransformer& ct;
};