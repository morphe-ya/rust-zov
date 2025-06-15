#pragma once

#include "../../../includes/includes.hpp"
#include "../classes/classes.hpp"

namespace render {
	struct color_t {
		float r, g, b, a;

		color_t( int r, int g, int b ) : r( r / 255.f ), g( g / 255.f ), b( b / 255.f ), a( 1.f ) { }
		color_t( int r, int g, int b, int a ) : r( r / 255.f ), g( g / 255.f ), b( b / 255.f ), a( a / 255.f ) { }
		color_t( float r, float g, float b, float a ) : r( r ), g( g ), b( b ), a( a ) { }
		color_t( float r, float g, float b ) : r( r ), g( g ), b( b ), a( 1.f ) { }

		color_t( ) : r( 0.f ), g( 0.f ), b( 0.f ), a( 0.f ) { }
	};

	inline sdk::drawing::texture2d_c* texture{ };
	inline sdk::unity::material_c* material{ };

	void draw_multi_color_filled_rect( sdk::math::vec2_t, sdk::math::vec2_t, color_t, color_t, color_t, color_t );
	void draw_filled_rect( sdk::math::vec2_t, sdk::math::vec2_t, color_t, float = 0.f );

	sdk::math::vec2_t calc_text_size( const char*, int = 14 );

	void draw_rect( sdk::math::vec2_t, sdk::math::vec2_t, color_t, float = 0.f );
	void draw_text( sdk::math::vec2_t, color_t, const char*, int = 14 );
}