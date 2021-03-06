#ifndef ObjexxFCL_Array6S_hh_INCLUDED
#define ObjexxFCL_Array6S_hh_INCLUDED

// Array6S: 6D Slice Array Proxy
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

// ObjexxFCL Headers
#include <ObjexxFCL/Array6S.fwd.hh>
#include <ObjexxFCL/ArrayRS.hh>
#include <ObjexxFCL/Array5S.hh>
#include <ObjexxFCL/MArray6.hh>

namespace ObjexxFCL {

// Array6S: 6D Slice Array Proxy
template< typename T >
class Array6S : public ArrayRS< T, 6 >
{

private: // Types

	typedef  ArrayRS< T, 6 >  Super;

private: // Friend

	template< typename > friend class Array6S;

public: // Types

	typedef  typename Super::Base  Base;
	typedef  typename Super::Traits  Traits;
	typedef  typename Super::IR  IR;
	typedef  typename Super::IS  IS;
	typedef  typename Super::DS  DS;

	// STL Style
	typedef  typename Super::value_type  value_type;
	typedef  typename Super::reference  reference;
	typedef  typename Super::const_reference  const_reference;
	typedef  typename Super::pointer  pointer;
	typedef  typename Super::const_pointer  const_pointer;
	typedef  typename Super::size_type  size_type;
	typedef  typename Super::difference_type  difference_type;

	// C++ Style
	typedef  typename Super::Value  Value;
	typedef  typename Super::Reference  Reference;
	typedef  typename Super::ConstReference  ConstReference;
	typedef  typename Super::Pointer  Pointer;
	typedef  typename Super::ConstPointer  ConstPointer;
	typedef  typename Super::Size  Size;
	typedef  typename Super::Difference  Difference;

	// Using
	using Super::in_range;
	using Super::isize;
	using Super::overlap;
	using Super::size;
	using Super::slice_k;
	using Super::contiguous_;
	using Super::data_;
	using Super::data_beg_;
	using Super::data_end_;
	using Super::size_;

public: // Creation

	// Default Constructor
	inline
	Array6S() :
	 m6_( 1 ),
	 m5_( 1 ),
	 m4_( 1 ),
	 m3_( 1 ),
	 m2_( 1 ),
	 m1_( 1 ),
	 k_( 0 ),
	 u1_( 0 ),
	 u2_( 0 ),
	 u3_( 0 ),
	 u4_( 0 ),
	 u5_( 0 ),
	 u6_( 0 )
	{}

	// Copy Constructor
	inline
	Array6S( Array6S const & a ) :
	 Super( a ),
	 m6_( a.m6_ ),
	 m5_( a.m5_ ),
	 m4_( a.m4_ ),
	 m3_( a.m3_ ),
	 m2_( a.m2_ ),
	 m1_( a.m1_ ),
	 k_( a.k_ ),
	 u1_( a.u1_ ),
	 u2_( a.u2_ ),
	 u3_( a.u3_ ),
	 u4_( a.u4_ ),
	 u5_( a.u5_ ),
	 u6_( a.u6_ )
	{
		data_set();
	}

	// Data Constructor
	inline
	Array6S( T const * data, std::int64_t const k, DS const & d1, DS const & d2, DS const & d3, DS const & d4, DS const & d5, DS const & d6 ) :
	 Super( data, d1.z() * d2.z() * d3.z() * d4.z() * d5.z() * d6.z() ),
	 m6_( d6.m() ),
	 m5_( d5.m() ),
	 m4_( d4.m() ),
	 m3_( d3.m() ),
	 m2_( d2.m() ),
	 m1_( d1.m() ),
	 k_( k + d1.k() + d2.k() + d3.k() + d4.k() + d5.k() + d6.k() ),
	 u1_( d1.u() ),
	 u2_( d2.u() ),
	 u3_( d3.u() ),
	 u4_( d4.u() ),
	 u5_( d5.u() ),
	 u6_( d6.u() )
	{
		contiguous_ = computed_contiguous();
		data_set();
	}

	// Non-Const Data Constructor
	inline
	Array6S( T * data, std::int64_t const k, DS const & d1, DS const & d2, DS const & d3, DS const & d4, DS const & d5, DS const & d6 ) :
	 Super( data, d1.z() * d2.z() * d3.z() * d4.z() * d5.z() * d6.z() ),
	 m6_( d6.m() ),
	 m5_( d5.m() ),
	 m4_( d4.m() ),
	 m3_( d3.m() ),
	 m2_( d2.m() ),
	 m1_( d1.m() ),
	 k_( k + d1.k() + d2.k() + d3.k() + d4.k() + d5.k() + d6.k() ),
	 u1_( d1.u() ),
	 u2_( d2.u() ),
	 u3_( d3.u() ),
	 u4_( d4.u() ),
	 u5_( d5.u() ),
	 u6_( d6.u() )
	{
		contiguous_ = computed_contiguous();
		data_set();
	}

	// Array Constructor
	template< template< typename > class A >
	inline
	Array6S( A< T > const & a ) :
	 Super( a.data(), a.size() ),
	 m6_( 1 ),
	 m5_( a.size6() ),
	 m4_( a.size5() * m5_ ),
	 m3_( a.size4() * m4_ ),
	 m2_( a.size3() * m3_ ),
	 m1_( a.size2() * m2_ ),
	 k_( -( m1_ + m2_ + m3_ + m4_ + m5_ + m6_ ) ),
	 u1_( a.isize1() ),
	 u2_( a.isize2() ),
	 u3_( a.isize3() ),
	 u4_( a.isize4() ),
	 u5_( a.isize5() ),
	 u6_( a.isize6() )
	{
		contiguous_ = true;
		data_set();
	}

	// Destructor
	inline
	virtual
	~Array6S()
	{}

public: // Assignment: Array

