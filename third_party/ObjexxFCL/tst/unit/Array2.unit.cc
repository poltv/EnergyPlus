// ObjexxFCL::Array2 Unit Tests
//
// Project: Objexx Fortran Compatibility Library (ObjexxFCL)
//
// Version: 4.0.0
//
// Language: C++
//
// Copyright (c) 2000-2015 Objexx Engineering, Inc. All Rights Reserved.
// Use of this source code or any derivative of it is restricted by license.
// Licensing is available from Objexx Engineering, Inc.:  http://objexx.com

// Google Test Headers
#include <gtest/gtest.h>

// ObjexxFCL Headers
#include <ObjexxFCL/Array2.all.hh>
#include <ObjexxFCL/Array.functions.hh>
#include "ObjexxFCL.unit.hh"

// C++ Headers
#include <string>

using namespace ObjexxFCL;
typedef  IndexRange  IR;

TEST( Array2Test, ConstructDefault )
{
	Array2D_int A1;
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 0u, A1.size1() );
	EXPECT_EQ( 0u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 0, A1.u1() );
	EXPECT_EQ( 0, A1.u2() );
	EXPECT_EQ( Array2D_int::IR(), A1.I1() );
	EXPECT_EQ( Array2D_int::IR(), A1.I2() );
	EXPECT_FALSE( A1.initializer_active() );

	Array2D_int const C1;
	EXPECT_EQ( 0u, C1.size() );
	EXPECT_EQ( 0u, C1.size1() );
	EXPECT_EQ( 0u, C1.size2() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 1, C1.l2() );
	EXPECT_EQ( 0, C1.u1() );
	EXPECT_EQ( 0, C1.u2() );
	EXPECT_EQ( Array2D_int::IR(), C1.I1() );
	EXPECT_EQ( Array2D_int::IR(), C1.I2() );
	EXPECT_FALSE( C1.initializer_active() );
}

TEST( Array2Test, ConstructCopy )
{
	Array2D_int A1;
	Array2D_int A2( A1 );
	EXPECT_EQ( A1.size(), A2.size() );
	EXPECT_EQ( A1.size1(), A2.size1() );
	EXPECT_EQ( A1.size2(), A2.size2() );
	EXPECT_EQ( A1.l1(), A2.l1() );
	EXPECT_EQ( A1.u1(), A2.u1() );
	EXPECT_EQ( A1.l2(), A2.l2() );
	EXPECT_EQ( A1.u2(), A2.u2() );
	EXPECT_EQ( A1.I1(), A2.I1() );
	EXPECT_EQ( A1.I2(), A2.I2() );
	EXPECT_EQ( A1.initializer_active(), A2.initializer_active() );
	EXPECT_TRUE( conformable( A1, A2 ) );
	EXPECT_TRUE( equal_dimensions( A1, A2 ) );
	EXPECT_TRUE( eq( A1, A2 ) );

	Array2D_int const C1;
	Array2D_int const C2( C1 );
	EXPECT_EQ( C1.size(), C2.size() );
	EXPECT_EQ( C1.size1(), C2.size1() );
	EXPECT_EQ( C1.size2(), C2.size2() );
	EXPECT_EQ( C1.l2(), C2.l2() );
	EXPECT_EQ( C1.u2(), C2.u2() );
	EXPECT_EQ( C1.l1(), C2.l1() );
	EXPECT_EQ( C1.u1(), C2.u1() );
	EXPECT_EQ( C1.I1(), C2.I1() );
	EXPECT_EQ( C1.I2(), C2.I2() );
	EXPECT_EQ( C1.initializer_active(), C2.initializer_active() );
	EXPECT_TRUE( eq( C1, C2 ) );
}

TEST( Array2Test, ConstructOtherData )
{
	// Avoid dependency on static list constructor
	Array2D_double A1( 2, 3 );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			A1( i1, i2 ) = i1 + i2;
		}
	}
	Array2D_int A2( A1 );
	EXPECT_EQ( A1.size(), A2.size() );
	EXPECT_EQ( A1.size1(), A2.size1() );
	EXPECT_EQ( A1.size2(), A2.size2() );
	EXPECT_EQ( A1.l1(), A2.l1() );
	EXPECT_EQ( A1.u1(), A2.u1() );
	EXPECT_EQ( A1.l2(), A2.l2() );
	EXPECT_EQ( A1.u2(), A2.u2() );
	EXPECT_EQ( A1.I1(), A2.I1() );
	EXPECT_EQ( A1.I2(), A2.I2() );
	EXPECT_EQ( A1.initializer_active(), A2.initializer_active() );
	EXPECT_TRUE( conformable( A1, A2 ) );
	EXPECT_TRUE( equal_dimensions( A1, A2 ) );
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			EXPECT_EQ( int( A1( i1, i2 ) ), A2( i1, i2 ) );
			EXPECT_DOUBLE_EQ( A1( i1, i2 ), double( A2( i1, i2 ) ) ); // Works because they are all integer values
		}
	}

	// No way to avoid dependency on value constructor
 	Array2D_double const C1( 2, 3, 3.1459 );
	Array2D_int const C2( C1 );
	EXPECT_EQ( C1.size(), C2.size() );
	EXPECT_EQ( C1.size1(), C2.size1() );
	EXPECT_EQ( C1.size2(), C2.size2() );
	EXPECT_EQ( C1.I1(), C2.I1() );
	EXPECT_EQ( C1.I2(), C2.I2() );
	EXPECT_EQ( C1.l1(), C2.l1() );
	EXPECT_EQ( C1.l2(), C2.l2() );
	EXPECT_EQ( C1.u1(), C2.u1() );
	EXPECT_EQ( C1.u2(), C2.u2() );
	EXPECT_TRUE( C1.initializer_active() );
	EXPECT_TRUE( C2.initializer_active() );
	EXPECT_TRUE( conformable( C1, C2 ) );
	EXPECT_TRUE( equal_dimensions( C1, C2 ) );
	for ( int i1 = C2.l1(); i1 <= C2.u1(); ++i1 )
		for ( int i2 = C2.l2(); i2 <= C2.u2(); ++i2 )
			EXPECT_DOUBLE_EQ( 3.0, double( C2( i1, i2 ) ) );
}

TEST( Array2Test, ConstructArgument )
{
	Array2D_int A1( 2, 3, 31459 );
	Array2A_int A2( A1 );
	Array2D_int A3( A2 );
 	EXPECT_EQ( A2.size(), A3.size() );
	EXPECT_EQ( A2.size1(), A3.size1() );
	EXPECT_EQ( A2.size2(), A3.size2() );
	EXPECT_EQ( A2.I1(), A3.I1() );
	EXPECT_EQ( A2.I2(), A3.I2() );
	EXPECT_EQ( A2.l1(), A3.l1() );
	EXPECT_EQ( A2.u1(), A3.u1() );
	EXPECT_EQ( A2.l2(), A3.l2() );
	EXPECT_EQ( A2.u2(), A3.u2() );
	EXPECT_EQ( A2.initializer_active(), A3.initializer_active() );
	EXPECT_TRUE( conformable( A1, A3 ) );
	EXPECT_TRUE( equal_dimensions( A1, A3 ) );
	EXPECT_TRUE( eq( A2, A3 ) );

 	Array2D_int const C1( 2, 3, 31459 );
	Array2A_int const C2( C1 );
	Array2D_int const C3( C2 );
	EXPECT_EQ( C2.size(), C3.size() );
	EXPECT_EQ( C2.size1(), C3.size1() );
	EXPECT_EQ( C2.size2(), C3.size2() );
	EXPECT_EQ( C2.l1(), C3.l1() );
	EXPECT_EQ( C2.l2(), C3.l2() );
	EXPECT_EQ( C2.u1(), C3.u1() );
	EXPECT_EQ( C2.u2(), C3.u2() );
	EXPECT_EQ( C2.initializer_active(), C3.initializer_active() );
	EXPECT_TRUE( conformable( C1, C3 ) );
	EXPECT_TRUE( equal_dimensions( C1, C3 ) );
	EXPECT_TRUE( eq( C2, C3 ) );

	Array2D_int E1( 2, 3, 31459 );
	Array2A_int E2( E1( 2, 2 ) );
	EXPECT_EQ( Array2A_int::npos, E2.size() );
	EXPECT_EQ( Array2A_int::npos, E2.size1() );
	EXPECT_EQ( 1u, E2.size2() );
	EXPECT_EQ( 1, E2.l1() );
	EXPECT_EQ( -1, E2.u1() );
	EXPECT_EQ( 1, E2.l2() );
	EXPECT_EQ( 1, E2.u2() );
	EXPECT_EQ( 31459, E2( 1, 1 ) );
	EXPECT_EQ( 31459, E2( 2, 1 ) );
	E2.dim( _, 1 );
	EXPECT_EQ( 1u, E2.size2() );
	EXPECT_EQ( 1, E2.l1() );
	EXPECT_EQ( -1, E2.u1() );
	EXPECT_EQ( 1, E2.l2() );
	EXPECT_EQ( 1, E2.u2() );
	EXPECT_EQ( 31459, E2( 1, 1 ) );
	EXPECT_EQ( 31459, E2( 2, 1 ) );
	E2.dim( 1, 2 );
	EXPECT_EQ( 2u, E2.size2() );
	EXPECT_EQ( 1, E2.l1() );
	EXPECT_EQ( 1, E2.u1() );
	EXPECT_EQ( 1, E2.l2() );
	EXPECT_EQ( 2, E2.u2() );
	EXPECT_EQ( 31459, E2( 1, 1 ) );
	EXPECT_EQ( 31459, E2( 1, 2 ) );
	EXPECT_DEBUG_DEATH( E2.dim( 1, _ ), ".*Assertion.*" );

	Array2D_int F1( 3, 3, 31459 );
	Array2A_int F2( F1( 2, 2 ), 2, 2 );
	EXPECT_EQ( 4u, F2.size() );
	EXPECT_EQ( 2u, F2.size1() );
	EXPECT_EQ( 2u, F2.size2() );
	EXPECT_EQ( 1, F2.l1() );
	EXPECT_EQ( 2, F2.u1() );
	EXPECT_EQ( 1, F2.l2() );
	EXPECT_EQ( 2, F2.u2() );
	EXPECT_TRUE( eq( F2, 31459 ) );
}

TEST( Array2Test, ConstructSticky )
{
	Array2D_int A1( Sticky_int( 31459 ) );
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 0u, A1.size1() );
	EXPECT_EQ( 0u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 0, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 0, A1.u2() );
	EXPECT_EQ( Array2D_int::IR(), A1.I1() );
	EXPECT_EQ( Array2D_int::IR(), A1.I2() );
	EXPECT_TRUE( A1.initializer_active() );
	A1.dimension( 2, 2 );
	EXPECT_EQ( 31459, A1( 1, 1 ) );
	EXPECT_EQ( 31459, A1( 1, 2 ) );
	EXPECT_EQ( 31459, A1( 2, 1 ) );
	EXPECT_EQ( 31459, A1( 2, 2 ) );

	Array2D_int const C1( Sticky_int( 31459 ) ); // Not a useful array: Can never hold anything
	EXPECT_EQ( 0u, C1.size() );
	EXPECT_EQ( 0u, C1.size1() );
	EXPECT_EQ( 0u, C1.size2() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 1, C1.l2() );
	EXPECT_EQ( 0, C1.u1() );
	EXPECT_EQ( 0, C1.u2() );
	EXPECT_EQ( Array2D_int::IR(), C1.I1() );
	EXPECT_EQ( Array2D_int::IR(), C1.I2() );
	EXPECT_TRUE( C1.initializer_active() );
}

TEST( Array2Test, ConstructIndexes )
{
	Array2D_int A1( 8, 10 );
	EXPECT_EQ( 80u, A1.size() );
	EXPECT_EQ( 8u, A1.size1() );
	EXPECT_EQ( 10u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 8, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 10, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 8 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 10 ), A1.I2() );
	EXPECT_FALSE( A1.initializer_active() );

	Array2D_int const C1( 8, 10 );
	EXPECT_EQ( 80u, C1.size() );
	EXPECT_EQ( 8u, C1.size1() );
	EXPECT_EQ( 10u, C1.size2() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 8, C1.u1() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 10, C1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 8 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 10 ), A1.I2() );
	EXPECT_FALSE( C1.initializer_active() );
}

