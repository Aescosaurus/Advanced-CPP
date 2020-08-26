#pragma once

#include "Vec2.h"

template<typename T>
class Mat2_
{
public:
	Vec2_<T> operator*( const Vec2_<T>& v ) const
	{
		Vec2_<T> vOut;
		vOut.x = cells[0][0] * v.x + cells[0][1] * v.y;
		vOut.y = cells[1][0] * v.x + cells[1][1] * v.y;
		return( vOut );
	}
	Mat2_ operator*( const Mat2_& rhs ) const
	{
		Mat2_ out;
		for( int rowLeft = 0; rowLeft < 2; ++rowLeft )
		{
			for( int colRight = 0; colRight < 2; ++colRight )
			{
				out.cells[rowLeft][colRight] = T( 0.0 );
				for( int i = 0; i < 2; ++i )
				{
					out.cells[rowLeft][colRight] += cells[rowLeft][i] *
						rhs.cells[i][colRight];
				}
			}
		}
		return( out );
	}
	Mat2_& operator*=( const Mat2_& rhs )
	{
		*this = *this * rhs;
		return( *this );
	}
	static Mat2_ Scale( T factor )
	{
		return( Mat2_{ factor,T( 0.0 ),
			T( 0.0 ),factor } );
	}
	static Mat2_ Identity()
	{
		return( Scale( T( 1.0 ) ) );
	}
	static Mat2_ FlipY()
	{
		return( Mat2_{ T( 1.0 ),T( 0.0 ),
			T( 0.0 ),T( 1.0 ) } );
	}
	static Mat2_ Rotation( T theta )
	{
		const auto cosT = std::cos( theta );
		const auto sinT = std::sin( theta );
		return( Mat2_{ cosT,-sinT,
			sinT,cosT } );
	}
public:
	// [row][col]
	T cells[2][2];
};

using Mat2 = Mat2_<float>;
using Mad2 = Mat2_<double>;