	// Copy Assignment
	inline
	Array6S &
	operator =( Array6S const & a )
	{
		if ( this != &a ) {
			assert( conformable( a ) );
			if ( overlap( a ) ) { // Overlap-safe
				CArray< T > c( size_ );
				size_type l( 0 );
				for ( int i1 = 1; i1 <= u1_; ++i1 ) {
					for ( int i2 = 1; i2 <= u2_; ++i2 ) {
						for ( int i3 = 1; i3 <= u3_; ++i3 ) {
							for ( int i4 = 1; i4 <= u4_; ++i4 ) {
								for ( int i5 = 1; i5 <= u5_; ++i5 ) {
									for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
										c[ l ] = a( i1, i2, i3, i4, i5, i6 );
									}
								}
							}
						}
					}
				}
				l = 0;
				for ( int i1 = 1; i1 <= u1_; ++i1 ) {
					for ( int i2 = 1; i2 <= u2_; ++i2 ) {
						for ( int i3 = 1; i3 <= u3_; ++i3 ) {
							for ( int i4 = 1; i4 <= u4_; ++i4 ) {
								for ( int i5 = 1; i5 <= u5_; ++i5 ) {
									for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
										operator ()( i1, i2, i3, i4, i5, i6 ) = c[ l ];
									}
								}
							}
						}
					}
				}
			} else { // Not overlap-safe
				for ( int i1 = 1; i1 <= u1_; ++i1 ) {
					for ( int i2 = 1; i2 <= u2_; ++i2 ) {
						for ( int i3 = 1; i3 <= u3_; ++i3 ) {
							for ( int i4 = 1; i4 <= u4_; ++i4 ) {
								for ( int i5 = 1; i5 <= u5_; ++i5 ) {
									for ( int i6 = 1; i6 <= u6_; ++i6 ) {
										operator ()( i1, i2, i3, i4, i5, i6 ) = a( i1, i2, i3, i4, i5, i6 );
									}
								}
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// Copy Assignment Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	operator =( Array6S< U > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) = a( i1, i2, i3, i4, i5, i6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// MArray Assignment Template
	template< class A, typename M >
	inline
	Array6S &
	operator =( MArray6< A, M > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) = a( i1, i2, i3, i4, i5, i6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// Array Assignment Template
	template< template< typename > class A >
	inline
	Array6S &
	operator =( A< T > const & a )
	{
		assert( conformable( a ) );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( size_ );
			size_type l( 0 );
			for ( int j1 = a.l1(), e1 = a.u1(); j1 <= e1; ++j1 ) {
				for ( int j2 = a.l2(), e2 = a.u2(); j2 <= e2; ++j2 ) {
					for ( int j3 = a.l3(), e3 = a.u3(); j3 <= e3; ++j3 ) {
						for ( int j4 = a.l4(), e4 = a.u4(); j4 <= e4; ++j4 ) {
							for ( int j5 = a.l5(), e5 = a.u5(); j5 <= e5; ++j5 ) {
								for ( int j6 = a.l6(), e6 = a.u6(); j6 <= e6; ++j6, ++l ) {
									c[ l ] = a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
			l = 0;
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) = c[ l ];
								}
							}
						}
					}
				}
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
				for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
					for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
						for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
							for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
								for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) = a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// Array Assignment Template
	template< template< typename > class A, typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	operator =( A< U > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
			for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
				for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
					for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
						for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
							for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) = a( j1, j2, j3, j4, j5, j6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// Initializer List Assignment Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	operator =( std::initializer_list< U > const l )
	{
		assert( size_ == l.size() );
		auto r( l.begin() );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6, ++r ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) = *r;
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// += MArray Template
	template< class A, typename M >
	inline
	Array6S &
	operator +=( MArray6< A, M > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) += a( i1, i2, i3, i4, i5, i6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// -= MArray Template
	template< class A, typename M >
	inline
	Array6S &
	operator -=( MArray6< A, M > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) -= a( i1, i2, i3, i4, i5, i6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// *= MArray Template
	template< class A, typename M >
	inline
	Array6S &
	operator *=( MArray6< A, M > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) *= a( i1, i2, i3, i4, i5, i6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// /= MArray Template
	template< class A, typename M >
	inline
	Array6S &
	operator /=( MArray6< A, M > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								assert( a( i1, i2, i3, i4, i5, i6 ) != T( 0 ) );
								operator ()( i1, i2, i3, i4, i5, i6 ) /= a( i1, i2, i3, i4, i5, i6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// += Array Template
	template< template< typename > class A >
	inline
	Array6S &
	operator +=( A< T > const & a )
	{
		assert( conformable( a ) );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( size_ );
			size_type l( 0 );
			for ( int j1 = a.l1(), e1 = a.u1(); j1 <= e1; ++j1 ) {
				for ( int j2 = a.l2(), e2 = a.u2(); j2 <= e2; ++j2 ) {
					for ( int j3 = a.l3(), e3 = a.u3(); j3 <= e3; ++j3 ) {
						for ( int j4 = a.l4(), e4 = a.u4(); j4 <= e4; ++j4 ) {
							for ( int j5 = a.l5(), e5 = a.u5(); j5 <= e5; ++j5 ) {
								for ( int j6 = a.l6(), e6 = a.u6(); j6 <= e6; ++j6, ++l ) {
									c[ l ] = a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
			l = 0;
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) += c[ l ];
								}
							}
						}
					}
				}
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
				for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
					for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
						for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
							for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
								for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) += a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// -= Array Template
	template< template< typename > class A >
	inline
	Array6S &
	operator -=( A< T > const & a )
	{
		assert( conformable( a ) );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( size_ );
			size_type l( 0 );
			for ( int j1 = a.l1(), e1 = a.u1(); j1 <= e1; ++j1 ) {
				for ( int j2 = a.l2(), e2 = a.u2(); j2 <= e2; ++j2 ) {
					for ( int j3 = a.l3(), e3 = a.u3(); j3 <= e3; ++j3 ) {
						for ( int j4 = a.l4(), e4 = a.u4(); j4 <= e4; ++j4 ) {
							for ( int j5 = a.l5(), e5 = a.u5(); j5 <= e5; ++j5 ) {
								for ( int j6 = a.l6(), e6 = a.u6(); j6 <= e6; ++j6, ++l ) {
									c[ l ] = a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
			l = 0;
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) -= c[ l ];
								}
							}
						}
					}
				}
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
				for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
					for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
						for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
							for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
								for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) -= a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// *= Array Template
	template< template< typename > class A >
	inline
	Array6S &
	operator *=( A< T > const & a )
	{
		assert( conformable( a ) );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( size_ );
			size_type l( 0 );
			for ( int j1 = a.l1(), e1 = a.u1(); j1 <= e1; ++j1 ) {
				for ( int j2 = a.l2(), e2 = a.u2(); j2 <= e2; ++j2 ) {
					for ( int j3 = a.l3(), e3 = a.u3(); j3 <= e3; ++j3 ) {
						for ( int j4 = a.l4(), e4 = a.u4(); j4 <= e4; ++j4 ) {
							for ( int j5 = a.l5(), e5 = a.u5(); j5 <= e5; ++j5 ) {
								for ( int j6 = a.l6(), e6 = a.u6(); j6 <= e6; ++j6, ++l ) {
									c[ l ] = a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
			l = 0;
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) *= c[ l ];
								}
							}
						}
					}
				}
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
				for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
					for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
						for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
							for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
								for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) *= a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// /= Array Template
	template< template< typename > class A >
	inline
	Array6S &
	operator /=( A< T > const & a )
	{
		assert( conformable( a ) );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( size_ );
			size_type l( 0 );
			for ( int j1 = a.l1(), e1 = a.u1(); j1 <= e1; ++j1 ) {
				for ( int j2 = a.l2(), e2 = a.u2(); j2 <= e2; ++j2 ) {
					for ( int j3 = a.l3(), e3 = a.u3(); j3 <= e3; ++j3 ) {
						for ( int j4 = a.l4(), e4 = a.u4(); j4 <= e4; ++j4 ) {
							for ( int j5 = a.l5(), e5 = a.u5(); j5 <= e5; ++j5 ) {
								for ( int j6 = a.l6(), e6 = a.u6(); j6 <= e6; ++j6, ++l ) {
									assert( a( j1, j2, j3, j4, j5, j6 ) != T( 0 ) );
									c[ l ] = a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
			l = 0;
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									operator ()( i1, i2, i3, i4, i5, i6 ) /= c[ l ];
								}
							}
						}
					}
				}
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
				for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
					for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
						for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
							for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
								for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
									assert( a( j1, j2, j3, j4, j5, j6 ) != T( 0 ) );
									operator ()( i1, i2, i3, i4, i5, i6 ) /= a( j1, j2, j3, j4, j5, j6 );
								}
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// += Array Template
	template< template< typename > class A, typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	operator +=( A< U > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
			for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
				for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
					for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
						for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
							for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) += a( j1, j2, j3, j4, j5, j6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// -= Array Template
	template< template< typename > class A, typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	operator -=( A< U > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
			for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
				for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
					for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
						for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
							for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) -= a( j1, j2, j3, j4, j5, j6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// *= Array Template
	template< template< typename > class A, typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	operator *=( A< U > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
			for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
				for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
					for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
						for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
							for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) *= a( j1, j2, j3, j4, j5, j6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// /= Array Template
	template< template< typename > class A, typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	operator /=( A< U > const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1, j1 = a.l1(); i1 <= u1_; ++i1, ++j1 ) {
			for ( int i2 = 1, j2 = a.l2(); i2 <= u2_; ++i2, ++j2 ) {
				for ( int i3 = 1, j3 = a.l3(); i3 <= u3_; ++i3, ++j3 ) {
					for ( int i4 = 1, j4 = a.l4(); i4 <= u4_; ++i4, ++j4 ) {
						for ( int i5 = 1, j5 = a.l5(); i5 <= u5_; ++i5, ++j5 ) {
							for ( int i6 = 1, j6 = a.l6(); i6 <= u6_; ++i6, ++j6 ) {
								assert( a( j1, j2, j3, j4, j5 ) != T( 0 ) );
								operator ()( i1, i2, i3, i4, i5, i6 ) /= a( j1, j2, j3, j4, j5, j6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

public: // Assignment: Logical

	// &&= Array
	inline
	Array6S &
	and_equals( Array6S const & a )
	{
		assert( conformable( a ) );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( size_ );
			size_type l( 0 );
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									c[ l ] = a( i1, i2, i3, i4, i5, i6 );
								}
							}
						}
					}
				}
			}
			l = 0;
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									auto & v( operator ()( i1, i2, i3, i4, i5, i6 ) );
									v = v && c[ l ];
								}
							}
						}
					}
				}
			}
		} else { // Not overlap-safe
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6 ) {
									auto & v( operator ()( i1, i2, i3, i4, i5, i6 ) );
									v = v && a( i1, i2, i3, i4, i5, i6 );
								}
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// ||= Array
	inline
	Array6S &
	or_equals( Array6S const & a )
	{
		assert( conformable( a ) );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( size_ );
			size_type l( 0 );
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									c[ l ] = a( i1, i2, i3, i4, i5, i6 );
								}
							}
						}
					}
				}
			}
			l = 0;
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6, ++l ) {
									auto & v( operator ()( i1, i2, i3, i4, i5, i6 ) );
									v = v || c[ l ];
								}
							}
						}
					}
				}
			}
		} else { // Not overlap-safe
			for ( int i1 = 1; i1 <= u1_; ++i1 ) {
				for ( int i2 = 1; i2 <= u2_; ++i2 ) {
					for ( int i3 = 1; i3 <= u3_; ++i3 ) {
						for ( int i4 = 1; i4 <= u4_; ++i4 ) {
							for ( int i5 = 1; i5 <= u5_; ++i5 ) {
								for ( int i6 = 1; i6 <= u6_; ++i6 ) {
									auto & v( operator ()( i1, i2, i3, i4, i5, i6 ) );
									v = v || a( i1, i2, i3, i4, i5, i6 );
								}
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// &&= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	and_equals( Array6S const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								auto & v( operator ()( i1, i2, i3, i4, i5, i6 ) );
								v = v && a( i1, i2, i3, i4, i5, i6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// ||= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	or_equals( Array6S const & a )
	{
		assert( conformable( a ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								auto & v( operator ()( i1, i2, i3, i4, i5, i6 ) );
								v = v || a( i1, i2, i3, i4, i5, i6 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

public: // Assignment: Value

	// = Value
	inline
	Array6S &
	operator =( T const & t )
	{
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) = t;
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// += Value
	inline
	Array6S &
	operator +=( T const & t )
	{
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) += t;
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// -= Value
	inline
	Array6S &
	operator -=( T const & t )
	{
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) -= t;
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// *= Value
	inline
	Array6S &
	operator *=( T const & t )
	{
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) *= t;
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// /= Value
	template< typename U, class = typename std::enable_if< std::is_floating_point< U >::value && std::is_assignable< T&, U >::value >::type >
	inline
	Array6S &
	operator /=( U const & u )
	{
		assert( u != U( 0 ) );
		U const inv_u( U( 1 ) / u );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) *= inv_u;
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// /= Value
	template< typename U, class = typename std::enable_if< !std::is_floating_point< U >::value && std::is_assignable< T&, U >::value >::type, typename = void >
	inline
	Array6S &
	operator /=( U const & u )
	{
		assert( u != U( 0 ) );
		for ( int i1 = 1; i1 <= u1_; ++i1 ) {
			for ( int i2 = 1; i2 <= u2_; ++i2 ) {
				for ( int i3 = 1; i3 <= u3_; ++i3 ) {
					for ( int i4 = 1; i4 <= u4_; ++i4 ) {
						for ( int i5 = 1; i5 <= u5_; ++i5 ) {
							for ( int i6 = 1; i6 <= u6_; ++i6 ) {
								operator ()( i1, i2, i3, i4, i5, i6 ) /= u;
							}
						}
					}
				}
			}
		}
		return *this;
	}

public: // Subscript

	// array( i1, i2, i3, i4, i5, i6 ) const
	inline
	T const &
	operator ()( int const i1, int const i2, int const i3, int const i4, int const i5, int const i6 ) const
	{
		assert( contains( i1, i2, i3, i4, i5, i6 ) );
		return data_[ k_ + ( m1_ * i1 ) + ( m2_ * i2 ) + ( m3_ * i3 ) + ( m4_ * i4 ) + ( m5_ * i5 ) + ( m6_ * i6 ) ];
	}

	// array( i1, i2, i3, i4, i5, i6 )
	inline
	T &
	operator ()( int const i1, int const i2, int const i3, int const i4, int const i5, int const i6 )
	{
		assert( contains( i1, i2, i3, i4, i5, i6 ) );
		return data_[ k_ + ( m1_ * i1 ) + ( m2_ * i2 ) + ( m3_ * i3 ) + ( m4_ * i4 ) + ( m5_ * i5 ) + ( m6_ * i6 ) ];
	}

	// Linear Index
	inline
	size_type
	index( int const i1, int const i2, int const i3, int const i4, int const i5, int const i6 ) const
	{
		return k_ + ( m1_ * i1 ) + ( m2_ * i2 ) + ( m3_ * i3 ) + ( m4_ * i4 ) + ( m5_ * i5 ) + ( m6_ * i6 );
	}

public: // Slice Proxy Generators

	// array( s1, s2, s3, s4, s5, s6 ) const
	inline
	Array6S
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, IS const & s5, IS const & s6 ) const
	{
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array6S( data_, k_, d1, d2, d3, d4, d5, d6 );
	}

	// array( i1, s2, s3, s4, s5, s6 ) const
	inline
	Array5S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d2, d3, d4, d5, d6 );
	}

	// array( s1, i2, s3, s4, s5, s6 ) const
	inline
	Array5S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d1, d3, d4, d5, d6 );
	}

	// array( s1, s2, i3, s4, s5, s6 ) const
	inline
	Array5S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d1, d2, d4, d5, d6 );
	}

	// array( s1, s2, s3, i4, s5, s6 ) const
	inline
	Array5S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d1, d2, d3, d5, d6 );
	}

	// array( s1, s2, s3, s4, i5, s6 ) const
	inline
	Array5S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d1, d2, d3, d4, d6 );
	}