TEST( Array2Test, ConstructIndexRange )
{
	// Explicit index range, positive bounds
	Array2D_int A11( IR( 2, 5 ), IR( 3, 7 ) );
	EXPECT_EQ( 20u, A11.size() );
	EXPECT_EQ( 4u, A11.size1() );
	EXPECT_EQ( 5u, A11.size2() );
	EXPECT_EQ( 2, A11.l1() );
	EXPECT_EQ( 5, A11.u1() );
	EXPECT_EQ( 3, A11.l2() );
	EXPECT_EQ( 7, A11.u2() );
	EXPECT_EQ( Array2D_int::IR( 2, 5 ), A11.I1() );
	EXPECT_EQ( Array2D_int::IR( 3, 7 ), A11.I2() );
	EXPECT_FALSE( A11.initializer_active() );

	// Explicit index range, negative bounds
 	Array2D_int A12( IR( -5, -2 ), IR( -7, -3 ) );
	EXPECT_EQ( 20u, A12.size() );
	EXPECT_EQ( 4u, A12.size1() );
	EXPECT_EQ( 5u, A12.size2() );
	EXPECT_EQ( -5, A12.l1() );
	EXPECT_EQ( -2, A12.u1() );
	EXPECT_EQ( -7, A12.l2() );
	EXPECT_EQ( -3, A12.u2() );
	EXPECT_EQ( Array2D_int::IR( -5, -2 ), A12.I1() );
	EXPECT_EQ( Array2D_int::IR( -7, -3 ), A12.I2() );
	EXPECT_FALSE( A12.initializer_active() );

	// Explicit index range, bounds that cross zero
	Array2D_int A13( IR( -3, 3 ), IR( -2, 2 ) );
	EXPECT_EQ( 35u, A13.size() );
	EXPECT_EQ( 7u, A13.size1() );
	EXPECT_EQ( 5u, A13.size2() );
	EXPECT_EQ( -3, A13.l1() );
	EXPECT_EQ( 3, A13.u1() );
	EXPECT_EQ( -2, A13.l2() );
	EXPECT_EQ( 2, A13.u2() );
	EXPECT_EQ( Array2D_int::IR( -3, 3 ), A13.I1() );
	EXPECT_EQ( Array2D_int::IR( -2, 2 ), A13.I2() );
	EXPECT_FALSE( A13.initializer_active() );

	// Index range initializer list, positive bounds
	Array2D_int A21( { 2, 5 }, { 3, 7 } );
	EXPECT_EQ( 20u, A21.size() );
	EXPECT_EQ( 4u, A21.size1() );
	EXPECT_EQ( 5u, A21.size2() );
	EXPECT_EQ( 2, A21.l1() );
	EXPECT_EQ( 5, A21.u1() );
	EXPECT_EQ( 3, A21.l2() );
	EXPECT_EQ( 7, A21.u2() );
	EXPECT_EQ( Array2D_int::IR( 2, 5 ), A21.I1() );
	EXPECT_EQ( Array2D_int::IR( 3, 7 ), A21.I2() );
	EXPECT_FALSE( A21.initializer_active() );

	// Index range initializer list, negative bounds
	Array2D_int A22( { -5, -2 }, { -7, -3 } );
	EXPECT_EQ( 20u, A22.size() );
	EXPECT_EQ( 4u, A22.size1() );
	EXPECT_EQ( 5u, A22.size2() );
	EXPECT_EQ( -5, A22.l1() );
	EXPECT_EQ( -2, A22.u1() );
	EXPECT_EQ( -7, A22.l2() );
	EXPECT_EQ( -3, A22.u2() );
	EXPECT_EQ( Array2D_int::IR( -5, -2 ), A22.I1() );
	EXPECT_EQ( Array2D_int::IR( -7, -3 ), A22.I2() );
	EXPECT_FALSE( A22.initializer_active() );

	// Index range initializer list, bounds that cross zero
	Array2D_int A23( { -3, 3 }, { -2, 2 } );
	EXPECT_EQ( 35u, A23.size() );
	EXPECT_EQ( 7u, A23.size1() );
	EXPECT_EQ( 5u, A23.size2() );
	EXPECT_EQ( -3, A23.l1() );
	EXPECT_EQ( 3, A23.u1() );
	EXPECT_EQ( -2, A23.l2() );
	EXPECT_EQ( 2, A23.u2() );
	EXPECT_EQ( Array2D_int::IR( -3, 3 ), A23.I1() );
	EXPECT_EQ( Array2D_int::IR( -2, 2 ), A23.I2() );
	EXPECT_FALSE( A23.initializer_active() );
}

TEST( Array2Test, ConstructIndexesInitializerValue )
{
	Array2D_int A1( 8, 10, 31459 );
	EXPECT_EQ( 80u, A1.size() );
	EXPECT_EQ( 8u, A1.size1() );
	EXPECT_EQ( 10u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 8, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 10, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 8 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 10 ), A1.I2() );
	EXPECT_TRUE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A1( i1, i2 ) );
		}
	}

	Array2D_int const C1( 8, 10, 31459 );
	EXPECT_EQ( 80u, C1.size() );
	EXPECT_EQ( 8u, C1.size1() );
	EXPECT_EQ( 10u, C1.size2() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 8, C1.u1() );
	EXPECT_EQ( 1, C1.l2() );
	EXPECT_EQ( 10, C1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 8 ), C1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 10 ), C1.I2() );
	EXPECT_TRUE( C1.initializer_active() );
	for ( int i1 = C1.l1(); i1 <= C1.u1(); ++i1 ) {
		for ( int i2 = C1.l2(); i2 <= C1.u2(); ++i2 ) {
			EXPECT_EQ( 31459, C1( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ConstructIndexRangeInitializerValue )
{
	// Explicit index range
	Array2D_int A11( IR( 2, 5 ), IR( 3, 7 ), 31459 );
	EXPECT_EQ( 20u, A11.size() );
	EXPECT_EQ( 4u, A11.size1() );
	EXPECT_EQ( 5u, A11.size2() );
	EXPECT_EQ( 2, A11.l1() );
	EXPECT_EQ( 5, A11.u1() );
	EXPECT_EQ( 3, A11.l2() );
	EXPECT_EQ( 7, A11.u2() );
	EXPECT_EQ( Array2D_int::IR( 2, 5 ), A11.I1() );
	EXPECT_EQ( Array2D_int::IR( 3, 7 ), A11.I2() );
	EXPECT_TRUE( A11.initializer_active() );
	for ( int i1 = A11.l1(); i1 <= A11.u1(); ++i1 ) {
		for ( int i2 = A11.l2(); i2 <= A11.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A11( i1, i2 ) );
		}
	}

	// Explicit index range, bounds that cross zero
	Array2D_int A12( IR( -3, 3 ), IR( -2, 2 ), -31459 );
	EXPECT_EQ( 35u, A12.size() );
	EXPECT_EQ( 7u, A12.size1() );
	EXPECT_EQ( 5u, A12.size2() );
	EXPECT_EQ( -3, A12.l1() );
	EXPECT_EQ( 3, A12.u1() );
	EXPECT_EQ( -2, A12.l2() );
	EXPECT_EQ( 2, A12.u2() );
	EXPECT_EQ( Array2D_int::IR( -3, 3 ), A12.I1() );
	EXPECT_EQ( Array2D_int::IR( -2, 2 ), A12.I2() );
	EXPECT_TRUE( A12.initializer_active() );
	for ( int i1 = A12.l1(); i1 <= A12.u1(); ++i1 ) {
		for ( int i2 = A12.l2(); i2 <= A12.u2(); ++i2 ) {
			EXPECT_EQ( -31459, A12( i1, i2 ) );
		}
	}

	// Index range initializer list
	Array2D_int A21( { 2, 5 }, { 3, 7 }, 2718 );
	EXPECT_EQ( 20u, A21.size() );
	EXPECT_EQ( 4u, A21.size1() );
	EXPECT_EQ( 5u, A21.size2() );
	EXPECT_EQ( 2, A21.l1() );
	EXPECT_EQ( 5, A21.u1() );
	EXPECT_EQ( 3, A21.l2() );
	EXPECT_EQ( 7, A21.u2() );
	EXPECT_EQ( Array2D_int::IR( 2, 5 ), A21.I1() );
	EXPECT_EQ( Array2D_int::IR( 3, 7 ), A21.I2() );
	EXPECT_TRUE( A21.initializer_active() );
	for ( int i1 = A21.l1(); i1 <= A21.u1(); ++i1 ) {
		for ( int i2 = A21.l2(); i2 <= A21.u2(); ++i2 ) {
			EXPECT_EQ( 2718, A21( i1, i2 ) );
		}
	}

	// Index range initializer list, bounds that cross zero
	Array2D_int A22( { -3, 3 }, { -2, 2 }, -2718 );
	EXPECT_EQ( 35u, A22.size() );
	EXPECT_EQ( 7u, A22.size1() );
	EXPECT_EQ( 5u, A22.size2() );
	EXPECT_EQ( -3, A22.l1() );
	EXPECT_EQ( 3, A22.u1() );
	EXPECT_EQ( -2, A22.l2() );
	EXPECT_EQ( 2, A22.u2() );
	EXPECT_EQ( Array2D_int::IR( -3, 3 ), A22.I1() );
	EXPECT_EQ( Array2D_int::IR( -2, 2 ), A22.I2() );
	EXPECT_TRUE( A22.initializer_active() );
	for ( int i1 = A22.l1(); i1 <= A22.u1(); ++i1 ) {
		for ( int i2 = A22.l2(); i2 <= A22.u2(); ++i2 ) {
			EXPECT_EQ( -2718, A22( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ConstructIndexesSticky )
{
	Array2D_int A1( 2, 3, Sticky_int( 31459 ), 2718 );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_TRUE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( 2718, A1( i1, i2 ) );
		}
	}
	A1.dimension( 2, 2 );
	EXPECT_EQ( 31459, A1( 1, 1 ) );
	EXPECT_EQ( 31459, A1( 1, 2 ) );
	EXPECT_EQ( 31459, A1( 2, 1 ) );
	EXPECT_EQ( 31459, A1( 2, 2 ) );

	Array2D_int const C1( 2, 3, Sticky_int( 31459 ), 2718 );
	EXPECT_EQ( 6u, C1.size() );
	EXPECT_EQ( 2u, C1.size1() );
	EXPECT_EQ( 3u, C1.size2() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 2, C1.u1() );
	EXPECT_EQ( 1, C1.l2() );
	EXPECT_EQ( 3, C1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), C1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), C1.I2() );
	EXPECT_TRUE( C1.initializer_active() );
	for ( int i1 = C1.l1(); i1 <= C1.u1(); ++i1 ) {
		for ( int i2 = C1.l2(); i2 <= C1.u2(); ++i2 ) {
			EXPECT_EQ( 2718, C1( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ConstructIndexRangeSticky )
{
	Array2D_int A1( { 1, 2 }, { 1, 3 }, Sticky_int( 31459 ) );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_TRUE( A1.initializer_active() );
	EXPECT_EQ( 31459, A1( 1, 1) );
	EXPECT_EQ( 31459, A1( 1, 2 ) );
	EXPECT_EQ( 31459, A1( 1, 3 ) );
	EXPECT_EQ( 31459, A1( 2, 1 ) );
	EXPECT_EQ( 31459, A1( 2, 2 ) );
	EXPECT_EQ( 31459, A1( 2, 3 ) );
	A1.dimension( 2, 2 );
	EXPECT_EQ( 31459, A1( 1, 1 ) );
	EXPECT_EQ( 31459, A1( 1, 2 ) );
	EXPECT_EQ( 31459, A1( 2, 1 ) );
	EXPECT_EQ( 31459, A1( 2, 2 ) );

	Array2D_int const C1( { 1, 2 }, { 1, 3 }, Sticky_int( 31459 ), 2718 );
	EXPECT_EQ( 6u, C1.size() );
	EXPECT_EQ( 2u, C1.size1() );
	EXPECT_EQ( 3u, C1.size2() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 2, C1.u1() );
	EXPECT_EQ( 1, C1.l2() );
	EXPECT_EQ( 3, C1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), C1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), C1.I2() );
	EXPECT_TRUE( C1.initializer_active() );
	EXPECT_EQ( 2718, C1( 1, 1) );
	EXPECT_EQ( 2718, C1( 1, 2 ) );
	EXPECT_EQ( 2718, C1( 1, 3 ) );
	EXPECT_EQ( 2718, C1( 2, 1 ) );
	EXPECT_EQ( 2718, C1( 2, 2 ) );
	EXPECT_EQ( 2718, C1( 2, 3 ) );
}

TEST( Array2Test, ConstructIndexesStickyInitializerValue )
{
	Array2D_int A1( 2, 3, Sticky_int( 31459 ), 2718 );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_TRUE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( 2718, A1( i1, i2 ) );
		}
	}

	Array2D_int const C1( 2, 3, Sticky_int( 31459 ), 2718 );
	EXPECT_EQ( 6u, C1.size() );
	EXPECT_EQ( 2u, C1.size1() );
	EXPECT_EQ( 3u, C1.size2() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 2, C1.u1() );
	EXPECT_EQ( 1, C1.l2() );
	EXPECT_EQ( 3, C1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), C1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), C1.I2() );
	EXPECT_TRUE( C1.initializer_active() );
	for ( int i1 = C1.l1(); i1 <= C1.u1(); ++i1 ) {
		for ( int i2 = C1.l2(); i2 <= C1.u2(); ++i2 ) {
			EXPECT_EQ( 2718, C1( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ConstructIndexRangeStickyInitializerValue )
{
	Array2D_int A1( { 1, 2 }, { 1, 3 }, Sticky_int( 31459 ), 2718 );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_TRUE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( 2718, A1( i1, i2 ) );
		}
	}

	Array2D_int const C1( { 1, 2 }, { 1, 3 }, Sticky_int( 31459 ), 2718 );
	EXPECT_EQ( 6u, C1.size() );
	EXPECT_EQ( 2u, C1.size1() );
	EXPECT_EQ( 3u, C1.size2() );
	EXPECT_EQ( 1, C1.l1() );
	EXPECT_EQ( 2, C1.u1() );
	EXPECT_EQ( 1, C1.l2() );
	EXPECT_EQ( 3, C1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), C1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), C1.I2() );
	EXPECT_TRUE( C1.initializer_active() );
	for ( int i1 = C1.l1(); i1 <= C1.u1(); ++i1 ) {
		for ( int i2 = C1.l2(); i2 <= C1.u2(); ++i2 ) {
			EXPECT_EQ( 2718, C1( i1, i2 ) );
		}
	}
}

