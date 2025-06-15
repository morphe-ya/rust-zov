#include "features.hpp"

#include "../../utilities/encrypt/encrypt.hpp"
#include "../../utilities/memory/memory.hpp"

#include "../sdk/classes/classes.hpp"
#include "../sdk/render/render.hpp"

#include "../il2cpp/il2cpp.hpp"
#include "../../core/core.hpp"

namespace features {
	namespace visuals {
		void draw_crosshair( ) {
			const auto& width = sdk::unity::screen_c::width( );
			const auto& height = sdk::unity::screen_c::height( );

			const auto& screen = sdk::math::vec2_t{ width / 2.f, height / 2.f };

			render::draw_filled_rect( { screen.x - 5.f, screen.y - 1.f }, { 11.f, 3.f }, { 0, 0, 0, 255 } );
			render::draw_filled_rect( { screen.x - 1.f, screen.y - 5.f }, { 3.f, 11.f }, { 0, 0, 0, 255 } );
			render::draw_filled_rect( { screen.x - 4.f, screen.y }, { 9.f, 1.f }, { 255, 0, 0, 255 } );
			render::draw_filled_rect( { screen.x, screen.y - 4.f }, { 1.f, 9.f }, { 255, 0, 0, 255 } );
		}

		void draw_watermark( ) {
			char buf[ 256 ]{ };
			sprintf( buf, e( "Rust | %s" ), e( __DATE__ ) );

			render::draw_filled_rect( { 3.f, 6.f }, { 129.f, 22.f }, { 0, 0, 0, 90 } );
			render::draw_filled_rect( { 3.f, 5.f }, { 129.f, 1.f }, { 255, 255, 255 } );

			render::draw_text( { 7.f, 5.f }, { 255.f, 255.f, 255.f }, buf );
		}

		void draw_screen( ) {
			draw_crosshair( );
			draw_watermark( );
		}

		struct box_t {
			sdk::math::vec2_t pos;
			sdk::math::vec2_t size;
		};

		void draw_player( sdk::base_player_c* player ) {
			const auto& position = sdk::unity::component_c::transform( player )->position( );

			if ( !position.x
				 && !position.y
				 && !position.z )
				return;

			auto base_pos = sdk::unity::camera_c::screen_transform( position );
			auto head_pos = sdk::unity::camera_c::screen_transform( player->get_bone_transform( 48 )->position( ) );

			auto standing_pos = sdk::unity::camera_c::screen_transform( position + sdk::math::vec3_t{ 0, 1.9f, 0, } );

			if ( base_pos.empty( ) || head_pos.empty( ) || standing_pos.empty( ) )
				return;

			const auto& box_width = ( base_pos.y - standing_pos.y ) * 0.45f;
			const auto& box_height = ( base_pos.y - head_pos.y ) * 1.15f;

			box_t box{ };

			box.pos = { base_pos.x - box_width * 0.5f, base_pos.y - box_height };
			box.size = { box_width, box_height };

			render::draw_rect( { box.pos.x - 1.f, box.pos.y - 1.f }, { box.size.x + 2.f, box.size.y + 2.f }, { 0, 0, 0 }, 0.f );
			render::draw_rect( { box.pos.x, box.pos.y }, { box.size.x, box.size.y }, { 255, 255, 255 } );
		}

		void draw_esp( ) {
			const auto& base_networkable = memory::read< uint64_t >( game_assembly + 0xBE7FB88 );

			if ( !memory::is_valid( base_networkable ) )
				return;

			const auto& static_fields = memory::read< uint64_t >( base_networkable + 0xB8 );

			if ( !memory::is_valid( static_fields ) )
				return;

			const auto& unk0 = memory::read< uint64_t >( static_fields + 0x30 );

			if ( !memory::is_valid( static_fields ) )
				return;

			const auto& pointer = sdk::base_networkable_c::decrypt( unk0 );

			if ( !memory::is_valid( pointer ) )
				return;

			const auto& unk1 = memory::read< uint64_t >( pointer + 0x10 );

			if ( !memory::is_valid( unk1 ) )
				return;

			const auto& wrapper = sdk::base_networkable_c::decrypt_list( unk1 );

			if ( !memory::is_valid( wrapper ) )
				return;

			const auto& entities = memory::read< uint64_t >( wrapper + 0x18 );

			if ( !memory::is_valid( entities ) )
				return;

			const auto& buffer = memory::read< uint64_t >( entities + 0x10 );
			const auto& count = memory::read< uint32_t >( entities + 0x18 );

			for ( int i{ }; i < count; ++i ) {
				const auto& entity = memory::read< uint64_t >( buffer + 0x20 + ( i * 0x8 ) );

				if ( !memory::is_valid( entity ) )
					continue;

				const auto& base_object = memory::read< uint64_t >( entity + 0x10 );

				if ( !base_object 
					 || base_object <= 100000 )
					continue;

				const auto& object = memory::read< uint64_t >( base_object + 0x30 );

				if ( !object 
					 || object <= 100000 )
					continue;

				const auto& tag = memory::read< uint16_t >( object + 0x54 );

				if ( tag == 0
					 || tag != 6 )
					continue;

				if ( i == 0 )
					local_player = reinterpret_cast< sdk::base_player_c* >( entity );

				if ( entity == ( uint64_t )local_player )
					continue;

				const auto& player = reinterpret_cast< sdk::base_player_c* >( entity );

				if ( player->is_dead( ) )
					continue;

				draw_player( player );
			}
		}
	}

	void main( ) {
		visuals::draw_screen( );
		visuals::draw_esp( );
	}
}