	// array( s1, s2, s3, s4, s5, i6 ) const
	inline
	Array5S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array5S< T >( data_, k, d1, d2, d3, d4, d5 );
	}

	// array( i1, i2, s3, s4, s5, s6 ) const
	inline
	Array4S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d3, d4, d5, d6 );
	}

	// array( i1, s2, i3, s4, s5, s6 ) const
	inline
	Array4S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d2, d4, d5, d6 );
	}

	// array( i1, s2, s3, i4, s5, s6 ) const
	inline
	Array4S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d2, d3, d5, d6 );
	}

	// array( i1, s2, s3, s4, i5, s6 ) const
	inline
	Array4S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d2, d3, d4, d6 );
	}

	// array( i1, s2, s3, s4, s5, i6 ) const
	inline
	Array4S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d2, d3, d4, d5 );
	}

	// array( s1, i2, i3, s4, s5, s6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d4, d5, d6 );
	}

	// array( s1, i2, s3, i4, s5, s6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d3, d5, d6 );
	}

	// array( s1, i2, s3, s4, i5, s6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d3, d4, d6 );
	}

	// array( s1, i2, s3, s4, s5, i6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d1, d3, d4, d5 );
	}

	// array( s1, s2, i3, i4, s5, s6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d5, d6 );
	}

	// array( s1, s2, i3, s4, i5, s6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d4, d6 );
	}

	// array( s1, s2, i3, s4, s5, i6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d4, d5 );
	}

	// array( s1, s2, s3, i4, i5, s6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d3, d6 );
	}

	// array( s1, s2, s3, i4, s5, i6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d3, d5 );
	}

	// array( s1, s2, s3, s4, i5, i6 ) const
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d3, d4 );
	}

	// array( i1, i2, i3, s4, s5, s6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d4, d5, d6 );
	}

	// array( i1, i2, s3, i4, s5, s6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d3, d5, d6 );
	}

	// array( i1, i2, s3, s4, i5, s6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d3, d4, d6 );
	}

	// array( i1, i2, s3, s4, s5, i6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d3, d4, d5 );
	}

	// array( i1, s2, i3, i4, s5, s6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d2, d5, d6 );
	}

	// array( i1, s2, i3, s4, i5, s6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d2, d4, d6 );
	}

	// array( i1, s2, i3, s4, s5, i6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d2, d4, d5 );
	}

	// array( i1, s2, s3, i4, i5, s6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d2, d3, d6 );
	}

	// array( i1, s2, s3, i4, s5, i6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d2, d3, d5 );
	}

	// array( i1, s2, s3, s4, i5, i6 ) const
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d2, d3, d4 );
	}

	// array( s1, i2, i3, i4, s5, s6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d1, d5, d6 );
	}

	// array( s1, i2, i3, s4, i5, s6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d1, d4, d6 );
	}

	// array( s1, i2, i3, s4, s5, i6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d4, d5 );
	}

	// array( s1, i2, s3, i4, i5, s6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d1, d3, d6 );
	}

	// array( s1, i2, s3, i4, s5, i6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d3, d5 );
	}

	// array( s1, i2, s3, s4, i5, i6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d3, d4 );
	}

	// array( s1, s2, i3, i4, i5, s6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d1, d2, d6 );
	}

	// array( s1, s2, i3, i4, s5, i6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d2, d5 );
	}

	// array( s1, s2, i3, s4, i5, i6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d2, d4 );
	}

	// array( s1, s2, s3, i4, i5, i6 ) const
	inline
	Array3S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d2, d3 );
	}

	// array( s1, s2, i3, i4, i5, i6 ) const
	inline
	Array2S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d1, d2 );
	}

	// array( s1, i2, s3, i4, i5, i6 ) const
	inline
	Array2S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d1, d3 );
	}

	// array( s1, i2, i3, s4, i5, i6 ) const
	inline
	Array2S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d1, d4 );
	}

	// array( s1, i2, i3, i4, s5, i6 ) const
	inline
	Array2S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d1, d5 );
	}

	// array( s1, i2, i3, i4, i5, s6 ) const
	inline
	Array2S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d1, d6 );
	}

	// array( i1, s2, s3, i4, i5, i6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d2, d3 );
	}

	// array( i1, s2, i3, s4, i5, i6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d2, d4 );
	}

	// array( i1, s2, i3, i4, s5, i6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d2, d5 );
	}

	// array( i1, s2, i3, i4, i5, s6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d2, d6 );
	}

	// array( i1, i2, s3, s4, i5, i6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d3, d4 );
	}

	// array( i1, i2, s3, i4, s5, i6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d3, d5 );
	}

	// array( i1, i2, s3, i4, i5, s6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d3, d6 );
	}

	// array( i1, i2, i3, s4, s5, i6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d4, d5 );
	}

	// array( i1, i2, i3, s4, i5, s6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d4, d6 );
	}

	// array( i1, i2, i3, i4, s5, s6 ) const
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, int const i3, int const i4, IS const & s5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d5, d6 );
	}

	// array( s1, i2, i3, i4, i5, i6 ) const
	inline
	Array1S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d1 );
	}

	// array( i1, s2, i3, i4, i5, i6 ) const
	inline
	Array1S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d2 );
	}

	// array( i1, i2, s3, i4, i5, i6 ) const
	inline
	Array1S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d3 );
	}

	// array( i1, i2, i3, s4, i5, i6 ) const
	inline
	Array1S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, int const i5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d4 );
	}

	// array( i1, i2, i3, i4, s5, i6 ) const
	inline
	Array1S< T >
	operator ()( int const i1, int const i2, int const i3, int const i4, IS const & s5, int const i6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d5 );
	}

	// array( i1, i2, i3, i4, i5, s6 ) const
	inline
	Array1S< T >
	operator ()( int const i1, int const i2, int const i3, int const i4, int const i5, IS const & s6 ) const
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array1S< T >( data_, k, d6 );
	}

	// array( s1, s2, s3, s4, s5, s6 )
	inline
	Array6S
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, IS const & s5, IS const & s6 )
	{
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array6S( data_, k_, d1, d2, d3, d4, d5, d6 );
	}

	// array( i1, s2, s3, s4, s5, s6 )
	inline
	Array5S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d2, d3, d4, d5, d6 );
	}

	// array( s1, i2, s3, s4, s5, s6 )
	inline
	Array5S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d1, d3, d4, d5, d6 );
	}

	// array( s1, s2, i3, s4, s5, s6 )
	inline
	Array5S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d1, d2, d4, d5, d6 );
	}

	// array( s1, s2, s3, i4, s5, s6 )
	inline
	Array5S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d1, d2, d3, d5, d6 );
	}

	// array( s1, s2, s3, s4, i5, s6 )
	inline
	Array5S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array5S< T >( data_, k, d1, d2, d3, d4, d6 );
	}

	// array( s1, s2, s3, s4, s5, i6 )
	inline
	Array5S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array5S< T >( data_, k, d1, d2, d3, d4, d5 );
	}

	// array( i1, i2, s3, s4, s5, s6 )
	inline
	Array4S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d3, d4, d5, d6 );
	}

	// array( i1, s2, i3, s4, s5, s6 )
	inline
	Array4S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d2, d4, d5, d6 );
	}

	// array( i1, s2, s3, i4, s5, s6 )
	inline
	Array4S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d2, d3, d5, d6 );
	}

	// array( i1, s2, s3, s4, i5, s6 )
	inline
	Array4S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d2, d3, d4, d6 );
	}

	// array( i1, s2, s3, s4, s5, i6 )
	inline
	Array4S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d2, d3, d4, d5 );
	}

	// array( s1, i2, i3, s4, s5, s6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d4, d5, d6 );
	}

	// array( s1, i2, s3, i4, s5, s6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d3, d5, d6 );
	}

	// array( s1, i2, s3, s4, i5, s6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d3, d4, d6 );
	}

	// array( s1, i2, s3, s4, s5, i6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d1, d3, d4, d5 );
	}

	// array( s1, s2, i3, i4, s5, s6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d5, d6 );
	}

	// array( s1, s2, i3, s4, i5, s6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d4, d6 );
	}

	// array( s1, s2, i3, s4, s5, i6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d4, d5 );
	}

	// array( s1, s2, s3, i4, i5, s6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d3, d6 );
	}

	// array( s1, s2, s3, i4, s5, i6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d3, d5 );
	}

	// array( s1, s2, s3, s4, i5, i6 )
	inline
	Array4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array4S< T >( data_, k, d1, d2, d3, d4 );
	}

	// array( i1, i2, i3, s4, s5, s6 )
	inline
	Array3S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d4, d5, d6 );
	}

	// array( i1, i2, s3, i4, s5, s6 )
	inline
	Array3S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d3, d5, d6 );
	}

	// array( i1, i2, s3, s4, i5, s6 )
	inline
	Array3S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d3, d4, d6 );
	}

	// array( i1, i2, s3, s4, s5, i6 )
	inline
	Array3S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d3, d4, d5 );
	}

	// array( i1, s2, i3, i4, s5, s6 )
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d2, d5, d6 );
	}

	// array( i1, s2, i3, s4, i5, s6 )
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d2, d4, d6 );
	}

	// array( i1, s2, i3, s4, s5, i6 )
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d2, d4, d5 );
	}

	// array( i1, s2, s3, i4, i5, s6 )
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d2, d3, d6 );
	}

	// array( i1, s2, s3, i4, s5, i6 )
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d2, d3, d5 );
	}

	// array( i1, s2, s3, s4, i5, i6 )
	inline
	Array3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d2, d3, d4 );
	}

	// array( s1, i2, i3, i4, s5, s6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d1, d5, d6 );
	}

	// array( s1, i2, i3, s4, i5, s6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d1, d4, d6 );
	}

	// array( s1, i2, i3, s4, s5, i6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d4, d5 );
	}

	// array( s1, i2, s3, i4, i5, s6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d1, d3, d6 );
	}

	// array( s1, i2, s3, i4, s5, i6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d3, d5 );
	}

	// array( s1, i2, s3, s4, i5, i6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d3, d4 );
	}

	// array( s1, s2, i3, i4, i5, s6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array3S< T >( data_, k, d1, d2, d6 );
	}

	// array( s1, s2, i3, i4, s5, i6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d2, d5 );
	}

	// array( s1, s2, i3, s4, i5, i6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d2, d4 );
	}

	// array( s1, s2, s3, i4, i5, i6 )
	inline
	Array3S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array3S< T >( data_, k, d1, d2, d3 );
	}

	// array( s1, s2, i3, i4, i5, i6 )
	inline
	Array2S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d1, d2 );
	}

	// array( s1, i2, s3, i4, i5, i6 )
	inline
	Array2S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d1, d3 );
	}

	// array( s1, i2, i3, s4, i5, i6 )
	inline
	Array2S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d1, d4 );
	}

	// array( s1, i2, i3, i4, s5, i6 )
	inline
	Array2S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d1, d5 );
	}

	// array( s1, i2, i3, i4, i5, s6 )
	inline
	Array2S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d1, d6 );
	}

	// array( i1, s2, s3, i4, i5, i6 )
	inline
	Array2S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d2, d3 );
	}

	// array( i1, s2, i3, s4, i5, i6 )
	inline
	Array2S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d2, d4 );
	}

	// array( i1, s2, i3, i4, s5, i6 )
	inline
	Array2S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d2, d5 );
	}

	// array( i1, s2, i3, i4, i5, s6 )
	inline
	Array2S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d2, d6 );
	}

	// array( i1, i2, s3, s4, i5, i6 )
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d3, d4 );
	}

	// array( i1, i2, s3, i4, s5, i6 )
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d3, d5 );
	}

	// array( i1, i2, s3, i4, i5, s6 )
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d3, d6 );
	}

	// array( i1, i2, i3, s4, s5, i6 )
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array2S< T >( data_, k, d4, d5 );
	}

	// array( i1, i2, i3, s4, i5, s6 )
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d4, d6 );
	}

	// array( i1, i2, i3, i4, s5, s6 )
	inline
	Array2S< T >
	operator ()( int const i1, int const i2, int const i3, int const i4, IS const & s5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array2S< T >( data_, k, d5, d6 );
	}

	// array( s1, i2, i3, i4, i5, i6 )
	inline
	Array1S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		DS const d1( u1_, s1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d1 );
	}

	// array( i1, s2, i3, i4, i5, i6 )
	inline
	Array1S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		DS const d2( u2_, s2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d2 );
	}

	// array( i1, i2, s3, i4, i5, i6 )
	inline
	Array1S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		DS const d3( u3_, s3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d3 );
	}

	// array( i1, i2, i3, s4, i5, i6 )
	inline
	Array1S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, int const i5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		DS const d4( u4_, s4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d4 );
	}

	// array( i1, i2, i3, i4, s5, i6 )
	inline
	Array1S< T >
	operator ()( int const i1, int const i2, int const i3, int const i4, IS const & s5, int const i6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		DS const d5( u5_, s5, m5_ );
		k += slice_k( u6_, i6, m6_ );
		return Array1S< T >( data_, k, d5 );
	}

	// array( i1, i2, i3, i4, i5, s6 )
	inline
	Array1S< T >
	operator ()( int const i1, int const i2, int const i3, int const i4, int const i5, IS const & s6 )
	{
		std::int64_t k( k_ );
		k += slice_k( u1_, i1, m1_ );
		k += slice_k( u2_, i2, m2_ );
		k += slice_k( u3_, i3, m3_ );
		k += slice_k( u4_, i4, m4_ );
		k += slice_k( u5_, i5, m5_ );
		DS const d6( u6_, s6, m6_ );
		return Array1S< T >( data_, k, d6 );
	}