static void initializer_function_int( Array2D_int & A )
{
	for ( int i1 = A.l1(); i1 <= A.u1(); ++i1 ) {
		for ( int i2 = A.l2(); i2 <= A.u2(); ++i2 ) {
			A( i1, i2 ) = i1 * 10 + i2;
		}
	}
}

static void initializer_function_double( Array2D_double & A )
{
	for ( int i1 = A.l1(); i1 <= A.u1(); ++i1 ) {
		for ( int i2 = A.l2(); i2 <= A.u2(); ++i2 ) {
			A( i1, i2 ) = i1 + i2 * 0.1;
		}
	}
}

static void initializer_function_string( Array2D_string & A )
{
	for ( int i1 = A.l1(); i1 <= A.u1(); ++i1 ) {
		for ( int i2 = A.l2(); i2 <= A.u2(); ++i2 ) {
			A( i1, i2 ) = string_of( i1 ) + "," + string_of( i2 );
		}
	}
}

TEST( Array2Test, ConstructIndexesInitializerFunction )
{
	Array2D_int A1( 2, 3, initializer_function_int );
	EXPECT_TRUE( eq( Array2D_int( 2, 3, { 11, 12, 13, 21, 22, 23 } ), A1 ) );
	Array2D_double A2( 2, 3, initializer_function_double );
	EXPECT_TRUE( eq( Array2D_double( 2, 3, { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 } ), A2 ) );
	Array2D_string A3( 2, 3, initializer_function_string );
	EXPECT_TRUE( eq( Array2D_string( 2, 3, { "1,1", "1,2", "1,3", "2,1", "2,2", "2,3" } ), A3 ) );

	Array2D_int const C1( 2, 3, initializer_function_int );
	EXPECT_TRUE( eq( Array2D_int( 2, 3, { 11, 12, 13, 21, 22, 23 } ), C1 ) );
	Array2D_double const C2( 2, 3, initializer_function_double );
	EXPECT_TRUE( eq( Array2D_double( 2, 3, { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 } ), C2 ) );
	Array2D_string const C3( 2, 3, initializer_function_string );
	EXPECT_TRUE( eq( Array2D_string( 2, 3, { "1,1", "1,2", "1,3", "2,1", "2,2", "2,3" } ), C3 ) );
}

TEST( Array2Test, ConstructIndexRangeInitializerFunction )
{
	Array2D_int A1( { 0, 1 }, { -1, 1 }, initializer_function_int );
	EXPECT_TRUE( eq( Array2D_int( { 0, 1 }, { -1, 1 }, { -1, 0, 1, 9, 10, 11 } ), A1 ) );
	Array2D_double A2( { 0, 1 }, { -1, 1 }, initializer_function_double );
	EXPECT_TRUE( eq( Array2D_double( { 0, 1 }, { -1, 1 }, { -0.1, 0.0, 0.1, 0.9, 1.0, 1.1 } ), A2 ) );
	Array2D_string A3( { 0, 1 }, { -1, 1 }, initializer_function_string );
	EXPECT_TRUE( eq( Array2D_string( { 0, 1 }, { -1, 1 }, { "0,-1", "0,0", "0,1", "1,-1", "1,0", "1,1" } ), A3 ) );

	Array2D_int const C1( { 0, 1 }, { -1, 1 }, initializer_function_int );
	EXPECT_TRUE( eq( Array2D_int( { 0, 1 }, { -1, 1 }, { -1, 0, 1, 9, 10, 11 } ), C1 ) );
	Array2D_double const C2( { 0, 1 }, { -1, 1 }, initializer_function_double );
	EXPECT_TRUE( eq( Array2D_double( { 0, 1 }, { -1, 1 }, { -0.1, 0.0, 0.1, 0.9, 1.0, 1.1 } ), C2 ) );
	Array2D_string const C3( { 0, 1 }, { -1, 1 }, initializer_function_string );
	EXPECT_TRUE( eq( Array2D_string( { 0, 1 }, { -1, 1 }, { "0,-1", "0,0", "0,1", "1,-1", "1,0", "1,1" } ), C3 ) );
}

TEST( Array2Test, ConstructIndexesInitializerList )
{
 	Array2D_int A1( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_FALSE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A1( i1, i2 ) );
		}
	}

	Array2D_uint A2( 2, 3, { 11u, 12u, 13u, 21u, 22u, 23u } );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 2, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 3, A2.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A2.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A2.I2() );
	EXPECT_FALSE( A2.initializer_active() );
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			EXPECT_EQ( unsigned( i1 * 10 + i2 ), A2( i1, i2 ) );
		}
	}

	Array2D_double A3( 2, 3, { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 } );
	EXPECT_EQ( 6u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 3u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 2, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 3, A3.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A3.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A3.I2() );
	EXPECT_FALSE( A3.initializer_active() );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_DOUBLE_EQ( i1 + i2 * 0.1, A3( i1, i2 ) );
		}
	}

	Array2D_string A4( 2, 3, { "1,1", "1,2", "1,3", "2,1", "2,2", "2,3" } );
	EXPECT_EQ( 6u, A4.size() );
	EXPECT_EQ( 2u, A4.size1() );
	EXPECT_EQ( 3u, A4.size2() );
	EXPECT_EQ( 1, A4.l1() );
	EXPECT_EQ( 2, A4.u1() );
	EXPECT_EQ( 1, A4.l2() );
	EXPECT_EQ( 3, A4.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A4.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A4.I2() );
	EXPECT_FALSE( A4.initializer_active() );
	char const * chars[] = { "", "1", "2", "3" };
	for ( int i1 = A4.l1(); i1 <= A4.u1(); ++i1 ) {
		for ( int i2 = A4.l2(); i2 <= A4.u2(); ++i2 ) {
			std::string c1( chars[ i1 ] ), c2( chars[ i2 ] );
			EXPECT_EQ( c1 + "," + c2, A4( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ConstructIndexRangeInitializerList )
{
	Array2D_int A1( { 0, 1 }, { -1, 1 }, { -1, 0, 1, 9, 10, 11 } );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 0, A1.l1() );
	EXPECT_EQ( 1, A1.u1() );
	EXPECT_EQ( -1, A1.l2() );
	EXPECT_EQ( 1, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 0, 1 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( -1, 1 ), A1.I2() );
	EXPECT_FALSE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A1( i1, i2 ) );
		}
	}

	Array2D_string A2( { 0, 1 }, { -1, 1 }, { "0,-1", "0,0", "0,1", "1,-1", "1,0", "1,1" } );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 0, A2.l1() );
	EXPECT_EQ( 1, A2.u1() );
	EXPECT_EQ( -1, A2.l2() );
	EXPECT_EQ( 1, A2.u2() );
	EXPECT_EQ( Array2D_int::IR( 0, 1 ), A2.I1() );
	EXPECT_EQ( Array2D_int::IR( -1, 1 ), A2.I2() );
	EXPECT_FALSE( A2.initializer_active() );
	char const * chars1[] = { "0", "1" };
	char const * chars2[] = { "-1", "0", "1" };
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			std::string c1( chars1[ i1 ] ), c2( chars2[ i2 + 1 ] );
			EXPECT_EQ( c1 + "," + c2, A2( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ConstructIndexesStickyInitializerList )
{
	Array2D_int A1( 2, 3, Sticky_int( 31459 ), { 11, 12, 13, 21, 22, 23 } );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_TRUE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A1( i1, i2 ) );
		}
	}
	A1.dimension( 2, 2 );
	EXPECT_EQ( 31459, A1( 1, 1 ) );
	EXPECT_EQ( 31459, A1( 1, 2 ) );
	EXPECT_EQ( 31459, A1( 2, 1 ) );
	EXPECT_EQ( 31459, A1( 2, 2 ) );

	Array2D_uint A2( 2, 3, Sticky_uint( 31459u ), { 11u, 12u, 13u, 21u, 22u, 23u } );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 2, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 3, A2.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A2.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A2.I2() );
	EXPECT_TRUE( A2.initializer_active() );
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			EXPECT_EQ( unsigned( i1 * 10 + i2 ), A2( i1, i2 ) );
		}
	}

	Array2D_double A3( 2, 3, Sticky_double( 3.1459 ), { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 } );
	EXPECT_EQ( 6u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 3u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 2, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 3, A3.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A3.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A3.I2() );
	EXPECT_TRUE( A3.initializer_active() );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_DOUBLE_EQ( i1 + i2 * 0.1, A3( i1, i2 ) );
		}
	}

	//Note The sticky argument must be at least as long as the longest argument in the initializer list, or those arguments end up truncated
	Array2D_string A4( 2, 3, Sticky_string( "X,X" ), { "1,1", "1,2", "1,3", "2,1", "2,2", "2,3" } );
	EXPECT_EQ( 6u, A4.size() );
	EXPECT_EQ( 2u, A4.size1() );
	EXPECT_EQ( 3u, A4.size2() );
	EXPECT_EQ( 1, A4.l1() );
	EXPECT_EQ( 2, A4.u1() );
	EXPECT_EQ( 1, A4.l2() );
	EXPECT_EQ( 3, A4.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A4.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A4.I2() );
	EXPECT_TRUE( A4.initializer_active() );
	char const * chars[] = { "", "1", "2", "3" };
	for ( int i1 = A4.l1(); i1 <= A4.u1(); ++i1 ) {
		for ( int i2 = A4.l2(); i2 <= A4.u2(); ++i2 ) {
			std::string c1( chars[ i1 ] ), c2( chars[ i2 ] );
			EXPECT_EQ( c1 + "," + c2, A4( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ConstructIndexRangeStickyInitializerList )
{
	Array2D_int A1( { 1, 2 }, { 1, 3 }, Sticky_int( 31459 ), { 11, 12, 13, 21, 22, 23 } );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_TRUE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A1( i1, i2 ) );
		}
	}
	A1.dimension( 2, 2 );
	EXPECT_EQ( 31459, A1( 1, 1 ) );
	EXPECT_EQ( 31459, A1( 1, 2 ) );
	EXPECT_EQ( 31459, A1( 2, 1 ) );
	EXPECT_EQ( 31459, A1( 2, 2 ) );

	Array2D_uint A2( { 1, 2 }, { 1, 3 }, Sticky_uint( 31459u ), { 11u, 12u, 13u, 21u, 22u, 23u } );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 2, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 3, A2.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A2.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A2.I2() );
	EXPECT_TRUE( A2.initializer_active() );
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			EXPECT_EQ( unsigned( i1 * 10 + i2 ), A2( i1, i2 ) );
		}
	}

	Array2D_double A3( { 1, 2 }, { 1, 3 }, Sticky_double( 3.1459 ), { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 } );
	EXPECT_EQ( 6u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 3u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 2, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 3, A3.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A3.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A3.I2() );
	EXPECT_TRUE( A3.initializer_active() );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_DOUBLE_EQ( i1 + i2 * 0.1, A3( i1, i2 ) );
		}
	}

	//Note The sticky argument must be at least as long as the longest argument in the initializer list, or those arguments end up truncated
	Array2D_string A4( { 1, 2 }, { 1, 3 }, Sticky_string( "X,X" ), { "1,1", "1,2", "1,3", "2,1", "2,2", "2,3" } );
	EXPECT_EQ( 6u, A4.size() );
	EXPECT_EQ( 2u, A4.size1() );
	EXPECT_EQ( 3u, A4.size2() );
	EXPECT_EQ( 1, A4.l1() );
	EXPECT_EQ( 2, A4.u1() );
	EXPECT_EQ( 1, A4.l2() );
	EXPECT_EQ( 3, A4.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A4.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A4.I2() );
	EXPECT_TRUE( A4.initializer_active() );
	char const * chars[] = { "", "1", "2", "3" };
	for ( int i1 = A4.l1(); i1 <= A4.u1(); ++i1 ) {
		for ( int i2 = A4.l2(); i2 <= A4.u2(); ++i2 ) {
			std::string c1( chars[ i1 ] ), c2( chars[ i2 ] );
			EXPECT_EQ( c1 + "," + c2, A4( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ConstructRange )
{
	Array2D_int A1( 2, 3 );

	Array2D_int A2( Array2D_int::range( A1 ) );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 2, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 3, A2.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A2.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A2.I2() );
	EXPECT_FALSE( A2.initializer_active() );
	// Values remain uninitialized

	Array2D_int A3( Array2D_int::range( A1, 31459 ) );
	EXPECT_EQ( 6u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 3u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 2, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 3, A3.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A3.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A3.I2() );
	EXPECT_TRUE( A3.initializer_active() );
	for ( int i1 = 1; i1 <= 2; ++i1 )
		for ( int i2 = 1; i2 <= 3; ++i2 )
			EXPECT_EQ( 31459, A3( i1, i2 ) );
}

TEST( Array2Test, ConstructShape )
{
	Array2D_int A1( 2, 3 );

	Array2D_int A2( Array2D_int::shape( A1 ) );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 2, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 3, A2.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A2.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A2.I2() );
	EXPECT_FALSE( A2.initializer_active() );
	// Values remain uninitialized

	Array2D_int A3( Array2D_int::shape( A1, 31459 ) );
	EXPECT_EQ( 6u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 3u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 2, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 3, A3.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A3.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A3.I2() );
	EXPECT_TRUE( A3.initializer_active() );
	for ( int i1 = 1; i1 <= 2; ++i1 )
		for ( int i2 = 1; i2 <= 3; ++i2 )
			EXPECT_EQ( 31459, A3( i1, i2 ) );
}

TEST( Array2Test, ConstructOneBased )
{
	Array2D_int A1( 2, 3 );
	Array2D_int A2( Array2D_int::one_based( A1 ) );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 2, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 3, A2.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 2 ), A2.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A2.I2() );
	EXPECT_FALSE( A2.initializer_active() );
	// Values remain uninitialized
}

