#pragma once

template< typename _Ty, _Ty value >
struct constant_holder_t {
	enum class e_value_holder : _Ty {
		m_value = value
	};
};

#define CONSTANT( value ) ( static_cast< decltype( value ) >( constant_holder_t< decltype( value ), value >::e_value_holder::m_value ) )

namespace fnv1a {
	constexpr auto fnv_basis = 14695981039346656037ull;
	constexpr auto fnv_prime = 1099511628211ull;

	__forceinline uint64_t rt( const char* txt ) {
		auto hash = fnv_basis;

		size_t length = 0;
		while ( txt[ length ] )
			++length;

		for ( auto i = 0u; i < length; i++ ) {
			hash ^= txt[ i ];
			hash *= fnv_prime;
		}

		return hash;
	}

	constexpr uint64_t ct( const char* txt, uint64_t value = fnv_basis ) {
		return !*txt ? value : ct( txt + 1, static_cast< uint64_t >( 1ull * ( value ^ static_cast< uint8_t >( *txt ) ) * fnv_prime ) );
	}
}

#define HASH( s ) CONSTANT( fnv1a::ct( s ) )
#define HASH_RT( s ) fnv1a::rt( s )