public: // Predicate

	// Contains Indexed Element?
	inline
	bool
	contains( int const i1, int const i2, int const i3, int const i4, int const i5, int const i6 ) const
	{
		if ( ! in_range( u1(), i1 ) ) return false;
		if ( ! in_range( u2(), i2 ) ) return false;
		if ( ! in_range( u3(), i3 ) ) return false;
		if ( ! in_range( u4(), i4 ) ) return false;
		if ( ! in_range( u5(), i5 ) ) return false;
		if ( ! in_range( u6(), i6 ) ) return false;
		return true;
	}

	// Conformable?
	template< typename U >
	inline
	bool
	conformable( Array6S< U > const & a ) const
	{
		return ( ( size1() == a.size1() ) && ( size2() == a.size2() ) && ( size3() == a.size3() ) && ( size4() == a.size4() ) && ( size5() == a.size5() ) && ( size6() == a.size6() ) );
	}

	// Conformable?
	template< class A, typename M >
	inline
	bool
	conformable( MArray6< A, M > const & a ) const
	{
		return ( ( size1() == a.size1() ) && ( size2() == a.size2() ) && ( size3() == a.size3() ) && ( size4() == a.size4() ) && ( size5() == a.size5() ) && ( size6() == a.size6() ) );
	}

	// Conformable?
	template< class A >
	inline
	bool
	conformable( A const & a ) const
	{
		return ( ( a.rank() == 6 ) && ( size1() == a.size1() ) && ( size2() == a.size2() ) && ( size3() == a.size3() ) && ( size4() == a.size4() ) && ( size5() == a.size5() ) && ( size6() == a.size6() ) );
	}

	// Equal Dimensions?
	template< typename U >
	inline
	bool
	equal_dimensions( Array6S< U > const & a ) const
	{
		return conformable( a );
	}

	// Equal Dimensions?
	template< class A, typename M >
	inline
	bool
	equal_dimensions( MArray6< A, M > const & a ) const
	{
		return conformable( a );
	}

	// Equal Dimensions?
	template< class A >
	inline
	bool
	equal_dimensions( A const & a ) const
	{
		return conformable( a );
	}