TEST( Array2Test, ConstructDiag )
{
	Array2D_int A1( Array2D_int::diag( 3, 31459 ) );
	EXPECT_EQ( 9u, A1.size() );
	EXPECT_EQ( 3u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 3, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_FALSE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 )
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 )
			EXPECT_EQ( ( i1 == i2 ) ? 31459 : 0, A1( i1, i2 ) );
}

TEST( Array2Test, ConstructIdentity )
{
	Array2D_int A1( Array2D_int::identity( 3 ) );
	EXPECT_EQ( 9u, A1.size() );
	EXPECT_EQ( 3u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 3, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I1() );
	EXPECT_EQ( Array2D_int::IR( 1, 3 ), A1.I2() );
	EXPECT_FALSE( A1.initializer_active() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 )
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 )
			EXPECT_EQ( ( i1 == i2 ) ? 1 : 0, A1( i1, i2 ) );
}

TEST( Array2Test, AssignDefault )
{
	Array2D_double A1( 2, 3, 3.1459 );
	Array2D_double const A2( 2, 3, 2.718 );
	EXPECT_FALSE( eq( A1, A2 ) );

	A1 = A2;
	EXPECT_TRUE( eq( A1, A2 ) );

	A1 = 3.1459;
	for ( int i1 = 1; i1 <= 2; ++i1 ) {
		for ( int i2 = 1; i2 <= 3; ++i2 ) {
			EXPECT_EQ( 3.1459, A1( i1, i2 ) );
		}
	}

	A1 = { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 };
	for ( int i1 = 1; i1 <= 2; ++i1 ) {
		for ( int i2 = 1; i2 <= 3; ++i2 ) {
			EXPECT_EQ( i1 + i2 * 0.1, A1( i1, i2 ) );
		}
	}
}

TEST( Array2Test, AssignOtherData )
{
	Array2D_int A1( 2, 3, 31459 );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A1( i1, i2 ) );
		}
	}

	Array2D_double const A2( 2, 3, 3.1459 );
	A1 = A2;
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( 3, A1( i1, i2 ) );
		}
	}

// These unit tests can generate warnings for certain templated types, that's fine
#ifdef __llvm__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wliteral-conversion"
#endif

	A1 = 2.718; // May cause warnings about conversion
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( 2, A1( i1, i2 ) );
		}
	}

	A1 = { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 }; // May cause warnings about conversion
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1, A1( i1, i2 ) );
		}
	}

#ifdef __llvm__
#pragma clang diagnostic pop
#endif

}

TEST( Array2Test, AssignArgument )
{
	Array2D_int A1( 2, 3, 31459 );
	Array2A_int A2( A1 );
	Array2D_int A3( 2, 3, 2718 );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A1( i1, i2 ) );
		}
	}

	A3 = A2;
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A3( i1, i2 ) );
		}
	}
}

TEST( Array2Test, AssignArithmetic )
{
	Array2D_int A1( 2, 3, 11 );
	Array2D_int const A2( 2, 3, 10 );
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );

	A1 += A2;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 21 ), A1 ) );
	A1 -= A2;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );
	A1 += 33;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 44 ), A1 ) );
	A1 -= 33;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );
	A1 *= A2;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 110 ), A1 ) );
	A1 /= A2;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );
	A1 *= 33;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 363 ), A1 ) );
	A1 /= 33;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );
}

TEST( Array2Test, AssignArithmeticArgument )
{
	Array2D_int A1( 2, 3, 11 );
	Array2D_int const A2( 2, 3, 10 );
	Array2A_int A3( A2 );

	A1 += A3;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 21 ), A1 ) );
	A1 -= A3;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );
	A1 += 33;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 44 ), A1 ) );
	A1 -= 33;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );
	A1 *= A3;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 110 ), A1 ) );
	A1 /= A3;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );
	A1 *= 33;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 363 ), A1 ) );
	A1 /= 33;
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 11 ), A1 ) );
}

TEST( Array2Test, RangeBasedFor )
{
	Array2D_int A( 2, 3, { 1, 2, 3, 4, 5, 6 } );
	int v( 0 );
	for ( auto const e : A ) {
		EXPECT_EQ( ++v, e );
	}
}

TEST( Array2Test, SubscriptTail )
{
	Array2D_double A1( 2, 3, { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 } );
	ArrayTail_double A2( A1.a( 1, 3 ) ); // Tail of last 4 values
	EXPECT_EQ( 4u, A2.size() );
	Array2A_double A3( A2 );
	EXPECT_EQ( 4u, A3.size() );
	EXPECT_EQ( 4u, A3.size1() );
	EXPECT_EQ( 1u, A3.size2() );
	EXPECT_TRUE( eq( Array2D_double( 4, 1, { 1.3, 2.1, 2.2, 2.3 } ), A3 ) );

	Array2D_double const C1( 2, 3, { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 } );
	ArrayTail_double const C2( C1.a( 1, 3 ) ); // Tail of last 4 values
	EXPECT_EQ( 4u, C2.size() );
	Array2A_double const C3( C2 );
	EXPECT_EQ( 4u, C3.size() );
	EXPECT_EQ( 4u, C3.size1() );
	EXPECT_EQ( 1u, C3.size2() );
	EXPECT_TRUE( eq( Array2D_double( 4, 1, { 1.3, 2.1, 2.2, 2.3 } ), C3 ) );
}

TEST( Array2Test, SubscriptIndex )
{
	Array2D_int A1( 2, 3 );
	EXPECT_EQ( 0u, A1.index( 1, 1 ) );
	EXPECT_EQ( 1u, A1.index( 1, 2 ) );
	EXPECT_EQ( 2u, A1.index( 1, 3 ) );
	EXPECT_EQ( 3u, A1.index( 2, 1 ) );
	EXPECT_EQ( 4u, A1.index( 2, 2 ) );
	EXPECT_EQ( 5u, A1.index( 2, 3 ) );

	Array2D_int const C1( 2, 3 );
	EXPECT_EQ( 0u, C1.index( 1, 1 ) );
	EXPECT_EQ( 1u, C1.index( 1, 2 ) );
	EXPECT_EQ( 2u, C1.index( 1, 3 ) );
	EXPECT_EQ( 3u, C1.index( 2, 1 ) );
	EXPECT_EQ( 4u, C1.index( 2, 2 ) );
	EXPECT_EQ( 5u, C1.index( 2, 3 ) );
}

