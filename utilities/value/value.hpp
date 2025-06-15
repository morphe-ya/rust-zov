#pragma once

#include "../../includes/includes.hpp"

#define o( any ) _lxy_oxor_any_::oxor_any< decltype( _lxy_oxor_any_::typeofs( any ) ), _lxy_oxor_any_::array_size( any ), __COUNTER__ >( any, _lxy_::make_index_sequence< sizeof( decltype( any ) ) >( ) )._get( )

namespace _lxy_ {
	template< typename _Ty >
	struct type_cast { using type = _Ty; };

	template<>
	struct type_cast< float > { using type = uint32_t; };

	template<>
	struct type_cast< double > { using type = uint64_t; };

	template< class _Ty, _Ty _Val >
	struct integral_constant {
		static constexpr _Ty value = _Val;

		using value_type = _Ty;
		using type = integral_constant;

		constexpr operator value_type( ) const noexcept {
			return value;
		}

		constexpr value_type operator()( ) const noexcept {
			return value;
		}
	};

	template< size_t... Ints >
	struct index_sequence {
		using type = index_sequence;
		using value_type = size_t;

		static constexpr size_t size( ) noexcept {
			return sizeof...( Ints );
		}
	};

	template< class Sequence1, class Sequence2 >
	struct _merge_and_renumber;

	template< size_t... I1, size_t... I2 >
	struct _merge_and_renumber< index_sequence< I1... >, index_sequence< I2... > >
		: index_sequence< I1..., ( sizeof...( I1 ) + I2 )... > { };

	template< size_t N >
	struct make_index_sequence
		: _merge_and_renumber< typename make_index_sequence< N / 2 >::type,
		typename make_index_sequence< N - N / 2 >::type > { };

	template<> struct make_index_sequence< 0 > : index_sequence< > { };
	template<> struct make_index_sequence< 1 > : index_sequence< 0 > { };
}

namespace _lxy_oxor_any_ {
	size_t& X( );
	size_t& Y( );

	static constexpr size_t base_key = static_cast< size_t >(
		( ( size_t )__TIME__[ 7 ] - '0' ) +
		( ( size_t )__TIME__[ 6 ] - '0' ) * 10 +
		( ( size_t )__TIME__[ 4 ] - '0' ) * 60 +
		( ( size_t )__TIME__[ 3 ] - '0' ) * 600 +
		( ( size_t )__TIME__[ 1 ] - '0' ) * 3600 +
		( ( size_t )__TIME__[ 0 ] - '0' ) * 36000 );

	template< uint64_t s, size_t n >
	class random_constant_64 {
		static constexpr uint64_t x = s ^ ( s << 13 );
		static constexpr uint64_t y = x ^ ( x >> 7 );
		static constexpr uint64_t z = y ^ ( y << 17 );
	public:
		static constexpr uint64_t value = random_constant_64< z, n - 1 >::value;
	};

	template< uint64_t s >
	class random_constant_64< s, 0 > {
	public:
		static constexpr uint64_t value = s;
	};

	template< typename T, size_t size >
	static __forceinline constexpr size_t array_size( const T( & )[ size ] ) { return size; }

	template< typename T >
	static __forceinline constexpr size_t array_size( T ) { return 0; }

	template< typename T, size_t size >
	static inline T typeofs( const T( & )[ size ] );

	template< typename T >
	static inline T typeofs( T );

	template< size_t key >
	static __forceinline constexpr uint8_t encrypt_byte( uint8_t c, size_t i ) {
		return static_cast< uint8_t >( ( ( c + ( key * 7 ) ) ^ ( i + key ) ) );
	}

	template< size_t key >
	static __forceinline constexpr uint8_t decrypt_byte( uint8_t c, size_t i ) {
		size_t a = c;
		size_t b = i + key;
		size_t a_xor_b = ( a + b ) - ( ( a & b ) + ( b & a ) );

		return static_cast< uint8_t >( ( a_xor_b ) - ( key * 7 ) );
	}

	template< size_t key >
	static __forceinline constexpr size_t limit( ) {
		constexpr size_t bcf_value[ ] = { 1, 2, 3, 4, 5, 6, 8, 9, 10, 16, 32, 40, 64, 66, 100, 128, 512, 1000, 1024, 4096, 'a', 'z', 'A', 'Z', '*' };
		return bcf_value[ key % ( sizeof( bcf_value ) / sizeof( bcf_value[ 0 ] ) ) ];
	}

	template< typename return_type, size_t key, size_t size >
	static __forceinline const return_type decrypt( uint8_t( &buffer )[ size ] ) {
		for ( volatile size_t i{ }; i < size; i++ ) {
			buffer[ i ] = decrypt_byte< key >( buffer[ i ], i );
		}

		return reinterpret_cast< return_type >( buffer );
	}

	static __forceinline constexpr size_t align( size_t n, size_t a ) {
		return ( n + a - 1 ) & ~( a - 1 );
	}

	template< typename any_t, size_t ary_size, size_t counter >
	class oxor_any {
		static constexpr size_t size = align( ary_size * sizeof( any_t ), 16 )
			+ random_constant_64< counter ^ base_key, ( counter^ base_key ) % 12 >::value % ( 16 + 1 );

		static constexpr size_t key = random_constant_64< counter ^ base_key, ( size ^ base_key ) % 128 >::value;
		alignas( 0x10 ) uint8_t buffer[ size ];
	public:
		template< size_t... indices >
		__forceinline constexpr oxor_any( const any_t( &any )[ ary_size ], _lxy_::index_sequence< indices... > ) :
			buffer{ encrypt_byte< key >( ( ( uint8_t* )&any )[ indices ], indices )... } { }

		__forceinline const any_t* _get( ) { return decrypt< const any_t*, key >( buffer ); }
	};

	template< typename any_t, size_t counter >
	class oxor_any< any_t, 0, counter > {
		static constexpr size_t size = align( sizeof( any_t ), 16 )
			+ random_constant_64< counter ^ base_key, ( counter ^ base_key ) % 128 >::value % ( 16 + 1 );

		static constexpr size_t key = random_constant_64< counter ^ base_key, ( size ^ base_key ) % 128 >::value;
		alignas( 0x10 ) uint8_t buffer[ size ];

	public:
		template< size_t... indices >
		__forceinline constexpr oxor_any( any_t any, _lxy_::index_sequence< indices... > ) :
			buffer{ encrypt_byte< key >( reinterpret_cast< uint8_t* >( &any )[ indices ], indices )... } { }

		__forceinline const any_t _get( ) { return *decrypt< const any_t*, key >( buffer ); }
	};
}