public: // Inspector

	// IndexRange of a Dimension
	inline
	IR
	I( int const d ) const
	{
		switch ( d ) {
		case 1:
			return I1();
		case 2:
			return I2();
		case 3:
			return I3();
		case 4:
			return I4();
		case 5:
			return I5();
		case 6:
			return I6();
		default:
			assert( false );
			return I1();
		}
	}

	// Upper Index of a Dimension
	inline
	int
	u( int const d ) const
	{
		switch ( d ) {
		case 1:
			return u1_;
		case 2:
			return u2_;
		case 3:
			return u3_;
		case 4:
			return u4_;
		case 5:
			return u5_;
		case 6:
			return u6_;
		default:
			assert( false );
			return u1_;
		}
	}

	// Size of a Dimension
	inline
	size_type
	size( int const d ) const
	{
		switch ( d ) {
		case 1:
			return size1();
		case 2:
			return size2();
		case 3:
			return size3();
		case 4:
			return size4();
		case 5:
			return size5();
		case 6:
			return size6();
		default:
			assert( false );
			return size1();
		}
	}

	// Size of a Dimension
	inline
	int
	isize( int const d ) const
	{
		switch ( d ) {
		case 1:
			return isize1();
		case 2:
			return isize2();
		case 3:
			return isize3();
		case 4:
			return isize4();
		case 5:
			return isize5();
		case 6:
			return isize6();
		default:
			assert( false );
			return isize1();
		}
	}

	// IndexRange of Dimension 1
	inline
	IR
	I1() const
	{
		return IR( 1, u1_ );
	}

	// Lower Index of Dimension 1
	inline
	int
	l1() const
	{
		return 1;
	}

	// Upper Index of Dimension 1
	inline
	int
	u1() const
	{
		return u1_;
	}

	// Size of Dimension 1
	inline
	size_type
	size1() const
	{
		return u1_;
	}

	// Size of Dimension 1
	inline
	int
	isize1() const
	{
		return u1_;
	}

	// IndexRange of Dimension 2
	inline
	IR
	I2() const
	{
		return IR( 1, u2_ );
	}

	// Lower Index of Dimension 2
	inline
	int
	l2() const
	{
		return 1;
	}

	// Upper Index of Dimension 2
	inline
	int
	u2() const
	{
		return u2_;
	}

	// Size of Dimension 2
	inline
	size_type
	size2() const
	{
		return u2_;
	}

	// Size of Dimension 2
	inline
	int
	isize2() const
	{
		return u2_;
	}

	// IndexRange of Dimension 3
	inline
	IR
	I3() const
	{
		return IR( 1, u3_ );
	}

	// Lower Index of Dimension 3
	inline
	int
	l3() const
	{
		return 1;
	}

	// Upper Index of Dimension 3
	inline
	int
	u3() const
	{
		return u3_;
	}

	// Size of Dimension 3
	inline
	size_type
	size3() const
	{
		return u3_;
	}

	// Size of Dimension 3
	inline
	int
	isize3() const
	{
		return u3_;
	}

	// IndexRange of Dimension 4
	inline
	IR
	I4() const
	{
		return IR( 1, u4_ );
	}

	// Lower Index of Dimension 4
	inline
	int
	l4() const
	{
		return 1;
	}

	// Upper Index of Dimension 4
	inline
	int
	u4() const
	{
		return u4_;
	}

	// Size of Dimension 4
	inline
	size_type
	size4() const
	{
		return u4_;
	}

	// Size of Dimension 4
	inline
	int
	isize4() const
	{
		return u4_;
	}

	// IndexRange of Dimension 5
	inline
	IR
	I5() const
	{
		return IR( 1, u5_ );
	}

	// Lower Index of Dimension 5
	inline
	int
	l5() const
	{
		return 1;
	}

	// Upper Index of Dimension 5
	inline
	int
	u5() const
	{
		return u5_;
	}

	// Size of Dimension 5
	inline
	size_type
	size5() const
	{
		return u5_;
	}

	// Size of Dimension 5
	inline
	int
	isize5() const
	{
		return u5_;
	}

	// IndexRange of Dimension 6
	inline
	IR
	I6() const
	{
		return IR( 1, u6_ );
	}

	// Lower Index of Dimension 6
	inline
	int
	l6() const
	{
		return 1;
	}

	// Upper Index of Dimension 6
	inline
	int
	u6() const
	{
		return u6_;
	}

	// Size of Dimension 6
	inline
	size_type
	size6() const
	{
		return u6_;
	}

	// Size of Dimension 6
	inline
	int
	isize6() const
	{
		return u6_;
	}

	// Shift for Proxy
	inline
	std::ptrdiff_t
	shift() const
	{
		return ( ( ( ( ( ( ( static_cast< std::ptrdiff_t >( u2_ + 1 ) * u3_ ) + 1 ) * u4_ ) + 1 ) * u5_ ) + 1 ) * u6_ ) + 1;
	}