TEST( Array2Test, SubscriptOperator )
{
	Array2D_int A1( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 11, A1[ 0 ] );
	EXPECT_EQ( 12, A1[ 1 ] );
	EXPECT_EQ( 13, A1[ 2 ] );
	EXPECT_EQ( 21, A1[ 3 ] );
	EXPECT_EQ( 22, A1[ 4 ] );
	EXPECT_EQ( 23, A1[ 5 ] );

	for ( std::size_t i = 0; i < A1.size(); ++i ) A1[ i ] = static_cast< int >( i * 10 );
	EXPECT_EQ(  0, A1[ 0 ] );
	EXPECT_EQ( 10, A1[ 1 ] );
	EXPECT_EQ( 20, A1[ 2 ] );
	EXPECT_EQ( 30, A1[ 3 ] );
	EXPECT_EQ( 40, A1[ 4 ] );
	EXPECT_EQ( 50, A1[ 5 ] );

	Array2D_int const C1( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_EQ( 11, C1[ 0 ] );
	EXPECT_EQ( 12, C1[ 1 ] );
	EXPECT_EQ( 13, C1[ 2 ] );
	EXPECT_EQ( 21, C1[ 3 ] );
	EXPECT_EQ( 22, C1[ 4 ] );
	EXPECT_EQ( 23, C1[ 5 ] );
}

TEST( Array2Test, Predicates )
{
	Array2D_int A1;
	EXPECT_FALSE( A1.active() );
	EXPECT_FALSE( A1.allocated() );
	EXPECT_TRUE( A1.contiguous() );
	EXPECT_TRUE( A1.capacity_bounded() );
	EXPECT_FALSE( A1.capacity_unbounded() );
	EXPECT_TRUE( A1.empty() );
	EXPECT_TRUE( A1.size_bounded() );
	EXPECT_FALSE( A1.size_unbounded() );
	EXPECT_TRUE( A1.owner() );
	EXPECT_FALSE( A1.proxy() );
	EXPECT_TRUE( A1.is_default() );
	EXPECT_TRUE( A1.is_zero() );
	EXPECT_TRUE( A1.is_uniform() );
	EXPECT_TRUE( A1.is_uniform( 0 ) );

	Array2D_int A2( 2, 3 ); // Uninitialized
	EXPECT_TRUE( A2.active() );
	EXPECT_TRUE( A2.allocated() );
	EXPECT_TRUE( A2.contiguous() );
	EXPECT_TRUE( A2.capacity_bounded() );
	EXPECT_FALSE( A2.capacity_unbounded() );
	EXPECT_FALSE( A2.empty() );
	EXPECT_TRUE( A2.capacity_bounded() );
	EXPECT_FALSE( A2.capacity_unbounded() );
	EXPECT_TRUE( A2.owner() );
	EXPECT_FALSE( A2.proxy() );

	Array2D_int A3( 2, 3, 31459 );
	EXPECT_TRUE( A3.active() );
	EXPECT_TRUE( A3.allocated() );
	EXPECT_TRUE( A3.contiguous() );
	EXPECT_TRUE( A3.capacity_bounded() );
	EXPECT_FALSE( A3.capacity_unbounded() );
	EXPECT_FALSE( A3.empty() );
	EXPECT_TRUE( A3.capacity_bounded() );
	EXPECT_FALSE( A3.capacity_unbounded() );
	EXPECT_TRUE( A3.owner() );
	EXPECT_FALSE( A3.proxy() );
	EXPECT_FALSE( A3.is_default() );
	EXPECT_FALSE( A3.is_zero() );
	EXPECT_TRUE( A3.is_uniform() );
	EXPECT_TRUE( A3.is_uniform( 31459 ) );

	Array2D_int A4( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_TRUE( A4.active() );
	EXPECT_TRUE( A4.allocated() );
	EXPECT_TRUE( A4.contiguous() );
	EXPECT_TRUE( A4.capacity_bounded() );
	EXPECT_FALSE( A4.capacity_unbounded() );
	EXPECT_FALSE( A4.empty() );
	EXPECT_TRUE( A4.capacity_bounded() );
	EXPECT_FALSE( A4.capacity_unbounded() );
	EXPECT_TRUE( A4.owner() );
	EXPECT_FALSE( A4.proxy() );
	EXPECT_FALSE( A4.is_default() );
	EXPECT_FALSE( A4.is_zero() );
	EXPECT_FALSE( A4.is_uniform() );
	EXPECT_FALSE( A4.is_uniform( 0 ) );
	EXPECT_FALSE( A4.is_uniform( 11 ) );
}

TEST( Array2Test, PredicateComparisonsValues )
{
	Array2D_int A1;
	EXPECT_TRUE( eq( A1, 0 ) && eq( 0, A1 ) ); // Empty array is considered to equal any scalar (no values don't equal the scalar)
	EXPECT_FALSE( ne( A1, 0 ) || ne( 0, A1 ) );
	EXPECT_FALSE( lt( A1, 0 ) || lt( 0, A1 ) );
	EXPECT_TRUE( le( A1, 0 ) && le( 0, A1 ) );
	EXPECT_FALSE( gt( A1, 0 ) || gt( 0, A1 ) );
	EXPECT_TRUE( ge( A1, 0 ) && ge( 0, A1 ) );

	Array2D_int A2( 2, 3, 31459 );
	EXPECT_TRUE( eq( A2, 31459 ) && eq( 31459, A1 ) );
	EXPECT_FALSE( ne( A2, 31459 ) || ne( 31459, A2 ) );
	EXPECT_TRUE( lt( A2, 31460 ) && lt( 31458, A2 ) );
	EXPECT_TRUE( le( A2, 31459 ) && le( 31459, A2 ) );
	EXPECT_TRUE( le( A2, 31460 ) && le( 31458, A2 ) );
	EXPECT_TRUE( gt( A2, 31458 ) && gt( 31460, A2 ) );
	EXPECT_TRUE( ge( A2, 31459 ) && ge( 31459, A2 ) );
	EXPECT_TRUE( ge( A2, 31458 ) && ge( 31460, A2 ) );

	Array2D_int A3( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_FALSE( eq( A3, 11 ) || eq( 23, A3 ) );
	EXPECT_TRUE( ne( A3, 11 ) && ne( 23, A3 ) );
	EXPECT_TRUE( lt( A3, 24 ) && lt( 10, A3 ) );
	EXPECT_FALSE( lt( A3, 23 ) || lt( 11, A3 ) );
	EXPECT_TRUE( le( A3, 23 ) && le( 11, A3 ) );
	EXPECT_TRUE( gt( A3, 10 ) && gt( 24, A3 ) );
	EXPECT_FALSE( gt( A3, 11 ) || gt( 23, A3 ) );
	EXPECT_TRUE( ge( A3, 11 ) && ge( 23, A3 ) );
}

TEST( Array2Test, PredicateComparisonArrays )
{
	//Note Illegal to compare non-conformable arrays

	Array2D_int A1;
	EXPECT_TRUE( eq( A1, A1 ) );
	EXPECT_FALSE( ne( A1, A1 ) );
	EXPECT_FALSE( lt( A1, A1 ) );
	EXPECT_TRUE( le( A1, A1 ) );
	EXPECT_FALSE( gt( A1, A1 ) );
	EXPECT_TRUE( ge( A1, A1 ) );

	Array2D_int A2( 2, 3, 20 );
	EXPECT_TRUE( eq( A2, A2 ) );
	EXPECT_FALSE( ne( A2, A2 ) );
	EXPECT_FALSE( lt( A2, A2 ) );
	EXPECT_TRUE( le( A2, A2 ) );
	EXPECT_FALSE( gt( A2, A2 ) );
	EXPECT_TRUE( ge( A2, A2 ) );

	Array2D_int A3( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_TRUE( eq( A3, A3 ) );
	EXPECT_FALSE( ne( A3, A3 ) );
	EXPECT_FALSE( lt( A3, A3 ) );
	EXPECT_TRUE( le( A3, A3 ) );
	EXPECT_FALSE( gt( A3, A3 ) );
	EXPECT_TRUE( ge( A3, A3 ) );

	EXPECT_FALSE( eq( A2, A3 ) || eq( A3, A2 ) );
	EXPECT_TRUE( ne( A2, A3 ) && ne( A3, A2 ) );
	EXPECT_FALSE( lt( A2, A3 ) || lt( A3, A2 ) );
	EXPECT_FALSE( le( A2, A3 ) || le( A3, A2 ) );
	EXPECT_FALSE( gt( A2, A3 ) || gt( A3, A2 ) );
	EXPECT_FALSE( ge( A2, A3 ) || ge( A3, A2 ) );

	Array2D_int A4( 2, 3, { 11, 12, 12, 21, 21, 22 } );
	EXPECT_FALSE( eq( A3, A4 ) || eq( A4, A3 ) );
	EXPECT_TRUE( ne( A3, A4 ) && ne( A4, A3 ) );
	EXPECT_FALSE( lt( A3, A4 ) );
	EXPECT_FALSE( lt( A4, A3 ) );
	EXPECT_FALSE( le( A3, A4 ) );
	EXPECT_TRUE( le( A4, A3 ) );
	EXPECT_FALSE( gt( A3, A4 ) );
	EXPECT_FALSE( gt( A4, A3 ) );
	EXPECT_TRUE( ge( A3, A4 ) );
	EXPECT_FALSE( ge( A4, A3 ) );

	Array2D_int A5( 2, 3, { 11, 12, 14, 21, 23, 24 } );
	EXPECT_FALSE( eq( A3, A4 ) || eq( A4, A3 ) );
	EXPECT_TRUE( ne( A3, A4 ) && ne( A4, A3 ) );
}

TEST( Array2Test, PredicateContains )
{
	Array2D_int A1( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_TRUE( A1.contains( 1, 1 ) && A1.contains( 2, 3 ) );
	EXPECT_FALSE( A1.contains( 3, 3 ) && A1.contains( 2, 4 ) );
	EXPECT_FALSE( A1.contains( 0, 1 ) && A1.contains( 1, 0 ) );

	Array2D_int A2( { -3, -2 }, { -1, 1 }, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_TRUE( A2.contains( -3, -1 ) && A2.contains( -2, 1 ) );
	EXPECT_FALSE( A2.contains( 0, 1 ) && A2.contains( -2, 2 ) );
	EXPECT_FALSE( A2.contains( -4, -1 ) && A2.contains( -3, -2 ) );

	Array2D_int const C1( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_TRUE( C1.contains( 1, 1 ) && C1.contains( 2, 3 ) );
	EXPECT_FALSE( C1.contains( 3, 3 ) && C1.contains( 2, 4 ) );
	EXPECT_FALSE( C1.contains( 0, 1 ) && C1.contains( 1, 0 ) );

	Array2D_int const C2( { -3, -2 }, { -1, 1 }, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_TRUE( C2.contains( -3, -1 ) && C2.contains( -2, 1 ) );
	EXPECT_FALSE( C2.contains( 0, 1 ) && C2.contains( -2, 2 ) );
	EXPECT_FALSE( C2.contains( -4, -1 ) && C2.contains( -3, -2 ) );
}

TEST( Array2Test, PredicateConformable )
{
	Array2D_int A1;
	Array2D_int A2( 2, 3 );
	Array2D_int A3( 2, 4 );
	Array2D_int A4( { 2, 3 }, { 2, 4 } );

	EXPECT_FALSE( A1.conformable( A2 ) || A2.conformable( A1 ) );
	EXPECT_FALSE( A1.conformable( A3 ) || A3.conformable( A1 ) );
	EXPECT_FALSE( A1.conformable( A4 ) || A4.conformable( A1 ) );
	EXPECT_FALSE( A2.conformable( A3 ) || A3.conformable( A2 ) );
	EXPECT_TRUE( A2.conformable( A4 ) && A4.conformable( A2 ) );
	EXPECT_FALSE( A3.conformable( A4 ) || A4.conformable( A3 ) );

	Array2D_int const C1;
	Array2D_int const C2( 2, 3 );
	Array2D_int const C3( 2, 4 );
	Array2D_int const C4( { 2, 3 }, { 2, 4 } );

	EXPECT_FALSE( C1.conformable( C2 ) || C2.conformable( C1 ) );
	EXPECT_FALSE( C1.conformable( C3 ) || C3.conformable( C1 ) );
	EXPECT_FALSE( C1.conformable( C4 ) || C4.conformable( C1 ) );
	EXPECT_FALSE( C2.conformable( C3 ) || C3.conformable( C2 ) );
	EXPECT_TRUE( C2.conformable( C4 ) && C4.conformable( C2 ) );
	EXPECT_FALSE( C3.conformable( C4 ) || C4.conformable( C3 ) );
}

TEST( Array2Test, PredicateConformableOtherData )
{
	Array2D_int A1( 2, 3 );
	Array2D_double A2( 2, 3 );
	Array2D_string A3( 2, 3 );

	EXPECT_TRUE( A1.conformable( A2 ) && A2.conformable( A1 ) );
	EXPECT_TRUE( A1.conformable( A3 ) && A3.conformable( A1 ) );
	EXPECT_TRUE( A2.conformable( A3 ) && A3.conformable( A2 ) );

	Array2D_int const C1( 2, 3 );
	Array2D_double const C2( 2, 3 );
	Array2D_string const C3( 2, 3 );

	EXPECT_TRUE( C1.conformable( C2 ) && C2.conformable( C1 ) );
	EXPECT_TRUE( C1.conformable( C3 ) && C3.conformable( C1 ) );
	EXPECT_TRUE( C2.conformable( C3 ) && C3.conformable( C2 ) );
}

TEST( Array2Test, PredicateConformableOtherArray )
{
	Array2D_int A1( 2, 3 );
	Array2A_int A2( A1 );
	Array2D_int A3( 2, 3 );

	EXPECT_TRUE( A1.conformable( A2 ) && A2.conformable( A1 ) );
	EXPECT_TRUE( A2.conformable( A3 ) && A3.conformable( A2 ) );

	Array2D_int const C1( 2, 3 );
	Array2A_int const C2( C1 );
	Array2D_int const C3( 2, 3 );

	EXPECT_TRUE( C1.conformable( C2 ) && C2.conformable( C1 ) );
	EXPECT_TRUE( C2.conformable( C3 ) && C3.conformable( C2 ) );
}

TEST( Array2Test, PredicateEqualDimensions )
{
	Array2D_int A1;
	Array2D_int A2( 2, 3 );
	Array2D_int A3( 2, 4 );
	Array2D_int A4( { 2, 3 }, { 2, 4 } );

	EXPECT_FALSE( A1.equal_dimensions( A2 ) || A2.equal_dimensions( A1 ) );
	EXPECT_FALSE( A1.equal_dimensions( A3 ) || A3.equal_dimensions( A1 ) );
	EXPECT_FALSE( A1.equal_dimensions( A4 ) || A4.equal_dimensions( A1 ) );
	EXPECT_FALSE( A2.equal_dimensions( A3 ) || A3.equal_dimensions( A2 ) );
	EXPECT_FALSE( A2.equal_dimensions( A4 ) || A4.equal_dimensions( A2 ) );
	EXPECT_FALSE( A3.equal_dimensions( A4 ) || A4.equal_dimensions( A3 ) );

	Array2D_int A5( 2, 3, 31459 );
	EXPECT_TRUE( A2.equal_dimensions( A5 ) && A5.equal_dimensions( A2 ) );

	Array2D_int const C1;
	Array2D_int const C2( 2, 3 );
	Array2D_int const C3( 2, 4 );
	Array2D_int const C4( { 2, 3 }, { 2, 4 } );

	EXPECT_FALSE( C1.equal_dimensions( C2 ) || C2.equal_dimensions( C1 ) );
	EXPECT_FALSE( C1.equal_dimensions( C3 ) || C3.equal_dimensions( C1 ) );
	EXPECT_FALSE( C1.equal_dimensions( C4 ) || C4.equal_dimensions( C1 ) );
	EXPECT_FALSE( C2.equal_dimensions( C3 ) || C3.equal_dimensions( C2 ) );
	EXPECT_FALSE( C2.equal_dimensions( C4 ) || C4.equal_dimensions( C2 ) );
	EXPECT_FALSE( C3.equal_dimensions( C4 ) || C4.equal_dimensions( C3 ) );

	Array2D_int C5( 2, 3, 31459 );
	EXPECT_TRUE( C2.equal_dimensions( C5 ) && C5.equal_dimensions( C2 ) );
}

TEST( Array2Test, PredicateIdentity )
{
	Array2D_int A1;
	EXPECT_TRUE( A1.is_identity() );

	Array2D_int A2( 1, 1, 1 );
	EXPECT_TRUE( A2.is_identity() );

	Array2D_int A3( 1, 1, 2 );
	EXPECT_FALSE( A3.is_identity() );

	Array2D_int A4( 2, 2, 1 );
	EXPECT_FALSE( A4.is_identity() );

	Array2D_int A5( 2, 2, 2 );
	EXPECT_FALSE( A5.is_identity() );

	Array2D_int A6( 2, 2, { 1, 2, 2, 1 } );
	EXPECT_FALSE( A6.is_identity() );

	Array2D_int A7( 2, 2, { 1, 0, 0, 1 } );
	EXPECT_TRUE( A7.is_identity() );
}

TEST( Array2DTest, PredicateSymmetric )
{
	Array2D_int A1;
	EXPECT_TRUE( A1.symmetric() );

	Array2D_int A2( 1, 1, 1 );
	EXPECT_TRUE( A2.symmetric() );

	Array2D_int A3( 1, 1, 2 );
	EXPECT_TRUE( A3.symmetric() );

	Array2D_int A4( 2, 2, 1 );
	EXPECT_TRUE( A4.symmetric() );

	Array2D_int A5( 2, 2, 2 );
	EXPECT_TRUE( A5.symmetric() );

	Array2D_int A6( 2, 2, { 1, 2, 3, 1 } );
	EXPECT_FALSE( A6.symmetric() );

	Array2D_int A7( 2, 2, { 1, 2, 2, 1 } );
	EXPECT_TRUE( A7.symmetric() );
}

TEST( Array2Test, PredicateInitializerActive )
{
	Array2D_int A1;
	EXPECT_FALSE( A1.initializer_active() );

	Array2D_int A2( 2, 3 );
	EXPECT_FALSE( A2.initializer_active() );

	Array2D_int A3( 2, 3, 31459 );
	EXPECT_TRUE( A3.initializer_active() );

	Array2D_int A4( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_FALSE( A4.initializer_active() );

	Array2D_int A5( 2, 3, initializer_function_int );
	EXPECT_TRUE( A5.initializer_active() );
}

TEST( Array2Test, Inspectors )
{
	Array2D_int const C1;
	// Rank
	EXPECT_EQ( 2, C1.rank() );
	// Size
	EXPECT_EQ( 0u, C1.size() );
	EXPECT_EQ( 0u, C1.capacity() );
	EXPECT_EQ( 0u, C1.size( 1 ) );
	EXPECT_EQ( C1.size1(), C1.size( 1 ) );
	EXPECT_EQ( 0u, C1.size( 2 ) );
	EXPECT_EQ( C1.size2(), C1.size( 2 ) );
	// Indexes
	EXPECT_EQ( IR(), C1.I( 1 ) );
	EXPECT_EQ( C1.I1(), C1.I( 1 ) );
	EXPECT_EQ( IR(), C1.I( 2 ) );
	EXPECT_EQ( C1.I2(), C1.I( 2 ) );
	EXPECT_EQ( 1, C1.l( 1 ) );
	EXPECT_EQ( C1.l1(), C1.l( 1 ) );
	EXPECT_EQ( 1, C1.l( 2 ) );
	EXPECT_EQ( C1.l2(), C1.l( 2 ) );
 	EXPECT_EQ( 0, C1.u( 1 ) );
	EXPECT_EQ( C1.u1(), C1.u( 1 ) );
	EXPECT_EQ( 0, C1.u( 2 ) );
	EXPECT_EQ( C1.u2(), C1.u( 2 ) );
	// Data
	EXPECT_EQ( nullptr, C1.data() );
	EXPECT_EQ( nullptr, C1.data_beg() );
	EXPECT_EQ( nullptr, C1.data_end() );

	Array2D_int const C2( 2, 3 );
	// Rank
	EXPECT_EQ( 2, C2.rank() );
	// Size
	EXPECT_EQ( 6u, C2.size() );
	EXPECT_EQ( 6u, C2.capacity() );
	EXPECT_EQ( 2u, C2.size( 1 ) );
	EXPECT_EQ( C2.size1(), C2.size( 1 ) );
	EXPECT_EQ( 3u, C2.size( 2 ) );
	EXPECT_EQ( C2.size2(), C2.size( 2 ) );
	// Indexes
	EXPECT_EQ( IR( 1, 2 ), C2.I( 1 ) );
	EXPECT_EQ( C2.I1(), C2.I( 1 ) );
	EXPECT_EQ( IR( 1, 3 ), C2.I( 2 ) );
	EXPECT_EQ( C2.I2(), C2.I( 2 ) );
	EXPECT_EQ( 1, C2.l( 1 ) );
	EXPECT_EQ( C2.l1(), C2.l( 1 ) );
	EXPECT_EQ( 1, C2.l( 2 ) );
	EXPECT_EQ( C2.l2(), C2.l( 2 ) );
 	EXPECT_EQ( 2, C2.u( 1 ) );
	EXPECT_EQ( C2.u1(), C2.u( 1 ) );
	EXPECT_EQ( 3, C2.u( 2 ) );
	EXPECT_EQ( C2.u2(), C2.u( 2 ) );
	// Data
	EXPECT_NE( nullptr, C2.data() );
	EXPECT_NE( nullptr, C2.data_beg() );
	EXPECT_NE( nullptr, C2.data_end() );
}

TEST( Array2Test, ModifierClear )
{
	// Changes nothing about an empty array
	Array2D_int A1;
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 0u, A1.size1() );
	EXPECT_EQ( 0u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 0, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 0, A1.u2() );
	EXPECT_FALSE( A1.initializer_active() );
	A1.clear();
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 0u, A1.size1() );
	EXPECT_EQ( 0u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 0, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 0, A1.u2() );
	EXPECT_FALSE( A1.initializer_active() );

	// Resets the size, indexes and initializer of an uninitialized array
	Array2D_int A2( { 2, 3 }, { 2, 4 } );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 2, A2.l1() );
	EXPECT_EQ( 3, A2.u1() );
	EXPECT_EQ( 2, A2.l2() );
	EXPECT_EQ( 4, A2.u2() );
	EXPECT_FALSE( A2.initializer_active() );
	A2.clear();
	EXPECT_EQ( 0u, A2.size() );
	EXPECT_EQ( 0u, A2.size1() );
	EXPECT_EQ( 0u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 0, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 0, A2.u2() );
	EXPECT_FALSE( A2.initializer_active() );
	EXPECT_EQ( nullptr, A2.data() );
	EXPECT_EQ( nullptr, A2.data_beg() );
	EXPECT_EQ( nullptr, A2.data_end() );

	// Resets the size, indexes, initializer and contents  of an initialized array
	Array2D_int A3( 2, 3, 31459 );
	EXPECT_EQ( 6u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 3u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 2, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 3, A3.u2() );
	EXPECT_TRUE( A3.initializer_active() );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A3( i1, i2 ) );
		}
	}
	A3.clear();
	EXPECT_EQ( 0u, A3.size() );
	EXPECT_EQ( 0u, A3.size1() );
	EXPECT_EQ( 0u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 0, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 0, A3.u2() );
	EXPECT_FALSE( A3.initializer_active() );
}

TEST( Array2Test, ModifierToDefault )
{
	// Changes nothing about an empty array
	Array2D_int A1;
	A1.to_default();
	EXPECT_TRUE( eq( Array2D_int(), A1 ) );

	// Zeroes out an uninitialized array
	Array2D_int A2( 2, 3 );
	EXPECT_FALSE( A2.initializer_active() );
	A2.to_default(); // Default value assigned depends on macros
	EXPECT_FALSE( A2.initializer_active() );

	// Zeroes out (not initializes) an initialized array
	Array2D_int A3( 2, 3, 31459 );
	EXPECT_TRUE( A3.initializer_active() );
	A3.to_default(); // Default value assigned depends on macros
	EXPECT_TRUE( A3.initializer_active() );
}

TEST( Array2Test, ModifierZero )
{
	// Changes nothing about an empty array
	Array2D_int A1;
	A1.zero();
	EXPECT_TRUE( eq( Array2D_int(), A1 ) );

	// Initializes an uninitialized array with actual dimensions
	Array2D_int A2( 2, 3 );
	A2.zero();
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			EXPECT_EQ( 0, A2( i1, i2 ) );
		}
	}

	// Zeroes out an array with contents
	Array2D_int A3( 2, 3, 31459 );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A3( i1, i2 ) );
		}
	}
	A3.zero();
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_EQ( 0, A3( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ModifierToZero )
{
	// Changes nothing about an empty array
	Array2D_int A1;
	A1.to_zero();
	EXPECT_TRUE( eq( Array2D_int(), A1 ) );

	// Initializes an uninitialized array with actual dimensions
	Array2D_int A2( 2, 3 );
	A2.to_zero();
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			EXPECT_EQ( 0, A2( i1, i2 ) );
		}
	}

	// Zeroes out an array with contents
	Array2D_int A3( 2, 3, 31459 );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A3( i1, i2 ) );
		}
	}
	A3.to_zero();
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_EQ( 0, A3( i1, i2 ) );
		}
	}
}

