#pragma once

#include "../../includes/includes.hpp"

#include "../../utilities/memory/memory.hpp"

namespace hooks {
	namespace impl {
		static bool initialized{ };

		using performance_ui_update_t = void( * )( void* );
		inline swap_ptr_c o_performance_ui_update{ };

		using on_gui_t = void( * )( void* );
		inline swap_ptr_c o_on_gui{ };

		void hk_performance_ui_update( void* );
		void hk_on_gui( void* );
	}

	void initialize( );
}