public: // MArray Generators

	// Template Helpers
	template< typename U > class Wrapper {};
	typedef  typename std::conditional< std::is_class< T >::value, T, Wrapper< T > >::type  ClassT;

	// MArray Generator
	template< typename M >
	inline
	MArray6< Array6S const, M >
	ma( M ClassT::* pmem ) const
	{
		return MArray6< Array6S const, M >( *this, pmem );
	}

	// MArray Generator
	template< typename M >
	inline
	MArray6< Array6S, M >
	ma( M ClassT::* pmem )
	{
		return MArray6< Array6S, M >( *this, pmem );
	}

public: // Comparison: Predicate

	// Slice == Slice
	friend
	inline
	bool
	eq( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( ( &a == &b ) || a.empty() ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) == b( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Slice != Slice
	friend
	inline
	bool
	ne( Array6S const & a, Array6S const & b )
	{
		return ! eq( a, b );
	}

	// Slice < Slice
	friend
	inline
	bool
	lt( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( ( &a == &b ) || a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) < b( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Slice <= Slice
	friend
	inline
	bool
	le( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( ( &a == &b ) || a.empty() ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) <= b( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Slice > Slice
	friend
	inline
	bool
	gt( Array6S const & a, Array6S const & b )
	{
		return lt( b, a );
	}

	// Slice >= Slice
	friend
	inline
	bool
	ge( Array6S const & a, Array6S const & b )
	{
		return le( b, a );
	}

	// Slice == Value
	friend
	inline
	bool
	eq( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) == t ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Slice != Value
	friend
	inline
	bool
	ne( Array6S const & a, T const & t )
	{
		return ! eq( a, t );
	}

	// Slice < Value
	friend
	inline
	bool
	lt( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) < t ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Slice <= Value
	friend
	inline
	bool
	le( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) <= t ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Slice > Value
	friend
	inline
	bool
	gt( Array6S const & a, T const & t )
	{
		return lt( t, a );
	}

	// Slice >= Value
	friend
	inline
	bool
	ge( Array6S const & a, T const & t )
	{
		return le( t, a );
	}

	// Value == Slice
	friend
	inline
	bool
	eq( T const & t, Array6S const & a )
	{
		return eq( a, t );
	}

	// Value != Slice
	friend
	inline
	bool
	ne( T const & t, Array6S const & a )
	{
		return ! eq( a, t );
	}

	// Value < Slice
	friend
	inline
	bool
	lt( T const & t, Array6S const & a )
	{
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( t < a( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Value <= Slice
	friend
	inline
	bool
	le( T const & t, Array6S const & a )
	{
		if ( a.empty() ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( t <= a( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Value > Slice
	friend
	inline
	bool
	gt( T const & t, Array6S const & a )
	{
		return lt( a, t );
	}

	// Value >= Slice
	friend
	inline
	bool
	ge( T const & t, Array6S const & a )
	{
		return le( a, t );
	}

public: // Comparison: Predicate: Any

	// Any Slice == Slice
	friend
	inline
	bool
	any_eq( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		if ( &a == &b ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) == b( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Slice != Slice
	friend
	inline
	bool
	any_ne( Array6S const & a, Array6S const & b )
	{
		return ! eq( a, b );
	}

	// Any Slice < Slice
	friend
	inline
	bool
	any_lt( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		if ( &a == &b ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) < b( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Slice <= Slice
	friend
	inline
	bool
	any_le( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		if ( &a == &b ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) <= b( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Slice > Slice
	friend
	inline
	bool
	any_gt( Array6S const & a, Array6S const & b )
	{
		return any_lt( b, a );
	}

	// Any Slice >= Slice
	friend
	inline
	bool
	any_ge( Array6S const & a, Array6S const & b )
	{
		return any_le( b, a );
	}

	// Any Slice == Value
	friend
	inline
	bool
	any_eq( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) == t ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Slice != Value
	friend
	inline
	bool
	any_ne( Array6S const & a, T const & t )
	{
		return ! eq( a, t );
	}

	// Any Slice < Value
	friend
	inline
	bool
	any_lt( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) < t ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Slice <= Value
	friend
	inline
	bool
	any_le( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) <= t ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Slice > Value
	friend
	inline
	bool
	any_gt( Array6S const & a, T const & t )
	{
		return any_lt( t, a );
	}

	// Any Slice >= Value
	friend
	inline
	bool
	any_ge( Array6S const & a, T const & t )
	{
		return any_le( t, a );
	}

	// Any Value == Slice
	friend
	inline
	bool
	any_eq( T const & t, Array6S const & a )
	{
		return any_eq( a, t );
	}

	// Any Value != Slice
	friend
	inline
	bool
	any_ne( T const & t, Array6S const & a )
	{
		return ! eq( a, t );
	}

	// Any Value < Slice
	friend
	inline
	bool
	any_lt( T const & t, Array6S const & a )
	{
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( t < a( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Value <= Slice
	friend
	inline
	bool
	any_le( T const & t, Array6S const & a )
	{
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( t <= a( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Value > Slice
	friend
	inline
	bool
	any_gt( T const & t, Array6S const & a )
	{
		return any_lt( a, t );
	}

	// Any Value >= Slice
	friend
	inline
	bool
	any_ge( T const & t, Array6S const & a )
	{
		return any_le( a, t );
	}

public: // Comparison: Predicate: All

	// All Slice == Slice
	friend
	inline
	bool
	all_eq( Array6S const & a, Array6S const & b )
	{
		return eq( a, b );
	}

	// All Slice != Slice
	friend
	inline
	bool
	all_ne( Array6S const & a, Array6S const & b )
	{
		return ! any_eq( a, b );
	}

	// All Slice < Slice
	friend
	inline
	bool
	all_lt( Array6S const & a, Array6S const & b )
	{
		return lt( a, b );
	}

	// All Slice <= Slice
	friend
	inline
	bool
	all_le( Array6S const & a, Array6S const & b )
	{
		return le( a, b );
	}

	// All Slice > Slice
	friend
	inline
	bool
	all_gt( Array6S const & a, Array6S const & b )
	{
		return gt( a, b );
	}

	// All Slice >= Slice
	friend
	inline
	bool
	all_ge( Array6S const & a, Array6S const & b )
	{
		return ge( a, b );
	}

	// All Slice == Value
	friend
	inline
	bool
	all_eq( Array6S const & a, T const & t )
	{
		return eq( a, t );
	}

	// All Slice != Value
	friend
	inline
	bool
	all_ne( Array6S const & a, T const & t )
	{
		return ! any_eq( a, t );
	}

	// All Slice < Value
	friend
	inline
	bool
	all_lt( Array6S const & a, T const & t )
	{
		return lt( a, t );
	}

	// All Slice <= Value
	friend
	inline
	bool
	all_le( Array6S const & a, T const & t )
	{
		return le( a, t );
	}

	// All Slice > Value
	friend
	inline
	bool
	all_gt( Array6S const & a, T const & t )
	{
		return gt( a, t );
	}

	// All Slice >= Value
	friend
	inline
	bool
	all_ge( Array6S const & a, T const & t )
	{
		return ge( a, t );
	}

	// All Value == Slice
	friend
	inline
	bool
	all_eq( T const & t, Array6S const & a )
	{
		return eq( t, a );
	}

	// All Value != Slice
	friend
	inline
	bool
	all_ne( T const & t, Array6S const & a )
	{
		return ! any_eq( t, a );
	}

	// All Value < Slice
	friend
	inline
	bool
	all_lt( T const & t, Array6S const & a )
	{
		return lt( t, a );
	}

	// All Value <= Slice
	friend
	inline
	bool
	all_le( T const & t, Array6S const & a )
	{
		return le( t, a );
	}

	// All Value > Slice
	friend
	inline
	bool
	all_gt( T const & t, Array6S const & a )
	{
		return gt( t, a );
	}

	// All Value >= Slice
	friend
	inline
	bool
	all_ge( T const & t, Array6S const & a )
	{
		return ge( t, a );
	}

public: // Comparison: Count

	// Count Slice == Slice
	friend
	inline
	size_type
	count_eq( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		if ( &a == &b ) return a.size_;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) == b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Slice != Slice
	friend
	inline
	size_type
	count_ne( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		if ( &a == &b ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) != b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Slice < Slice
	friend
	inline
	size_type
	count_lt( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		if ( &a == &b ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) < b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Slice <= Slice
	friend
	inline
	size_type
	count_le( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		if ( &a == &b ) return a.size_;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) <= b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Slice > Slice
	friend
	inline
	size_type
	count_gt( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		if ( &a == &b ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) > b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Slice >= Slice
	friend
	inline
	size_type
	count_ge( Array6S const & a, Array6S const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		if ( &a == &b ) return a.size_;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) >= b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Slice == Value
	friend
	inline
	size_type
	count_eq( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) == t ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Value == Slice
	friend
	inline
	size_type
	count_eq( T const & t, Array6S const & a )
	{
		return count_eq( a, t );
	}

	// Count Slice != Value
	friend
	inline
	size_type
	count_ne( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) != t ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Value != Slice
	friend
	inline
	size_type
	count_ne( T const & t, Array6S const & a )
	{
		return count_ne( a, t );
	}

	// Count Slice < Value
	friend
	inline
	size_type
	count_lt( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) < t ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Value < Slice
	friend
	inline
	size_type
	count_lt( T const & t, Array6S const & a )
	{
		return count_gt( a, t );
	}

	// Count Slice <= Value
	friend
	inline
	size_type
	count_le( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) <= t ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Value <= Slice
	friend
	inline
	size_type
	count_le( T const & t, Array6S const & a )
	{
		return count_ge( a, t );
	}

	// Count Slice > Value
	friend
	inline
	size_type
	count_gt( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) > t ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Value > Slice
	friend
	inline
	size_type
	count_gt( T const & t, Array6S const & a )
	{
		return count_lt( a, t );
	}

	// Count Slice >= Value
	friend
	inline
	size_type
	count_ge( Array6S const & a, T const & t )
	{
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) >= t ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Value >= Slice
	friend
	inline
	size_type
	count_ge( T const & t, Array6S const & a )
	{
		return count_le( a, t );
	}

public: // Comparison: Predicate: MArray

	// Array6S == MArray6
	template< class A >
	friend
	inline
	bool
	eq( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) == b( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Array6S != MArray6
	template< class A >
	friend
	inline
	bool
	ne( Array6S const & a, MArray6< A, T > const & b )
	{
		return ! eq( a, b );
	}

	// Array6S < MArray6
	template< class A >
	friend
	inline
	bool
	lt( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) < b( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Array6S <= MArray6
	template< class A >
	friend
	inline
	bool
	le( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) <= b( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Array6S > MArray6
	template< class A >
	friend
	inline
	bool
	gt( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) > b( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// Array6S >= MArray6
	template< class A >
	friend
	inline
	bool
	ge( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( ! ( a( i1, i2, i3, i4, i5, i6 ) >= b( i1, i2, i3, i4, i5, i6 ) ) ) return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	// MArray6 == Array6S
	template< class A >
	friend
	inline
	bool
	eq( MArray6< A, T > const & a, Array6S const & b )
	{
		return eq( b, a );
	}

	// MArray6 != Array6S
	template< class A >
	friend
	inline
	bool
	ne( MArray6< A, T > const & a, Array6S const & b )
	{
		return ne( b, a );
	}

	// MArray6 < Array6S
	template< class A >
	friend
	inline
	bool
	lt( MArray6< A, T > const & a, Array6S const & b )
	{
		return gt( b, a );
	}

	// MArray6 <= Array6S
	template< class A >
	friend
	inline
	bool
	le( MArray6< A, T > const & a, Array6S const & b )
	{
		return ge( b, a );
	}

	// MArray6 > Array6S
	template< class A >
	friend
	inline
	bool
	gt( MArray6< A, T > const & a, Array6S const & b )
	{
		return lt( b, a );
	}

	// MArray6 >= Array6S
	template< class A >
	friend
	inline
	bool
	ge( MArray6< A, T > const & a, Array6S const & b )
	{
		return le( b, a );
	}

public: // Comparison: Predicate: Any: MArray

	// Any Array6S == MArray6
	template< class A >
	friend
	inline
	bool
	any_eq( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) == b( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Array6S != MArray6
	template< class A >
	friend
	inline
	bool
	any_ne( Array6S const & a, MArray6< A, T > const & b )
	{
		return ! eq( a, b );
	}

	// Any Array6S < MArray6
	template< class A >
	friend
	inline
	bool
	any_lt( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) < b( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Array6S <= MArray6
	template< class A >
	friend
	inline
	bool
	any_le( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) <= b( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Array6S > MArray6
	template< class A >
	friend
	inline
	bool
	any_gt( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) > b( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any Array6S >= MArray6
	template< class A >
	friend
	inline
	bool
	any_ge( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) >= b( i1, i2, i3, i4, i5, i6 ) ) return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// Any MArray6 == Array6S
	template< class A >
	friend
	inline
	bool
	any_eq( MArray6< A, T > const & a, Array6S const & b )
	{
		return any_eq( b, a );
	}

	// Any MArray6 != Array6S
	template< class A >
	friend
	inline
	bool
	any_ne( MArray6< A, T > const & a, Array6S const & b )
	{
		return any_ne( b, a );
	}

	// Any MArray6 < Array6S
	template< class A >
	friend
	inline
	bool
	any_lt( MArray6< A, T > const & a, Array6S const & b )
	{
		return any_gt( b, a );
	}

	// Any MArray6 <= Array6S
	template< class A >
	friend
	inline
	bool
	any_le( MArray6< A, T > const & a, Array6S const & b )
	{
		return any_ge( b, a );
	}

	// Any MArray6 > Array6S
	template< class A >
	friend
	inline
	bool
	any_gt( MArray6< A, T > const & a, Array6S const & b )
	{
		return any_lt( b, a );
	}

	// Any MArray6 >= Array6S
	template< class A >
	friend
	inline
	bool
	any_ge( MArray6< A, T > const & a, Array6S const & b )
	{
		return any_le( b, a );
	}

public: // Comparison: Predicate: All: MArray

	// All Array6S == MArray6
	template< class A >
	friend
	inline
	bool
	all_eq( Array6S const & a, MArray6< A, T > const & b )
	{
		return eq( a, b );
	}

	// All Array6S != MArray6
	template< class A >
	friend
	inline
	bool
	all_ne( Array6S const & a, MArray6< A, T > const & b )
	{
		return ! any_eq( a, b );
	}

	// All Array6S < MArray6
	template< class A >
	friend
	inline
	bool
	all_lt( Array6S const & a, MArray6< A, T > const & b )
	{
		return lt( a, b );
	}

	// All Array6S <= MArray6
	template< class A >
	friend
	inline
	bool
	all_le( Array6S const & a, MArray6< A, T > const & b )
	{
		return le( a, b );
	}

	// All Array6S > MArray6
	template< class A >
	friend
	inline
	bool
	all_gt( Array6S const & a, MArray6< A, T > const & b )
	{
		return gt( a, b );
	}

	// All Array6S >= MArray6
	template< class A >
	friend
	inline
	bool
	all_ge( Array6S const & a, MArray6< A, T > const & b )
	{
		return ge( a, b );
	}

	// All MArray6 == Array6S
	template< class A >
	friend
	inline
	bool
	all_eq( MArray6< A, T > const & a, Array6S const & b )
	{
		return all_eq( b, a );
	}

	// All MArray6 != Array6S
	template< class A >
	friend
	inline
	bool
	all_ne( MArray6< A, T > const & a, Array6S const & b )
	{
		return all_ne( b, a );
	}

	// All MArray6 < Array6S
	template< class A >
	friend
	inline
	bool
	all_lt( MArray6< A, T > const & a, Array6S const & b )
	{
		return all_gt( b, a );
	}

	// All MArray6 <= Array6S
	template< class A >
	friend
	inline
	bool
	all_le( MArray6< A, T > const & a, Array6S const & b )
	{
		return all_ge( b, a );
	}

	// All MArray6 > Array6S
	template< class A >
	friend
	inline
	bool
	all_gt( MArray6< A, T > const & a, Array6S const & b )
	{
		return all_lt( b, a );
	}

	// All MArray6 >= Array6S
	template< class A >
	friend
	inline
	bool
	all_ge( MArray6< A, T > const & a, Array6S const & b )
	{
		return all_le( b, a );
	}

public: // Comparison: Count: MArray

	// Count Array6S == MArray6
	template< class A >
	friend
	inline
	size_type
	count_eq( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) == b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Array6S != MArray6
	template< class A >
	friend
	inline
	size_type
	count_ne( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) != b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Array6S < MArray6
	template< class A >
	friend
	inline
	size_type
	count_lt( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) < b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Array6S <= MArray6
	template< class A >
	friend
	inline
	size_type
	count_le( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) <= b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Array6S > MArray6
	template< class A >
	friend
	inline
	size_type
	count_gt( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) > b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count Array6S >= MArray6
	template< class A >
	friend
	inline
	size_type
	count_ge( Array6S const & a, MArray6< A, T > const & b )
	{
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type n( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								if ( a( i1, i2, i3, i4, i5, i6 ) >= b( i1, i2, i3, i4, i5, i6 ) ) ++n;
							}
						}
					}
				}
			}
		}
		return n;
	}

	// Count MArray6 == Array6S
	template< class A >
	friend
	inline
	size_type
	count_eq( MArray6< A, T > const & a, Array6S const & b )
	{
		return count_eq( b, a );
	}

	// Count MArray6 != Array6S
	template< class A >
	friend
	inline
	size_type
	count_ne( MArray6< A, T > const & a, Array6S const & b )
	{
		return count_ne( b, a );
	}

	// Count MArray6 < Array6S
	template< class A >
	friend
	inline
	size_type
	count_lt( MArray6< A, T > const & a, Array6S const & b )
	{
		return count_gt( b, a );
	}

	// Count MArray6 <= Array6S
	template< class A >
	friend
	inline
	size_type
	count_le( MArray6< A, T > const & a, Array6S const & b )
	{
		return count_ge( b, a );
	}

	// Count MArray6 > Array6S
	template< class A >
	friend
	inline
	size_type
	count_gt( MArray6< A, T > const & a, Array6S const & b )
	{
		return count_lt( b, a );
	}

	// Count MArray6 >= Array6S
	template< class A >
	friend
	inline
	size_type
	count_ge( MArray6< A, T > const & a, Array6S const & b )
	{
		return count_le( b, a );
	}

private: // Methods

	// Contiguous?
	inline
	bool
	computed_contiguous() const
	{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsequenced"
		std::int64_t u( u6_ );
		return ( m6_ == 1 ) && ( m5_ == u ) && ( m4_ == ( u *= u5_ ) ) && ( m3_ == ( u *= u4_ ) ) && ( m2_ == ( u *= u3_ ) ) && ( m1_ == ( u *= u2_ ) );
#pragma clang diagnostic pop
	}

	// Memory Range Set
	inline
	void
	data_set()
	{
		if ( size_ > 0u ) { // Non-empty slice
			data_beg_ = data_end_ = data_ + k_;
			data_beg_ += m1_ * ( m1_ >= 0 ? 1 : u1_ );
			data_end_ += m1_ * ( m1_ <= 0 ? 1 : u1_ );
			data_beg_ += m2_ * ( m2_ >= 0 ? 1 : u2_ );
			data_end_ += m2_ * ( m2_ <= 0 ? 1 : u2_ );
			data_beg_ += m3_ * ( m3_ >= 0 ? 1 : u3_ );
			data_end_ += m3_ * ( m3_ <= 0 ? 1 : u3_ );
			data_beg_ += m4_ * ( m4_ >= 0 ? 1 : u4_ );
			data_end_ += m4_ * ( m4_ <= 0 ? 1 : u4_ );
			data_beg_ += m5_ * ( m5_ >= 0 ? 1 : u5_ );
			data_end_ += m5_ * ( m5_ <= 0 ? 1 : u5_ );
			data_beg_ += m6_ * ( m6_ >= 0 ? 1 : u6_ );
			data_end_ += m6_ * ( m6_ <= 0 ? 1 : u6_ );
		} else {
			data_ = data_beg_ = data_end_ = nullptr;
		}
	}

private: // Data

	std::int64_t const m6_; // Multiplier of dim 6
	std::int64_t const m5_; // Multiplier of dim 5
	std::int64_t const m4_; // Multiplier of dim 4
	std::int64_t const m3_; // Multiplier of dim 3
	std::int64_t const m2_; // Multiplier of dim 2
	std::int64_t const m1_; // Multiplier of dim 1
	std::int64_t const k_; // Constant
	int const u1_; // Upper index of dim 1
	int const u2_; // Upper index of dim 2
	int const u3_; // Upper index of dim 3
	int const u4_; // Upper index of dim 4
	int const u5_; // Upper index of dim 5
	int const u6_; // Upper index of dim 6

}; // Array6S

// Conformable?
template< typename U, typename V >
inline
bool
conformable( Array6S< U > const & a, Array6S< V > const & b )
{
	return a.conformable( b );
}

// Conformable?
template< typename U, class A, typename M >
inline
bool
conformable( Array6S< U > const & a, MArray6< A, M > const & b )
{
	return a.conformable( b );
}

// Conformable?
template< class A, typename M, typename V >
inline
bool
conformable( MArray6< A, M > const & a, Array6S< V > const & b )
{
	return b.conformable( a );
}

// Stream >> Array6S
template< typename T >
inline
std::istream &
operator >>( std::istream & stream, Array6S< T > & a )
{
	if ( stream && ( a.size() > 0u ) ) {
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								stream >> a( i1, i2, i3, i4, i5, i6 );
								if ( ! stream ) break;
							} if ( ! stream ) break;
						} if ( ! stream ) break;
					} if ( ! stream ) break;
				} if ( ! stream ) break;
			} if ( ! stream ) break;
		}
	}
	return stream;
}

// Stream << Array6S
template< typename T >
inline
std::ostream &
operator <<( std::ostream & stream, Array6S< T > const & a )
{
	typedef  TypeTraits< T >  Traits;
	if ( stream && ( a.size() > 0u ) ) {
		std::ios_base::fmtflags const old_flags( stream.flags() );
		std::streamsize const old_precision( stream.precision( Traits::precision ) );
		stream << std::right << std::showpoint << std::uppercase;
		int const w( Traits::iwidth );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								stream << std::setw( w ) << a( i1, i2, i3, i4, i5, i6 ) << ' ';
								if ( ! stream ) break;
							} if ( ! stream ) break;
						} if ( ! stream ) break;
					} if ( ! stream ) break;
				} if ( ! stream ) break;
			} if ( ! stream ) break;
		}
		stream.precision( old_precision );
		stream.flags( old_flags );
	}
	return stream;
}

// Read an Array6S from a Binary File
template< typename T >
inline
std::istream &
read_binary( std::istream & stream, Array6S< T > & a )
{
	std::size_t const n( a.size() );
	if ( stream && ( n > 0u ) ) {
		std::size_t const type_size( sizeof( T ) / sizeof( std::istream::char_type ) );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								stream.read( ( std::istream::char_type * )&a( i1, i2, i3, i4, i5, i6 ), type_size );
								if ( ! stream ) break;
							} if ( ! stream ) break;
						} if ( ! stream ) break;
					} if ( ! stream ) break;
				} if ( ! stream ) break;
			} if ( ! stream ) break;
		}
	}
	return stream;
}

// Write an Array6S to a Binary File
template< typename T >
inline
std::ostream &
write_binary( std::ostream & stream, Array6S< T > const & a )
{
	std::size_t const n( a.size() );
	if ( stream && ( n > 0u ) ) {
		std::size_t const type_size( sizeof( T ) / sizeof( std::ostream::char_type ) );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								stream.write( ( std::ostream::char_type const * )&a( i1, i2, i3, i4, i5, i6 ), type_size );
								if ( ! stream ) break;
							} if ( ! stream ) break;
						} if ( ! stream ) break;
					} if ( ! stream ) break;
				} if ( ! stream ) break;
			} if ( ! stream ) break;
		}
	}
	return stream;
}

namespace fmt {

// List-Directed Format: Array6S
template< typename T >
inline
std::string
LD( Array6S< T > const & a )
{
	std::string s;
	std::size_t const n( a.size() );
	if ( n > 0u ) {
		s.reserve( n * TypeTraits< T >::width );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
						for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
							for ( int i6 = 1, e6 = a.u6(); i6 <= e6; ++i6 ) {
								s.append( fmt::LD( a( i1, i2, i3, i4, i5, i6 ) ) );
							}
						}
					}
				}
			}
		}
	}
	return s;
}

} // fmt

} // ObjexxFCL

#endif // ObjexxFCL_Array6S_hh_INCLUDED