TEST( Array2Test, ModifierInvert )
{
	// Changes nothing about an empty array
	Array2D_double A1;
	A1.invert();
	EXPECT_TRUE( eq( Array2D_double(), A1 ) );

	// Illegal to call on an uninitialized array

	// Inverts values of an initialized array
	Array2D_double A2( 2, 3, { 1.0, 10.0, 100.0, 0.1, 0.01, 0.001 } );
	A2.invert();
	EXPECT_TRUE( eq( Array2D_double( 2, 3, { 1.0, 0.1, 0.01, 10.0, 100.0, 1000.0 } ), A2 ) );

	// Inverts values of an initialized array
	Array2D_double A3( 2, 3, { -1.0, -10.0, -100.0, -0.1, -0.01, -0.001 } );
	A3.invert();
	EXPECT_TRUE( eq( Array2D_double( 2, 3, { -1.0, -0.1, -0.01, -10.0, -100.0, -1000.0 } ), A3 ) );
}

TEST( Array2Test, ModifierAllocateDeallocate )
{
	Array2D_int A1;
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 0u, A1.size1() );
	EXPECT_EQ( 0u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 0, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 0, A1.u2() );
	EXPECT_FALSE( A1.allocated() );

	A1.allocate( 2, 3 );
	EXPECT_EQ( 6u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 3u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 3, A1.u2() );
	EXPECT_TRUE( A1.allocated() );

	A1.deallocate();
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 0u, A1.size1() );
	EXPECT_EQ( 0u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 0, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 0, A1.u2() );
	EXPECT_FALSE( allocated( A1 ) );

	Array2D_int A2( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_EQ( 6u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 3u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 2, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 3, A2.u2() );
	EXPECT_TRUE( A2.allocated() );

	A2.deallocate();
	EXPECT_EQ( 0u, A2.size() );
	EXPECT_EQ( 0u, A2.size1() );
	EXPECT_EQ( 0u, A2.size2() );
	EXPECT_EQ( 1, A2.l1() );
	EXPECT_EQ( 0, A2.u1() );
	EXPECT_EQ( 1, A2.l2() );
	EXPECT_EQ( 0, A2.u2() );
	EXPECT_FALSE( allocated( A2 ) );

	Array2D_int A3;
	EXPECT_EQ( 0u, A3.size() );
	EXPECT_EQ( 0u, A3.size1() );
	EXPECT_EQ( 0u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 0, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 0, A3.u2() );
	EXPECT_FALSE( A3.allocated() );

	A3.allocate( Array2D_int( 2, 3 ) );
	EXPECT_EQ( 6u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 3u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 2, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 3, A3.u2() );
	EXPECT_TRUE( A3.allocated() );

	A3.deallocate();
	EXPECT_EQ( 0u, A3.size() );
	EXPECT_EQ( 0u, A3.size1() );
	EXPECT_EQ( 0u, A3.size2() );
	EXPECT_EQ( 1, A3.l1() );
	EXPECT_EQ( 0, A3.u1() );
	EXPECT_EQ( 1, A3.l2() );
	EXPECT_EQ( 0, A3.u2() );
	EXPECT_FALSE( allocated( A3 ) );
}

