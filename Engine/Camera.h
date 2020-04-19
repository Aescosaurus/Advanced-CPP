#pragma once

#include "CoordinateTransformer.h"
#include "RectF.h"

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
	RectF GetViewportRect() const
	{
		const float zoom = 1.0f / scale;
		return( RectF::FromCenter(
			pos,
			float( Graphics::ScreenWidth / 2 ) * zoom,
			float( Graphics::ScreenHeight / 2 ) * zoom
		) );
	}
private:
	Vec2 pos = Vec2::Zero();
	float scale = 1.0f;
	CoordinateTransformer& ct;
};