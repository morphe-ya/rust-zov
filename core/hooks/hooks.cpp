#include "hooks.hpp"

#include "../il2cpp/il2cpp.hpp"
#include "../features/features.hpp"

#include "../sdk/sdk.hpp"
#include "../sdk/classes/classes.hpp"
#include "../sdk/render/render.hpp"

#include "../../utilities/encrypt/encrypt.hpp"

namespace hooks {
	namespace impl {
		void hk_performance_ui_update( void* instance ) {
			if ( !initialized ) {
				const auto& klass = sdk::unity::find< klass_t >( { e( "UnityEngine" ), e( "GameObject" ) } );

				if ( !memory::is_valid( klass ) )
					return o_performance_ui_update.original< performance_ui_update_t >( )( instance );

				const auto& game_object = reinterpret_cast< sdk::unity::game_object_c* >( il2cpp::object_new( klass ) );

				if ( !memory::is_valid( game_object ) )
					return o_performance_ui_update.original< performance_ui_update_t >( )( instance );

				sdk::unity::game_object_c::create( game_object, sdk::unity::string_c::make( "" ) );

				game_object->add_component( sdk::unity::find< type_t >( { "", e( "DevControls" ) } ) );
				sdk::unity::object_c::dont_destroy_on_load( game_object );

				initialized = true;
			}

			return o_performance_ui_update.original< performance_ui_update_t >( )( instance );
		}

		void hk_on_gui( void* instance ) {
			const auto& event = sdk::unity::event_c::current( );

			if ( !memory::is_valid( event ) )
				return;

			const auto& type = event->type( );

			if ( type != sdk::unity::e_event_type::repaint )
				return;

			features::main( );

			return;
		}
	}

	void initialize( ) {
		impl::o_performance_ui_update.setup( sdk::unity::find< method_t >( { e( "Facepunch" ), e( "PerformanceUI" ), e( "Update" ) } ), &impl::hk_performance_ui_update );
		impl::o_on_gui.setup( sdk::unity::find< method_t >( { "", e( "DevControls" ), e( "OnGUI" ) } ), &impl::hk_on_gui );
	}
}