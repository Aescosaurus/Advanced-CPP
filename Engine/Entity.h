#pragma once

#include <vector>
#include "Vec2.h"
#include "Drawable.h"
#include <random>

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
	{
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> dist{ 0.001f,0.1f };
		timeScale = dist( rng );
	}

	void Update()
	{
		scale = std::sin( time );
		time += timeScale;
	}

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
	Drawable GetDrawable() const
	{
		Drawable d{ model,Colors::Lerp( c,Colors::White,
			( std::cos( time ) + 1 ) / 2.0f ) };
		d.Scale( scale );
		d.Translate( pos );
		return( d );
	}
private:
	Color c;
	float scale = 1.0f;
	Vec2 pos = Vec2::Zero();
	std::vector<Vec2> model;
	float time = 0.0f;
	float timeScale;
};