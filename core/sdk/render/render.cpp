#include "render.hpp"

#include "../../../utilities/encrypt/encrypt.hpp"
#include "../../../utilities/memory/memory.hpp"

#include "../../il2cpp/il2cpp.hpp"

namespace render {
	void draw_multi_color_filled_rect( sdk::math::vec2_t pos, sdk::math::vec2_t size, color_t first, color_t second, color_t third, color_t fourth ) {
		if ( !material ) {
			const auto& klass = sdk::unity::find< klass_t >( { e( "UnityEngine" ), e( "Material" ) } );

			if ( !memory::is_valid( klass ) )
				return;

			const auto& shader = sdk::unity::shader_c::find( sdk::unity::string_c::make( e( "Hidden/Internal-Colored" ) ) );

			if ( !memory::is_valid( klass ) )
				return;

			material = reinterpret_cast< sdk::unity::material_c* >( il2cpp::object_new( klass ) );

			if ( !memory::is_valid( material ) )
				return;

			sdk::unity::material_c::create_with_shader( material, shader );

			material->set_int( sdk::unity::string_c::make( e( "_SrcBlend" ) ), 5 );
			material->set_int( sdk::unity::string_c::make( e( "_DstBlend" ) ), 10 );
			material->set_int( sdk::unity::string_c::make( e( "_Cull" ) ), 0 );
			material->set_int( sdk::unity::string_c::make( e( "_ZWrite" ) ), 0 );

			sdk::unity::object_c::dont_destroy_on_load( material );
		}

		material->set_pass( 0 );
		sdk::gl::start( sdk::gl::e_primitive_mode::quads );

		sdk::gl::gl_c::color( *reinterpret_cast< sdk::unity::color_c* >( &first ) );
		sdk::gl::gl_c::vertex3( pos.x, pos.y, 0 );

		sdk::gl::gl_c::color( *reinterpret_cast< sdk::unity::color_c* >( &second ) );
		sdk::gl::gl_c::vertex3( pos.x + size.x, pos.y, 0 );

		sdk::gl::gl_c::color( *reinterpret_cast< sdk::unity::color_c* >( &third ) );
		sdk::gl::gl_c::vertex3( pos.x + size.x, pos.y + size.y, 0 );

		sdk::gl::gl_c::color( *reinterpret_cast< sdk::unity::color_c* >( &fourth ) );
		sdk::gl::gl_c::vertex3( pos.x, pos.y + size.y, 0 );

		sdk::gl::gl_c::color( *reinterpret_cast< sdk::unity::color_c* >( &first ) );
		sdk::gl::gl_c::vertex3( pos.x, pos.y, 0 );

		sdk::gl::end( );
	}

	void draw_filled_rect( sdk::math::vec2_t pos, sdk::math::vec2_t size, color_t color, float rounding ) {
		if ( !texture )
			texture = sdk::drawing::texture2d_c::white_texture( );

		sdk::drawing::gui_c::draw_texture3( { pos.x, pos.y, size.x, size.y }, texture, 0, false, 0.f, *reinterpret_cast< sdk::unity::color_c* >( &color ), { 0.f, 0.f, 0.f, 0.f }, { rounding, rounding, rounding, rounding }, true );
	}

	sdk::math::vec2_t calc_text_size( const char* text, int font ) {
		const auto& string = sdk::unity::string_c::make( text );
		const auto& content = sdk::drawing::gui_content_c::temp( string );

		const auto& skin = sdk::drawing::gui_c::skin( );
		const auto& label = skin->label( );

		label->set_font_size( font );
		return label->calc_size( content );
	}

	void draw_rect( sdk::math::vec2_t pos, sdk::math::vec2_t size, color_t color, float rounding ) {
		if ( !texture )
			texture = sdk::drawing::texture2d_c::white_texture( );

		sdk::drawing::gui_c::draw_texture2( { pos.x, pos.y, size.x, size.y }, texture, 0, false, 0.f, *reinterpret_cast< sdk::unity::color_c* >( &color ), 2.f, rounding );
	}

	void draw_text( sdk::math::vec2_t pos, color_t color, const char* text, int font ) {
		const auto& string = sdk::unity::string_c::make( text );
		const auto& content = sdk::drawing::gui_content_c::temp( string );

		const auto& skin = sdk::drawing::gui_c::skin( );
		const auto& label = skin->label( );

		label->set_font_size( font );
		const auto& size = label->calc_size( content );

		sdk::drawing::gui_c::set_color( *reinterpret_cast< sdk::unity::color_c* >( &color ) );
		sdk::drawing::gui_c::label( { pos.x, pos.y, size.x, size.y }, content, label );
	}
}