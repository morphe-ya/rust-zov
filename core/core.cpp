#include "core.hpp"

#include "hooks/hooks.hpp"

#include "../utilities/process/process.hpp"
#include "../utilities/memory/memory.hpp"
#include "../utilities/hash/hash.hpp"

namespace core {
	void initialize( ) {
		game_assembly = process::get_module_base( HASH( "gameassembly" ) );
		unity_player = process::get_module_base( HASH( "unityplayer" ) );

		if ( !memory::is_valid( game_assembly )
			 || !memory::is_valid( unity_player ) )
			return;

		hooks::initialize( );
	}
}