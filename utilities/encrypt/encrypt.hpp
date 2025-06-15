#pragma once

#include <immintrin.h>

#include <cstdint>
#include <cstddef>
#include <utility>
#include <type_traits>

#define e_key( buf ) ::encrypt::encrypt_c( [ ]( ) { return buf; }, std::integral_constant< size_t, sizeof( buf ) / sizeof( *buf ) >{ }, std::make_index_sequence< ::encrypt::detail::_buffer_size< sizeof( buf )>( )>{ } )
#define e( buf ) e_key( buf ).crypt_get( )

namespace encrypt {
    namespace detail {
        template< size_t Size >
        __forceinline constexpr size_t _buffer_size( ) {
            return ( ( Size / 16 ) + ( Size % 16 != 0 ) ) * 2;
        }

        template< uint32_t seed >
        __forceinline constexpr uint32_t key4( ) noexcept {
            uint32_t value = seed;

            for ( char c : __TIME__ )
                value = static_cast< uint32_t >( ( value ^ c ) * 16777619ull );

            return value;
        }

        template< size_t Size >
        __forceinline constexpr uint64_t key8( ) {
            constexpr auto first_part = key4< 2166136261 + Size >( );
            constexpr auto second_part = key4< first_part >( );

            return ( static_cast< uint64_t >( first_part ) << 32 ) | second_part;
        }

        template< size_t n, class _Ty >
        __forceinline constexpr uint64_t
            load_xored_str8( uint64_t key, size_t idx, const _Ty* str ) noexcept {
            using cast_type = typename std::make_unsigned< _Ty >::type;

            constexpr auto value_size = sizeof( _Ty );
            constexpr auto idx_offset = 8 / value_size;

            uint64_t value = key;

            for ( size_t i = 0; i < idx_offset && i + idx * idx_offset < n; ++i )
                value ^=  ( uint64_t{ static_cast< cast_type >( str[ i + idx * idx_offset ] ) } << ( ( i % idx_offset ) * 8 * value_size ) );

            return value;
        }

        __forceinline uint64_t load_from_reg( uint64_t value ) noexcept {
            volatile uint64_t reg = value;
            return reg;
        }
    }

    template< class _Ty, size_t Size, class keys, class indices >
    class encrypt_c;

    template< class _Ty, size_t Size, uint64_t... Keys, size_t... indices >
    class encrypt_c< _Ty, Size, std::integer_sequence< uint64_t, Keys... >, std::index_sequence< indices... > > {
        constexpr static inline uint64_t alignment = 16;
        alignas( alignment ) uint64_t _storage[ sizeof...( Keys ) ];

    public:
        using value_type = _Ty;
        using size_type = size_t;
        using pointer = _Ty*;
        using const_pointer = const _Ty*;

        template< class L >
        __forceinline encrypt_c( L l, std::integral_constant< size_t, Size >, std::index_sequence< indices... > ) noexcept
            : _storage{ ::encrypt::detail::load_from_reg( ( std::integral_constant<uint64_t, detail::load_xored_str8< Size >( Keys, indices, l( ) )>::value ) )... } { }

        __forceinline constexpr size_type size( ) const noexcept {
            return Size - 1;
        }

        __forceinline void crypt( ) noexcept {
            alignas( alignment ) uint64_t keys[ ]{ ::encrypt::detail::load_from_reg( keys )... };

            ( ( indices >= sizeof( _storage ) / 16 ? static_cast< void >( 0 ) : _mm_store_si128(
                reinterpret_cast< __m128i* >( _storage ) + indices,
                _mm_xor_si128( _mm_load_si128( reinterpret_cast< const __m128i* >( _storage ) + indices ),
                _mm_load_si128( reinterpret_cast< const __m128i* >( keys ) + indices ) ) ) ), ... );
        }

        __forceinline const_pointer get( ) const noexcept {
            return reinterpret_cast< const_pointer >( _storage );
        }

        __forceinline pointer get( ) noexcept {
            return reinterpret_cast< pointer >( _storage );
        }

        __forceinline pointer crypt_get( ) noexcept {
            alignas( alignment ) uint64_t keys[ ]{ ::encrypt::detail::load_from_reg( Keys )... };

            ( ( indices >= sizeof( _storage ) / 16 ? static_cast< void >( 0 ) : _mm_store_si128(
                reinterpret_cast< __m128i* >( _storage ) + indices,
                _mm_xor_si128( _mm_load_si128( reinterpret_cast< const __m128i* >( _storage ) + indices ),
                _mm_load_si128( reinterpret_cast< const __m128i* >( keys ) + indices ) ) ) ), ... );

            return ( pointer )( _storage );
        }
    };

    template< class L, size_t Size, size_t... indices >
    encrypt_c( L l, std::integral_constant< size_t, Size >, std::index_sequence< indices... > ) -> encrypt_c<
        std::remove_const_t< std::remove_reference_t< decltype( l( )[ 0 ] ) > >,
        Size,
        std::integer_sequence< uint64_t, detail::key8< indices >( )... >,
        std::index_sequence< indices... > >;
}