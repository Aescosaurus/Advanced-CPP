#pragma once

#include <cmath>
#include "Vec2.h"

template<typename T>
class Vec3_
{
public:
	constexpr Vec3_() = default;
	constexpr Vec3_( T x,T y )
		:
		x( x ),
		y( y )
	{}
	constexpr Vec3_( T amount ) = delete;
	explicit Vec3_( const Vec2_<T>& v2 )
		:
		Vec3_( v2.x,v2.y )
	{}
	explicit operator Vec2_<T>() const
	{
		return( Vec2_{ x,y } );
	}
	template<typename T2>
	explicit operator Vec3_<T2>() const
	{
		return( Vec3_<T2>{ T2( x ),T2( y ),T2( w ) } );
	}

	constexpr Vec3_ operator+( const Vec3_& rhs ) const
	{
		return Vec3_( x + rhs.x,y + rhs.y );
	}
	constexpr Vec3_& operator+=( const Vec3_& rhs )
	{
		return *this = *this + rhs;
	}
	constexpr Vec3_ operator*( T rhs ) const
	{
		return Vec3_( x * rhs,y * rhs );
	}
	constexpr Vec3_& operator*=( T rhs )
	{
		return *this = *this * rhs;
	}
	constexpr Vec3_ operator-( const Vec3_& rhs ) const
	{
		return Vec3_( x - rhs.x,y - rhs.y );
	}
	constexpr Vec3_& operator-=( const Vec3_& rhs )
	{
		return *this = *this - rhs;
	}
	constexpr Vec3_ operator/( T rhs ) const
	{
		return Vec3_{ x / rhs,y / rhs };
	}
	constexpr Vec3_& operator/=( T rhs )
	{
		*this = ( *this ) / rhs;
		return *this;
	}
	constexpr Vec3_ operator%( T rhs ) const
	{
		return Vec3_{ x % rhs,y % rhs };
	}
	constexpr Vec3_& operator%=( T rhs ) const
	{
		*this = ( *this ) % rhs;
		return( *this );
	}
	constexpr Vec3_ operator-() const
	{
		return( Vec3_<T>{ -x,-y } );
	}

	constexpr bool operator==( const Vec3_<T>& rhs ) const
	{
		return( x == rhs.x && y == rhs.y );
	}
	constexpr bool operator!=( const Vec3_<T>& rhs ) const
	{
		return( !( *this == rhs ) );
	}

	constexpr T GetLength() const
	{
		return T( std::sqrt( GetLengthSq() ) );
	}
	constexpr T GetLengthSq() const
	{
		return x * x + y * y;
	}
	constexpr T GetAngle() const
	{
		return( std::atan2( y,x ) );
	}

	constexpr Vec3_& Normalize()
	{
		return *this = GetNormalized();
	}
	constexpr Vec3_ GetNormalized() const
	{
		const T len = GetLength();
		if( len != T( 0.0f ) )
		{
			return *this * ( 1.0f / len );
		}
		return *this;
	}
	Vec3_& Rotate( T angle )
	{
		const T cosTheta = cos( angle );
		const T sinTheta = sin( angle );

		const T newX = x * cosTheta - y * sinTheta;
		y = x * sinTheta + y * cosTheta;
		x = newX;

		return( *this );
	}
	Vec3_ GetRotated( T angle ) const
	{
		return( Vec3_{ *this }.Rotate( angle ) );
	}
	T operator*( const Vec3_& rhs ) const
	{
		return( x * rhs.x + y * rhs.y );
	}

	static constexpr Vec3_ Up()
	{
		return Vec3_{ T( 0.0f ),T( 1.0f ) };
	}
	static constexpr Vec3_ Down()
	{
		return Vec3_{ T( 0.0f ),T( -1.0f ) };
	}
	static constexpr Vec3_ Left()
	{
		return Vec3_{ T( -1.0f ),T( 0.0f ) };
	}
	static constexpr Vec3_ Right()
	{
		return Vec3_{ T( 1.0f ),T( 0.0f ) };
	}
	static constexpr Vec3_ Zero()
	{
		return( Vec3_<T>{ T( 0.0 ),T( 0.0 ) } );
	}
	static constexpr Vec3_ One()
	{
		return( Vec3_<T>{ T( 1.0 ),T( 1.0 ) } );
	}
	static constexpr Vec3_ FromAngle( float angle )
	{
		return( Vec3_{ T( std::cos( angle ) ),
			T( std::sin( angle ) ) } );
	}

	constexpr Vec3_ X() const
	{
		return( Vec3_{ x,T( 0 ) } );
	}
	constexpr Vec3_ Y() const
	{
		return( Vec3_{ T( 0 ),y } );
	}
public:
	T x;
	T y;
	T w = T( 1 );
};

typedef Vec3_<float> Vec3;
typedef Vec3_<int> Vei3;