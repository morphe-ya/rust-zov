#include "classes.hpp"

#include "../sdk.hpp"

#include "../../il2cpp/il2cpp.hpp"
#include "../../../core/core.hpp"

#include "../../../utilities/encrypt/encrypt.hpp"
#include "../../../utilities/memory/memory.hpp"

namespace sdk {
	namespace unity {
		template< typename _Ty >
		_Ty component_c::get( uint64_t type ) {
			using function_t = _Ty( * )( void*, uint64_t );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Component" ), e( "GetComponent" ), -1 } ) ) );

			return function( this, type );
		}

		transform_c* component_c::transform( void* instance ) {
			using function_t = transform_c * ( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Component" ), e( "get_transform" ) } ) ) );

			return function( instance );
		}

		void object_c::dont_destroy_on_load( void* object ) {
			using function_t = void( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Object" ), e( "DontDestroyOnLoad" ), 1 } ) ) );

			return function( object );
		}

		void game_object_c::create( void* object, sdk::unity::string_c* name ) {
			using function_t = void( * )( void*, sdk::unity::string_c* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GameObject" ), e( "Internal_CreateGameObject" ), 2 } ) ) );

			return function( object, name );
		}

		component_c* game_object_c::add_component( uint64_t type ) {
			using function_t = component_c * ( * )( void*, uint64_t );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GameObject" ), e( "AddComponent" ), 1 } ) ) );

			return function( this, type );
		}

		template< typename _Ty >
		_Ty game_object_c::get( uint64_t type ) {
			using function_t = uint64_t( * )( void*, uint64_t );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Component" ), e( "GetComponent" ), 1 } ) ) );

			return memory::read< _Ty >( function( this, type ) );
		}

		asset_bundle_c* asset_bundle_c::load_from_file( sdk::unity::string_c* path ) {
			using function_t = asset_bundle_c * ( * )( sdk::unity::string_c*, uint32_t, uint64_t );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( sdk::unity::find< icall_t >( { e( "UnityEngine.AssetBundle::LoadFromFile_Internal(System.String,System.UInt32,System.UInt64)" ) } ) );

			return function( path, 0, 0 );
		}

		template< typename _Ty >
		_Ty asset_bundle_c::load_asset( sdk::unity::string_c* name, uint64_t type ) {
			using function_t = asset_bundle_c * ( * )( void*, sdk::unity::string_c*, uint64_t );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( sdk::unity::find< icall_t >( { e( "UnityEngine.AssetBundle::LoadAsset_Internal(System.String,System.Type)" ) } ) );

			return function( this, name, type );
		}

		shader_c* shader_c::find( sdk::unity::string_c* name ) {
			using function_t = shader_c * ( * )( sdk::unity::string_c* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Shader" ), e( "Find" ), 1 } ) ) );

			return function( name );
		}

		void material_c::create_with_shader( material_c* self, shader_c* shader ) {
			using function_t = void( * )( material_c*, shader_c* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Material" ), e( "CreateWithShader" ), 2 } ) ) );

			return function( self, shader );
		}

		void material_c::set_int( sdk::unity::string_c* name, int value ) {
			using function_t = void( * )( material_c*, sdk::unity::string_c*, int );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Material" ), e( "SetInt" ), 2 } ) ) );

			return function( this, name, value );
		}

		void material_c::set_pass( int pass ) {
			using function_t = void( * )( material_c*, int );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Material" ), e( "SetPass" ), 1 } ) ) );

			return function( this, pass );
		}

		camera_c* camera_c::main( ) {
			using function_t = camera_c * ( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( sdk::unity::find< icall_t >( { e( "UnityEngine.Camera::get_main()" ) } ) );

			return function( );
		}

		void camera_c::set_aspect( float value ) {
			using function_t = void( * )( void*, float );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Camera" ), e( "set_aspect" ), 1 } ) ) );

			return function( this, value );
		}

		float camera_c::aspect( ) {
			using function_t = float( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Camera" ), e( "get_aspect" ) } ) ) );

			return function( this );
		}

		math::vec3_t camera_c::screen_transform( math::vec3_t pos ) {
			math::mat4x4_t matrix = view_matrix( );

			if ( !matrix.m )
				return { 0, 0, 0 };

			math::vec3_t out{ };
			const auto& temp = matrix.transpose( );

			auto trans = math::vec3_t{ temp[ 3 ][ 0 ], temp[ 3 ][ 1 ], temp[ 3 ][ 2 ] };
			auto up = math::vec3_t{ temp[ 1 ][ 0 ], temp[ 1 ][ 1 ], temp[ 1 ][ 2 ] };
			auto right = math::vec3_t{ temp[ 0 ][ 0 ], temp[ 0 ][ 1 ], temp[ 0 ][ 2 ] };

			float w = trans.dot( pos ) + temp[ 3 ][ 3 ];

			if ( w < 0.001f )
				return { 0, 0, 0 };

			const auto& x = right.dot( pos ) + temp[ 0 ][ 3 ];
			const auto& y = up.dot( pos ) + temp[ 1 ][ 3 ];

			out.x = ( static_cast< float >( screen_c::width( ) ) / 2 ) * ( 1 + x / w );
			out.y = ( static_cast< float >( screen_c::height( ) ) / 2 ) * ( 1 - y / w );
			out.z = 0.0f;

			return out;
		}

		math::mat4x4_t camera_c::view_matrix( ) {
			static camera_c* camera{ };

			if ( !camera )
				camera = camera_c::main( );

			const auto& main = memory::read< uint64_t >( ( uint64_t )camera + 0x10 );

			if ( !main )
				return { };

			const auto& matrix = memory::read< math::mat4x4_t >( main + 0x30C );

			if ( !matrix.m )
				return { };

			return matrix;
		}

		int screen_c::width( ) {
			using function_t = int( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Screen" ), e( "get_width" ) } ) ) );

			return function( );
		}

		int screen_c::height( ) {
			using function_t = int( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Screen" ), e( "get_height" ) } ) ) );

			return function( );
		}

		float screen_c::fps( ) {
			using function_t = float( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Time" ), e( "get_unscaledDeltaTime" ) } ) ) );

			return ( 1.f / function( ) );
		}

		float time_c::time( ) {
			using function_t = float( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Time" ), e( "get_time" ) } ) ) );

			return function( );
		}

		math::vec2_t input_c::scroll_delta( ) {
			using function_t = void( * )( math::vec2_t* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Input" ), e( "get_mouseScrollDelta_Injected" ), 1 } ) ) );

			math::vec2_t out{ };
			function( &out );

			return out;
		}

		bool input_c::is_down( e_key_code key ) {
			using function_t = bool( * )( e_key_code );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Input" ), e( "GetKeyInt" ), 1 } ) ) );

			return function( key );
		}

		math::vec3_t transform_c::forward( ) {
			using function_t = math::vec3_t( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Transform" ), e( "get_forward" ) } ) ) );

			return function( this );
		}

		math::vec3_t transform_c::right( ) {
			using function_t = math::vec3_t( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Transform" ), e( "get_right" ) } ) ) );

			return function( this );
		}

		math::vec3_t transform_c::up( ) {
			using function_t = math::vec3_t( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Transform" ), e( "get_up" ) } ) ) );

			return function( this );
		}

		math::vec3_t transform_c::set_position( math::vec3_t pos ) {
			using function_t = math::vec3_t( * )( void*, math::vec3_t );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Transform" ), e( "set_position" ), 1 } ) ) );

			return function( this, pos );
		}

		math::vec3_t transform_c::position( ) {
			using function_t = math::vec3_t( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Transform" ), e( "get_position" ) } ) ) );

			return function( this );
		}

		event_c* event_c::current( ) {
			using function_t = event_c * ( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Event" ), e( "get_current" ) } ) ) );

			return function( );
		}

		e_event_type event_c::type( ) {
			using function_t = e_event_type( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Event" ), e( "get_type" ) } ) ) );

			return function( this );
		}
	}

	namespace drawing {
		texture2d_c* texture2d_c::white_texture( ) {
			using function_t = texture2d_c * ( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "Texture2D" ), e( "get_whiteTexture" ) } ) ) );

			return function( );
		}

		gui_content_c* gui_content_c::temp( sdk::unity::string_c* str ) {
			using function_t = gui_content_c * ( * )( sdk::unity::string_c* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GUIContent" ), e( "Temp" ), 1, e( "t" ) } ) ) );

			return function( str );
		}

		void gui_style_c::set_font_size( int size ) {
			using function_t = void( * )( void*, int );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GUIStyle" ), e( "set_fontSize" ), 1 } ) ) );

			return function( this, size );
		}

		int gui_style_c::font_size( ) {
			using function_t = int( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GUIStyle" ), e( "get_fontSize" ) } ) ) );

			return function( this );
		}

		math::vec2_t gui_style_c::calc_size( gui_content_c* content ) {
			using function_t = void( * )( void*, gui_content_c*, math::vec2_t& );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( sdk::unity::find< icall_t >( { e( "UnityEngine.GUIStyle::Internal_CalcSize_Injected(UnityEngine.GUIContent,UnityEngine.Vector2&)" ) } ) );

			math::vec2_t out{ };
			function( this, content, out );

			return out;
		}

		gui_style_c* gui_skin_c::label( ) {
			using function_t = gui_style_c * ( * )( void* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GUISkin" ), e( "get_label" ) } ) ) );

			return function( this );
		}

		gui_skin_c* gui_c::skin( ) {
			using function_t = gui_skin_c * ( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GUI" ), e( "get_skin" ) } ) ) );

			return function( );
		}

		void gui_c::set_color( sdk::unity::color_c color ) {
			using function_t = void( * )( sdk::unity::color_c );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GUI" ), e( "set_color" ), 1 } ) ) );

			return function( color );
		}

		sdk::unity::color_c gui_c::color( ) {
			using function_t = sdk::unity::color_c( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GUI" ), e( "get_color" ) } ) ) );

			return function( );
		}

		void gui_c::draw_texture( sdk::unity::rect_t pos, texture2d_c* texture ) {
			using function_t = void( * )( sdk::unity::rect_t, texture2d_c* );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GUI" ), e( "DrawTexture" ), 2 } ) ) );

			return function( pos, texture );
		}

		void gui_c::draw_texture2( sdk::unity::rect_t pos, texture2d_c* texture, int scale, bool blend, float aspect, sdk::unity::color_c color, float border, float radius ) {
			using function_t = void( * )( sdk::unity::rect_t, texture2d_c*, int, bool, float, sdk::unity::color_c, float, float );
			static function_t function{ };

			if ( !function )
				/*  @todo: update
				*   public static void DrawTexture(Rect position, Texture image, ScaleMode scaleMode, bool alphaBlend, float imageAspect, Color color, float borderWidth, float borderRadius)
				*/
				function = reinterpret_cast< function_t >( game_assembly + o( 0xA10B8B0 ) );

			return function( pos, texture, scale, blend, aspect, color, border, radius );
		}

		void gui_c::draw_texture3( sdk::unity::rect_t pos, texture2d_c* texture, int scale, bool blend, float aspect, sdk::unity::color_c color, math::vec4_t border, math::vec4_t radius, bool smooth ) {
			using function_t = void( * )( sdk::unity::rect_t, texture2d_c*, int, bool, float, sdk::unity::color_c, math::vec4_t, math::vec4_t, bool );
			static function_t function{ };

			if ( !function )
				/*  @todo: update
				*   internal static void DrawTexture(Rect position, Texture image, ScaleMode scaleMode, bool alphaBlend, float imageAspect, Color color, Vector4 borderWidths, Vector4 borderRadiuses, bool drawSmoothCorners)
				*/
				function = reinterpret_cast< function_t >( game_assembly + o( 0xA10BFF0 ) );

			return function( pos, texture, scale, blend, aspect, color, border, radius, smooth );
		}

		void gui_c::label( sdk::unity::rect_t pos, gui_content_c* content, gui_style_c* style ) {
			using function_t = void( * )( sdk::unity::rect_t, gui_content_c*, gui_style_c* );
			static function_t function{ };

			if ( !function )
				/*  @todo: update
				*   private static void DoLabel(Rect position, GUIContent content, GUIStyle style)
				*/
				function = reinterpret_cast< function_t >( game_assembly + o( 0xA10FFF0 ) );

			return function( pos, content, style );
		}

	}

	namespace gl {
		void gl_c::push( ) {
			using function_t = void( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GL" ), e( "PushMatrix" ) } ) ) );

			return function( );
		}

		void gl_c::pop( ) {
			using function_t = void( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GL" ), e( "PopMatrix" ) } ) ) );

			return function( );
		}

		void gl_c::begin( e_primitive_mode mode ) {
			using function_t = void( * )( e_primitive_mode );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GL" ), e( "Begin" ), 1 } ) ) );

			return function( mode );
		}

		void gl_c::end( ) {
			using function_t = void( * )( );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GL" ), e( "End" ) } ) ) );

			return function( );
		}

		void gl_c::color( unity::color_c color ) {
			using function_t = void( * )( unity::color_c );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GL" ), e( "Color" ), 1 } ) ) );

			return function( color );
		}

		void gl_c::vertex3( float x, float y, float z ) {
			using function_t = void( * )( float, float, float );
			static function_t function{ };

			if ( !function )
				function = reinterpret_cast< function_t >( memory::read< uint64_t >( sdk::unity::find< method_t >( { e( "UnityEngine" ), e( "GL" ), e( "Vertex3" ), 3 } ) ) );

			return function( x, y, z );
		}

		void start( e_primitive_mode mode ) {
			gl_c::push( );
			gl_c::begin( mode );
		}

		void end( ) {
			gl_c::end( );
			gl_c::pop( );
		}
	}

	namespace math {
		float vec2_t::length( ) {
			return sqrtf( ( x * x ) + ( y * y ) );
		}

		bool vec3_t::empty( ) {
			return x == 0
				&& y == 0
				&& z == 0;
		}

		float vec3_t::length( ) {
			return sqrtf( ( x * x ) + ( y * y ) + ( z * z ) );
		}

		float vec3_t::length2d( ) {
			return sqrtf( ( x * x ) + ( z * z ) );
		}

		template< typename _Ty >
		_Ty vec3_t::remainder( _Ty value, _Ty min, _Ty max ) {
			while ( value > max )
				value -= max * 2;

			while ( value < min )
				value += max * 2;

			return value;
		}

		vec3_t vec3_t::clamp( ) {
			const auto& yaw_limit = static_cast< float >( 180 );
			const auto& pitch_limit = static_cast< float >( 90 );

			y = remainder( y, -yaw_limit, yaw_limit );
			x = remainder( x, -pitch_limit, pitch_limit );

			if ( x != x )
				x = 0;
			if ( y != y )
				y = 0;
			if ( z != z )
				z = 0;

			return *this;
		}

		float vec3_t::dot( const vec3_t& vector ) {
			return x * vector.x + y * vector.y + z * vector.z;
		}

		float vec3_t::distance3d( const vec3_t& vector ) {
			return sqrtf( ( x - vector.x ) * ( x - vector.x ) + ( y - vector.y ) * ( y - vector.y ) + ( z - vector.z ) * ( z - vector.z ) );
		}

		float vec3_t::distance( const vec3_t& vector ) {
			return sqrtf( ( x - vector.x ) * ( x - vector.x ) + ( y - vector.y ) * ( y - vector.y ) + ( z - vector.z ) * ( z - vector.z ) );
		}

		vec3_t vec3_t::normalized( ) {
			float len = length( );
			return vec3_t( x / len, y / len, z / len );
		}

		float vec4_t::dot( const vec4_t& vector ) {
			return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
		}

		float vec4_t::distance( const vec4_t& vector ) {
			return sqrtf( ( x - vector.x ) * ( x - vector.x ) + ( y - vector.y ) * ( y - vector.y ) + ( z - vector.z ) * ( z - vector.z ) + ( w - vector.w ) * ( w - vector.w ) );
		}

		mat4x4_t mat4x4_t::transpose( ) {
			mat4x4_t m;

			for ( int i{ }; i < 4; ++i )
				for ( int j{ }; j < 4; ++j )
					m.m[ i ][ j ] = this->m[ j ][ i ];

			return m;
		}

		bool mat4x4_t::empty( ) {
			if ( !m[ 3 ][ 0 ]
				 && !m[ 3 ][ 1 ]
				 && !m[ 3 ][ 2 ]
				 && !m[ 2 ][ 1 ]
				 && !m[ 2 ][ 0 ]
				 && !m[ 2 ][ 2 ] )
				return true;

			return false;
		}
	}

	uint64_t base_networkable_c::decrypt( uint64_t address ) {
		uint64_t rax = memory::read< uint64_t >( address + 0x18 );
		uint64_t* rdx = &rax;
		uint32_t r8d = 0x2;
		uint32_t eax, ecx, edx;

		do {
			eax = *( uint32_t* )( rdx );
			rdx = ( uint64_t* )( ( uint8_t* )rdx + 0x4 );
			eax = eax + 0x84B02EEE;
			ecx = eax;
			eax = eax << 0xD;
			ecx = ecx >> 0x13;
			ecx = ecx | eax;
			ecx = ecx - 0x2F1224FF;
			*( ( uint32_t* )rdx - 1 ) = ecx;
			--r8d;
		} while ( r8d );

		return il2cpp::gchandle_get_target( rax );
	}

	uint64_t base_networkable_c::decrypt_list( uint64_t address ) {
		uint64_t rax = memory::read< uint64_t >( address + 0x18 );
		uint64_t* rdx = &rax;
		uint32_t r8d = 0x2;
		uint32_t eax, ecx, edx;

		do {
			ecx = *( uint32_t* )( rdx );
			eax = *( uint32_t* )( rdx );
			rdx = ( uint64_t* )( ( uint8_t* )rdx + 0x4 );
			ecx = ecx >> 0xA;
			eax = eax << 0x16;
			ecx = ecx | eax;
			ecx = ecx - 0x49064304;
			ecx = ecx ^ 0xFA11D865;
			*( ( uint32_t* )rdx - 1 ) = ecx;
			--r8d;
		} while ( r8d );

		return il2cpp::gchandle_get_target( rax );
	}

	sdk::unity::transform_c* base_player_c::get_bone_transform( int id ) {
		const auto& model = memory::read< uint64_t >( ( uint64_t )this + 0xC8 );

		if ( !memory::is_valid( model ) )
			return 0;

		const auto& transforms = memory::read< uint64_t >( model + 0x50 );

		if ( !memory::is_valid( transforms ) )
			return 0;

		const auto& bone = memory::read< sdk::unity::transform_c* >( transforms + 0x20 + id * 0x8 );

		if ( !memory::is_valid( bone ) )
			return 0;

		return bone;
	}

	bool base_player_c::is_sleeping( ) {
		const auto& flags = memory::read< int >( ( uint64_t )this + 0x558 );
		return flags & 16;
	}

	bool base_player_c::is_dead( ) {
		return memory::read< int >( ( uint64_t )this + 0x234 ) == 1;
	}
}