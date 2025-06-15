#pragma once

#include "../../includes/includes.hpp"
#include <type_traits>

namespace sdk {
	namespace unity {
		namespace defines {
			typedef struct _method_t {
				const char* m_space;
				const char* m_name;

				const char* m_method;
				int32_t m_count{ };

				const char* m_arg{ };
				int32_t m_selected_arg{ };
			} method_t, * pmethod_t;

			typedef struct _klass_t {
				const char* m_space;
				const char* m_name;
			} klass_t, * pklass_t;

			typedef struct _field_t {
				const char* m_space;
				const char* m_name;

				const char* m_field;
				bool m_offset{ true };
			} field_t, * pfield_t;

			typedef struct _value_t {
				const char* m_space;
				const char* m_name;

				const char* m_field;
			} value_t, * pvalue_t;

			typedef struct _icall_t {
				const char* m_name;
			} icall_t, * picall_t;

			typedef struct _type_t {
				const char* m_space;
				const char* m_name;

				char pad_0x0012[ 0x0012 ];
			} type_t, * ptype_t;
		}

		uint64_t new_string( const char* );

		uint64_t method( const char*, const char*, int, const char* = "", int = 0, const char* = "" );
		uint64_t field( const char*, const char*, bool = true, const char* = "" );
		uint64_t value( const char*, const char*, const char* = "" );
		uint64_t klass( const char*, const char* = "" );
		uint64_t icall( const char* );
		uint64_t type( const char*, const char* = "" );

		template< typename _Ty >
		__forceinline uint64_t find( _Ty data ) {
			if ( std::is_same< _Ty, defines::method_t >( ) ) {
				const auto& method = *reinterpret_cast< defines::method_t* >( &data );
				return sdk::unity::method( method.m_name, method.m_method, method.m_count, method.m_arg, method.m_selected_arg, method.m_space );

			} else if ( std::is_same< _Ty, defines::klass_t >( ) ) {
				const auto& klass = *reinterpret_cast< defines::klass_t* >( &data );
				return sdk::unity::klass( klass.m_name, klass.m_space );

			} else if ( std::is_same< _Ty, defines::field_t >( ) ) {
				const auto& field = *reinterpret_cast< defines::field_t* >( &data );
				return sdk::unity::field( field.m_name, field.m_field, field.m_offset, field.m_space );

			} else if ( std::is_same< _Ty, defines::value_t >( ) ) {
				const auto& value = *reinterpret_cast< defines::value_t* >( &data );
				return sdk::unity::value( value.m_name, value.m_field, value.m_space );

			} else if ( std::is_same< _Ty, defines::icall_t >( ) ) {
				const auto& icall = *reinterpret_cast< defines::icall_t* >( &data );
				return sdk::unity::icall( icall.m_name );

			} else if ( std::is_same< _Ty, defines::type_t >( ) ) {
				const auto& type = *reinterpret_cast< defines::type_t* >( &data );
				return sdk::unity::type( type.m_name );
			}
			
			return 0;
		}

		class string_c {
		public:
			char pad_0x0010[ 0x0010 ];

			uint32_t m_size;
			wchar_t m_buffer[ 128 + 1 ];

			static string_c* make( const char* str ) {
				return reinterpret_cast< string_c* >( new_string( str ) );
			}
		};
	}
}

using namespace sdk::unity::defines;