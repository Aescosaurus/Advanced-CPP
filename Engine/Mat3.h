#pragma once

#include "Vec3.h"

template<typename T>
class Mat3_
{
public:
	Vec2_<T> operator*( const Vec2_<T>& v ) const
	{
		return( Vec2_<T>{ *this * Vec3_( v ) } );
	}
	Vec3_<T> operator*( const Vec3_<T>& v ) const
	{
		Vec3_<T> vOut;
		vOut.x = cells[0][0] * v.x + cells[0][1] * v.y + cells[0][2] * v.w;
		vOut.y = cells[1][0] * v.x + cells[1][1] * v.y + cells[1][2] * v.w;
		vOut.w = cells[2][0] * v.x + cells[2][1] * v.y + cells[2][2] * v.w;
		return( vOut );
	}
	Mat3_ operator*( const Mat3_& rhs ) const
	{
		Mat3_ out;
		for( int rowLeft = 0; rowLeft < 3; ++rowLeft )
		{
			for( int colRight = 0; colRight < 3; ++colRight )
			{
				out.cells[rowLeft][colRight] = T( 0.0 );
				for( int i = 0; i < 3; ++i )
				{
					out.cells[rowLeft][colRight] += cells[rowLeft][i] *
						rhs.cells[i][colRight];
				}
			}
		}
		return( out );
	}
	static Mat3_ Scale( T factor )
	{
		return( Mat3_{
			factor,T( 0.0 ),T( 0 ),
			T( 0.0 ),factor,T( 0 ),
			T( 0 ),T( 0 ),T( 1 )
			} );
	}
	static Mat3_ Identity()
	{
		return( Scale( T( 1.0 ) ) );
	}
	static Mat3_ FlipY()
	{
		return( Mat3_{
			T( 1 ),T( 0 ),T( 0 ),
			T( 0 ),T( -1 ),T( 0 ),
			T( 0 ),T( 0 ),T( 1 )
			} );
	}
	static Mat3_ Rotation( T theta )
	{
		const auto cosT = std::cos( theta );
		const auto sinT = std::sin( theta );
		return( Mat3_{
			cosT,-sinT,T( 0 ),
			sinT,cosT,T( 0 ),
			T( 0 ),T( 0 ),T( 1 )
			} );
	}
	static Mat3_ Translation( T x,T y )
	{
		return( Mat3_{
			T( 1 ),T( 0 ),x,
			T( 0 ),T( 1 ),y,
			T( 0 ),T( 0 ),T( 1 )
			} );
	}
	static Mat3_ ScaleIndependent( T x,T y )
	{
		return( Mat3_{
			T( x ),T( 0 ),T( 0 ),
			T( 0 ),T( y ),T( 0 ),
			T( 0 ),T( 0 ),T( 1 )
			} );
	}
public:
	// [row][col]
	T cells[3][3];
};

using Mat3 = Mat3_<float>;
using Mad3 = Mat3_<double>;