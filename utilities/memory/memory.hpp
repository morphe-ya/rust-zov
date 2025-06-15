#pragma once

#include "../../includes/includes.hpp"

#include "../value/value.hpp"

namespace memory {
	__forceinline bool is_valid( const uint64_t address ) {
		if ( address >= o( 0x10000 ) && address <= o( 0x7FFFFFFEFFFF ) )
			return true;

		return false;
	}

	__forceinline bool is_valid( const void* address ) {
		if ( reinterpret_cast< uint64_t >( address ) >= o( 0x10000 ) && reinterpret_cast< uint64_t >( address ) <= o( 0x7FFFFFFEFFFF ) )
			return true;

		return false;
	}

	__forceinline void copy( const uint64_t dst, const void* src, const size_t size ) {
		memcpy( reinterpret_cast< void* >( dst ), src, size );
	}

	__forceinline void set( const uint64_t dst, const uint8_t src, const size_t size ) {
		memset( reinterpret_cast< void* >( dst ), src, size );
	}

	template< typename _Ty >
	__forceinline _Ty read( const uint64_t address ) {
		return *reinterpret_cast< _Ty* >( address );
	}

	template< typename _Ty >
	__forceinline void write( const uint64_t address, _Ty value ) {
		*reinterpret_cast< _Ty* >( address ) = value;
	}
}

class swap_ptr_c {
private:
	uint64_t m_original;
public:
	void setup( uint64_t address, void* replacement ) {
		m_original = memory::read< uint64_t >( address );
		memory::write< void* >( address, replacement );
	}

	template< typename _Ty >
	_Ty original( ) {
		return reinterpret_cast< _Ty >( m_original );
	}
};

class virtual_c {
private:
	uint64_t m_original;
public:
	void setup( uint64_t klass, uint64_t address, void* replacement ) {
		const auto& match = memory::read< uint64_t >( address );
		const auto& table = klass;

		if ( !match
			 || !table )
			return;

		if ( match == reinterpret_cast< uint64_t >( replacement ) )
			return;

		for ( uint64_t i = match; i <= table + o( 0x10000 ); i += 1 ) {
			const auto& ptr = memory::read< uint64_t >( i );

			if ( ptr != match )
				continue;

			memory::write< void* >( i, replacement );
			break;
		}

		m_original = match;
	}

	template< typename _Ty >
	_Ty original( ) {
		return reinterpret_cast< _Ty >( m_original );
	}
};