static void dimension_initializer_function( Array2D_int & A1 )
{
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			A1( i1, i2 ) = i1 * 10 + i2;
		}
	}
}

TEST( Array2Test, DimensionIndexRange )
{
	Array2D_int A1( 3, 4 );
	EXPECT_EQ( 12u, A1.size() );
	EXPECT_EQ( 3u, A1.size1() );
	EXPECT_EQ( 4u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 3, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 4, A1.u2() );
	// Values are uninitialized

	// 1:3, 1:4 -> 2:4, 2:5.
	A1.dimension( { 2, 4 }, { 2, 5 } );
	EXPECT_EQ( 12u, A1.size() );
	EXPECT_EQ( 3u, A1.size1() );
	EXPECT_EQ( 4u, A1.size2() );
	EXPECT_EQ( 2, A1.l1() );
	EXPECT_EQ( 4, A1.u1() );
	EXPECT_EQ( 2, A1.l2() );
	EXPECT_EQ( 5, A1.u2() );
	// Values are uninitialized

	// 1:3, 1:4 -> 2:4, 2:5 := 2:3, 2:4
	Array2D_int A2( 3, 4 );
	A2.dimension( { 2, 4 }, { 2, 5 }, 31459 ); // Without new initial value array is uninitialized (POD) or default contructed (UDT)
	EXPECT_EQ( 3u, A2.size1() );
	EXPECT_EQ( 4u, A2.size2() );
	EXPECT_EQ( 2, A2.l1() );
	EXPECT_EQ( 4, A2.u1() );
	EXPECT_EQ( 2, A2.l2() );
	EXPECT_EQ( 5, A2.u2() );
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A2( i1, i2 ) );
		}
	}

	// 1:3, 1:4 -> 2:4, 2:5 := 2:3, 2:4
	Array2D_int A3( 3, 4 );
	A3.dimension( { 2, 4 }, { 2, 5 }, dimension_initializer_function );
	EXPECT_EQ( 3u, A3.size1() );
	EXPECT_EQ( 4u, A3.size2() );
	EXPECT_EQ( 2, A3.l1() );
	EXPECT_EQ( 4, A3.u1() );
	EXPECT_EQ( 2, A3.l2() );
	EXPECT_EQ( 5, A3.u2() );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A3( i1, i2 ) );
		}
	}

	// 1:3, 1:4 -> 2:4, 2:5 := 2:3, 2:4
	Array2D_int A4( 3, 4, Sticky_int( 31459 ) ); // Sticky initializer is reapplied after dimension call
	A4.dimension( { 2, 4 }, { 2, 5 } );
	EXPECT_EQ( 3u, A4.size1() );
	EXPECT_EQ( 4u, A4.size2() );
	EXPECT_EQ( 2, A4.l1() );
	EXPECT_EQ( 4, A4.u1() );
	EXPECT_EQ( 2, A4.l2() );
	EXPECT_EQ( 5, A4.u2() );
	for ( int i1 = A4.l1(); i1 <= A4.u1(); ++i1 ) {
		for ( int i2 = A4.l2(); i2 <= A4.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A4( i1, i2 ) );
		}
	}
}

TEST( Array2Test, DimensionArrays )
{
	Array2D_int A1( 3, 4 );
	EXPECT_EQ( 12u, A1.size() );
	EXPECT_EQ( 3u, A1.size1() );
	EXPECT_EQ( 4u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 3, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 4, A1.u2() );
	// Values are uninitialized

	// 1:3, 1:4 -> 2:4, 2:5.
	A1.dimension( Array2D_int( { 2, 4 }, { 2, 5 } ) );
	EXPECT_EQ( 12u, A1.size() );
	EXPECT_EQ( 3u, A1.size1() );
	EXPECT_EQ( 4u, A1.size2() );
	EXPECT_EQ( 2, A1.l1() );
	EXPECT_EQ( 4, A1.u1() );
	EXPECT_EQ( 2, A1.l2() );
	EXPECT_EQ( 5, A1.u2() );
	// Values are uninitialized

	// 1:3, 1:4 -> 2:4, 2:5 := 2:3, 2:4
	Array2D_int A2( 3, 4 );
	A2.dimension( Array2D_int( { 2, 4 }, { 2, 5 } ), 31459 );
	EXPECT_EQ( 3u, A2.size1() );
	EXPECT_EQ( 4u, A2.size2() );
	EXPECT_EQ( 2, A2.l1() );
	EXPECT_EQ( 4, A2.u1() );
	EXPECT_EQ( 2, A2.l2() );
	EXPECT_EQ( 5, A2.u2() );
	for ( int i1 = A2.l1(); i1 <= A2.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A2.u2(); ++i2 ) {
			EXPECT_EQ( 31459, A2( i1, i2 ) );
		}
	}

	// 1:3, 1:4 -> 2:4, 2:5 := 2:3, 2:4
	Array2D_int A3( 3, 4 );
	A3.dimension( Array2D_int( { 2, 4 }, { 2, 5 } ), dimension_initializer_function );
	EXPECT_EQ( 3u, A3.size1() );
	EXPECT_EQ( 4u, A3.size2() );
	EXPECT_EQ( 2, A3.l1() );
	EXPECT_EQ( 4, A3.u1() );
	EXPECT_EQ( 2, A3.l2() );
	EXPECT_EQ( 5, A3.u2() );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A3( i1, i2 ) );
		}
	}
}

TEST( Array2Test, RedimensionIndexRange )
{
	Array2D_int A1( 2, 5, { 11, 12, 13, 14, 15, 21, 22, 23, 24, 25 } );
	Array2D_int A2( A1 );
	Array2D_int A3( A1 );

	EXPECT_EQ( 10u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 5u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 5, A1.u2() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A1( i1, i2 ) );
		}
	}

	// 1:2, 1:5 -> 2:3, 3:7 := 2:2, 3:5
	A2.redimension( { 2, 3 }, { 3, 7 } );
	EXPECT_EQ( 10u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 5u, A2.size2() );
	EXPECT_EQ( 2, A2.l1() );
	EXPECT_EQ( 3, A2.u1() );
	EXPECT_EQ( 3, A2.l2() );
	EXPECT_EQ( 7, A2.u2() );
	// Values for previous range are now uninitialized
	for ( int i1 = A2.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A2( i1, i2 ) );
		}
	}

	// 1:2, 1:5 -> 2:3, 3:7 := 2:2, 3:5
	A3.redimension( { 2, 3 }, { 3, 7 }, 31459 );
	EXPECT_EQ( 10u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 5u, A3.size2() );
	EXPECT_EQ( 2, A3.l1() );
	EXPECT_EQ( 3, A3.u1() );
	EXPECT_EQ( 3, A3.l2() );
	EXPECT_EQ( 7, A3.u2() );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			if ( ( i1 >= A3.l1() && i1 <= A1.u1() ) && ( i2 >= A3.l2() && i2 <= A1.u2() ) )
				EXPECT_EQ( i1 * 10 + i2, A3( i1, i2 ) );
			else
				EXPECT_EQ( 31459, A3( i1, i2 ) );
		}
	}
}

TEST( Array2Test, RedimensionArrays )
{
	Array2D_int A1( 2, 5, { 11, 12, 13, 14, 15, 21, 22, 23, 24, 25 } );
	Array2D_int A2( A1 );
	Array2D_int A3( A1 );
	Array2D_int A4( A1 );

	EXPECT_EQ( 10u, A1.size() );
	EXPECT_EQ( 2u, A1.size1() );
	EXPECT_EQ( 5u, A1.size2() );
	EXPECT_EQ( 1, A1.l1() );
	EXPECT_EQ( 2, A1.u1() );
	EXPECT_EQ( 1, A1.l2() );
	EXPECT_EQ( 5, A1.u2() );
	for ( int i1 = A1.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A1.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A1( i1, i2 ) );
		}
	}

	A2.redimension( Array2D_int( { 2, 3 }, { 3, 7 } ) );
	EXPECT_EQ( 10u, A2.size() );
	EXPECT_EQ( 2u, A2.size1() );
	EXPECT_EQ( 5u, A2.size2() );
	EXPECT_EQ( 2, A2.l1() );
	EXPECT_EQ( 3, A2.u1() );
	EXPECT_EQ( 3, A2.l2() );
	EXPECT_EQ( 7, A2.u2() );
	// Values for previous range are now uninitialized
	for ( int i1 = A2.l1(); i1 <= A1.u1(); ++i1 ) {
		for ( int i2 = A2.l2(); i2 <= A1.u2(); ++i2 ) {
			EXPECT_EQ( i1 * 10 + i2, A2( i1, i2 ) );
		}
	}

	A3.redimension( Array2D_int( { 2, 3 }, { 3, 7 } ), 31459 );
	EXPECT_EQ( 10u, A3.size() );
	EXPECT_EQ( 2u, A3.size1() );
	EXPECT_EQ( 5u, A3.size2() );
	EXPECT_EQ( 2, A3.l1() );
	EXPECT_EQ( 3, A3.u1() );
	EXPECT_EQ( 3, A3.l2() );
	EXPECT_EQ( 7, A3.u2() );
	for ( int i1 = A3.l1(); i1 <= A3.u1(); ++i1 ) {
		for ( int i2 = A3.l2(); i2 <= A3.u2(); ++i2 ) {
			if ( ( i1 >= A3.l1() && i1 <= A1.u1() ) && ( i2 >= A3.l2() && i2 <= A1.u2() ) )
				EXPECT_EQ( i1 * 10 + i2, A3( i1, i2 ) );
			else
				EXPECT_EQ( 31459, A3( i1, i2 ) );
		}
	}

	A4.redimension( Array2D_int( { 2, 3 }, { 3, 7 } ) ); // "New" elements are uninitialized
	EXPECT_EQ( 10u, A4.size() );
	EXPECT_EQ( 2u, A4.size1() );
	EXPECT_EQ( 5u, A4.size2() );
	EXPECT_EQ( 2, A4.l1() );
	EXPECT_EQ( 3, A4.u1() );
	EXPECT_EQ( 3, A4.l2() );
	EXPECT_EQ( 7, A4.u2() );
	for ( int i1 = A4.l1(); i1 <= A4.u1(); ++i1 ) {
		for ( int i2 = A4.l2(); i2 <= A4.u2(); ++i2 ) {
			if ( ( i1 >= A4.l1() && i1 <= A1.u1() ) && ( i2 >= A4.l2() && i2 <= A1.u2() ) )
				EXPECT_EQ( i1 * 10 + i2, A4( i1, i2 ) );
			else
				EXPECT_EQ( ( i1 - 1 ) * 10 + ( i2 - 2 ), A1( i1 - 1, i2 - 2 ) );
		}
	}
}

