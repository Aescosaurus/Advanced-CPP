#pragma once

#include "CoordinateTransformer.h"
#include "RectF.h"
#include "ChiliMath.h"

class Camera
{
public:
	Camera( CoordinateTransformer& ct )
		:
		ct( ct )
	{}

	void Draw( Drawable& drawable ) const
	{
		drawable.ApplyTransformation(
			Mat3::Rotation( angle ) *
			Mat3::Scale( scale ) *
			Mat3::Translation( -pos.x,-pos.y ) );
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
	void SetAngle( float angle )
	{
		this->angle = angle;
	}

	const Vec2& GetPos() const
	{
		return( pos );
	}
	float GetScale() const
	{
		return( scale );
	}
	float GetAngle() const
	{
		return( angle );
	}
	RectF GetViewportRect() const
	{
		const float zoom = 1.0f / scale;
		const float diag = sqrt(
			sq( float( Graphics::ScreenWidth / 2 ) * zoom ) +
			sq( float( Graphics::ScreenHeight / 2 ) * zoom ) );
		return( RectF::FromCenter( pos,diag,diag ) );
	}
private:
	Vec2 pos = Vec2::Zero();
	float scale = 1.0f;
	float angle = 0.0f;
	CoordinateTransformer& ct;
};