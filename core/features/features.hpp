#pragma once

#include "../../includes/includes.hpp"
#include "../sdk/classes/classes.hpp"

namespace features {
	inline sdk::base_player_c* local_player{ };

	namespace visuals {
		void draw_crosshair( );
		void draw_watermark( );

		void draw_screen( );
		void draw_esp( );
	}

	namespace misc {
		void main( );
	}

	void main( );
}