TEST( Array2Test, Initializer )
{
	Array2D_int A1( 2, 3 );
	EXPECT_FALSE( A1.initializer_active() );
	A1.initializer( 31459 );
	EXPECT_TRUE( A1.initializer_active() );

	Array2D_int A2( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_FALSE( A2.initializer_active() );
	A2.initializer( 31459 );
	EXPECT_TRUE( A2.initializer_active() );

	Array2D_int A3( 2, 3 );
	EXPECT_FALSE( A3.initializer_active() );
	A3.initializer( initializer_function_int );
	EXPECT_TRUE( A3.initializer_active() );

	Array2D_int A4( 2, 3, 31459 );
	EXPECT_TRUE( A4.initializer_active() );
	A4.initializer( initializer_function_int );
	EXPECT_TRUE( A4.initializer_active() );

	Array2D_int A5( 2, 3, initializer_function_int );
	EXPECT_TRUE( A5.initializer_active() );
	A5.initializer( 31459 );
	EXPECT_TRUE( A5.initializer_active() );
}

TEST( Array2Test, InitializerClear )
{
	Array2D_int A1( 2, 3 );
	EXPECT_FALSE( A1.initializer_active() );
	A1.initializer_clear();
	EXPECT_FALSE( A1.initializer_active() );

	Array2D_int A2( 2, 3, 31459 );
	EXPECT_TRUE( A2.initializer_active() );
	A2.initializer_clear();
	EXPECT_FALSE( A2.initializer_active() );

	Array2D_int A3( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_FALSE( A3.initializer_active() );
	A3.initializer_clear();
	EXPECT_FALSE( A3.initializer_active() );

	Array2D_int A4( 2, 3, initializer_function_int );
	EXPECT_TRUE( A4.initializer_active() );
	A4.initializer_clear();
	EXPECT_FALSE( A4.initializer_active() );
}

TEST( Array2Test, Initialize )
{
	Array2D_int A1( 2, 3 );
	EXPECT_FALSE( A1.initializer_active() );
	A1.initializer( 31459 );
	EXPECT_TRUE( A1.initializer_active() );
	A1.initialize();
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 31459 ), A1 ) );

	Array2D_int A2( 2, 3 );
	EXPECT_FALSE( A2.initializer_active() );
	A2.initializer( initializer_function_int );
	EXPECT_TRUE( A2.initializer_active() );
	A2.initialize();
	EXPECT_TRUE( eq( Array2D_int( 2, 3, { 11, 12, 13, 21, 22, 23 } ), A2 ) );

	Array2D_int A3( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	EXPECT_FALSE( A3.initializer_active() );
	EXPECT_TRUE( eq( Array2D_int( 2, 3, { 11, 12, 13, 21, 22, 23 } ), A3 ) );
	A3.initializer( 31459 );
	EXPECT_TRUE( A3.initializer_active() );
	A3.initialize();
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 31459 ), A3 ) );

	Array2D_int A4( 2, 3, 31459 );
	EXPECT_TRUE( A4.initializer_active() );
	EXPECT_TRUE( eq( Array2D_int( 2, 3, 31459 ), A4 ) );
	A4.initializer( initializer_function_int );
	EXPECT_TRUE( A4.initializer_active() );
	A4.initialize();
	EXPECT_TRUE( eq( Array2D_int( 2, 3, { 11, 12, 13, 21, 22, 23 } ), A4 ) );
}

TEST( Array2Test, Swap )
{
	Array2D_int A1( 2, 3, { 11, 12, 13, 21, 22, 23 } );
	Array2D_int A2;
	Array2D_int const A3( A1 );
	EXPECT_TRUE( eq( A1, A3 ) );
	EXPECT_TRUE( eq( Array2D_int(), A2 ) );
	A1.swap( A2 );
	EXPECT_TRUE( eq( A2, A3 ) );
	EXPECT_TRUE( eq( Array2D_int(), A1 ) );
}

TEST( Array2Test, Diagonals )
{
	{
		Array2D_int A( 3, 3, { 11, 12, 13, 21, 22, 23, 31, 32, 33 } );
		A.to_identity();
		EXPECT_EQ( 1, A( 1, 1 ) );
		EXPECT_EQ( 1, A( 2, 2 ) );
		EXPECT_EQ( 1, A( 3, 3 ) );
		EXPECT_EQ( 0, A( 1, 2 ) );
		EXPECT_EQ( 0, A( 1, 3 ) );
		EXPECT_EQ( 0, A( 2, 1 ) );
		EXPECT_EQ( 0, A( 2, 3 ) );
		EXPECT_EQ( 0, A( 3, 1 ) );
		EXPECT_EQ( 0, A( 3, 2 ) );
	}
	{
		Array2D_int A( {-1,1}, 3, { 11, 12, 13, 21, 22, 23, 31, 32, 33 } );
		A.to_diag( 9 );
		EXPECT_EQ( 9, A( -1, 1 ) );
		EXPECT_EQ( 9, A(  0, 2 ) );
		EXPECT_EQ( 9, A(  1, 3 ) );
		EXPECT_EQ( 0, A(  0, 1 ) );
		EXPECT_EQ( 0, A(  1, 1 ) );
		EXPECT_EQ( 0, A( -1, 2 ) );
		EXPECT_EQ( 0, A(  1, 2 ) );
		EXPECT_EQ( 0, A( -1, 3 ) );
		EXPECT_EQ( 0, A(  0, 3 ) );
	}
	{
		Array2D_int A( 3, 3, { 11, 12, 13, 21, 22, 23, 31, 32, 33 } );
		A.set_diagonal( 9 );
		EXPECT_EQ( 9, A( 1, 1 ) );
		EXPECT_EQ( 9, A( 2, 2 ) );
		EXPECT_EQ( 9, A( 3, 3 ) );
		EXPECT_EQ( 12, A( 1, 2 ) );
		EXPECT_EQ( 13, A( 1, 3 ) );
		EXPECT_EQ( 21, A( 2, 1 ) );
		EXPECT_EQ( 23, A( 2, 3 ) );
		EXPECT_EQ( 31, A( 3, 1 ) );
		EXPECT_EQ( 32, A( 3, 2 ) );
	}
}

TEST( Array2Test, Transpose )
{
	{
		Array2D_int A( 2, {-1,0}, { 11, 12, 21, 22 } ), C( A );
		A.transpose();
		EXPECT_EQ( C( 1, -1 ), A( 1, -1 ) );
		EXPECT_EQ( C( 1,  0 ), A( 2, -1 ) );
		EXPECT_EQ( C( 2, -1 ), A( 1,  0 ) );
		EXPECT_EQ( C( 2,  0 ), A( 2,  0 ) );
	}
	{
		Array2D_int A( 2, 3 );
		A( 1, 1 ) = 4;
		A( 1, 2 ) = 3;
		A( 1, 3 ) = 5;
		A( 2, 1 ) = 9;
		A( 2, 2 ) = 2;
		A( 2, 3 ) = 8;
		Array2D_int B( transpose( A ) );
		EXPECT_EQ( 1, B.l1() );
		EXPECT_EQ( 3, B.u1() );
		EXPECT_EQ( 1, B.l2() );
		EXPECT_EQ( 2, B.u2() );
		EXPECT_EQ( 3u, B.size1() );
		EXPECT_EQ( 2u, B.size2() );
		EXPECT_EQ( A( 1, 1 ), B( 1, 1 ) );
		EXPECT_EQ( A( 1, 2 ), B( 2, 1 ) );
		EXPECT_EQ( A( 1, 3 ), B( 3, 1 ) );
		EXPECT_EQ( A( 2, 1 ), B( 1, 2 ) );
		EXPECT_EQ( A( 2, 2 ), B( 2, 2 ) );
		EXPECT_EQ( A( 2, 3 ), B( 3, 2 ) );
	}
	{
		Array2D_int A( 2, {-1,1} );
		A( 1, -1 ) = 4;
		A( 1,  0 ) = 3;
		A( 1,  1 ) = 5;
		A( 2, -1 ) = 9;
		A( 2,  0 ) = 2;
		A( 2,  1 ) = 8;
		Array2D_int B( transpose( A ) );
		EXPECT_EQ( 1, B.l1() );
		EXPECT_EQ( 3, B.u1() );
		EXPECT_EQ( 1, B.l2() );
		EXPECT_EQ( 2, B.u2() );
		EXPECT_EQ( 3u, B.size1() );
		EXPECT_EQ( 2u, B.size2() );
		EXPECT_EQ( A( 1, -1 ), B( 1, 1 ) );
		EXPECT_EQ( A( 1,  0 ), B( 2, 1 ) );
		EXPECT_EQ( A( 1,  1 ), B( 3, 1 ) );
		EXPECT_EQ( A( 2, -1 ), B( 1, 2 ) );
		EXPECT_EQ( A( 2,  0 ), B( 2, 2 ) );
		EXPECT_EQ( A( 2,  1 ), B( 3, 2 ) );
	}
	{
		Array2D_int A( 2, {-1,1} );
		A( 1, -1 ) = 4;
		A( 1,  0 ) = 3;
		A( 1,  1 ) = 5;
		A( 2, -1 ) = 9;
		A( 2,  0 ) = 2;
		A( 2,  1 ) = 8;
		Array2D_int B( transposed( A ) );
		EXPECT_EQ( -1, B.l1() );
		EXPECT_EQ( 1, B.u1() );
		EXPECT_EQ( 1, B.l2() );
		EXPECT_EQ( 2, B.u2() );
		EXPECT_EQ( 3u, B.size1() );
		EXPECT_EQ( 2u, B.size2() );
		EXPECT_EQ( A( 1, -1 ), B( -1, 1 ) );
		EXPECT_EQ( A( 1,  0 ), B(  0, 1 ) );
		EXPECT_EQ( A( 1,  1 ), B(  1, 1 ) );
		EXPECT_EQ( A( 2, -1 ), B( -1, 2 ) );
		EXPECT_EQ( A( 2,  0 ), B(  0, 2 ) );
		EXPECT_EQ( A( 2,  1 ), B(  1, 2 ) );
	}
}

TEST( Array2Test, FunctionCount )
{
	Array2D_bool A( 2, 3, { true, false, false, false, true, true } );
	Array1D_size C1( 3, { 1, 1, 1 } );
	Array1D_size C2( 2, { 1, 2 } );
	EXPECT_EQ( 3u, count( A ) );
	EXPECT_TRUE( eq( C1, count( A, 1 ) ) );
	EXPECT_TRUE( eq( C2, count( A, 2 ) ) );
}

TEST( Array2Test, FunctionSum )
{
	Array2D_int A( 2, 2, { 11, 12, 21, 22 } );
	Array1D_int S1( 2, { 32, 34 } );
	Array1D_int S2( 2, { 23, 43 } );
	EXPECT_EQ( 66, sum( A ) );
	EXPECT_TRUE( eq( S1, sum( A, 1 ) ) );
	EXPECT_TRUE( eq( S2, sum( A, 2 ) ) );
}

TEST( Array2Test, FunctionProduct )
{
	Array2D_int A( 2, 2, { 11, 12, 21, 22 } );
	Array1D_int P1( 2, { 231, 264 } );
	Array1D_int P2( 2, { 132, 462 } );
	EXPECT_EQ( 60984, product( A ) );
	EXPECT_TRUE( eq( P1, product( A, 1 ) ) );
	EXPECT_TRUE( eq( P2, product( A, 2 ) ) );
}
