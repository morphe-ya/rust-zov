#pragma once

#include "../../../includes/includes.hpp"
#include "../sdk.hpp"

namespace sdk {
	namespace math {
		struct vec2_t {
			float x, y;

			vec2_t( ) { }
			vec2_t( float x, float y ) : x( x ), y( y ) { }

			vec2_t operator-( const vec2_t& vector ) const {
				return vec2_t( x - vector.x, y - vector.y );
			}

			vec2_t& operator+=( const vec2_t& vector ) {
				x += vector.x;
				y += vector.y;

				return *this;
			}
			vec2_t& operator-=( const vec2_t& vector ) {
				x -= vector.x;
				y -= vector.y;

				return *this;
			}

			float length( );
		};

		struct vec3_t {
			float x;
			float y;
			float z;

			vec3_t( ) { }

			vec3_t( float x, float y, float z )
				: x( x ), y( y ), z( z ) { }

			bool empty( );

			float length( );
			float length2d( );

			template< typename _Ty >
			_Ty remainder( _Ty, _Ty, _Ty );

			vec3_t clamp( );
			float dot( const vec3_t& );

			float distance3d( const vec3_t& );
			float distance( const vec3_t& );

			vec3_t normalized( );

			vec3_t& operator+=( const vec3_t& vector ) {
				x += vector.x;
				y += vector.y;
				z += vector.z;

				return *this;
			}

			vec3_t& operator-=( const vec3_t& vector ) {
				x -= vector.x;
				y -= vector.y;
				z -= vector.z;

				return *this;
			}

			vec3_t& operator*=( float number ) {
				x *= number;
				y *= number;
				z *= number;

				return *this;
			}

			vec3_t& operator/=( float number ) {
				x /= number;
				y /= number;
				z /= number;

				return *this;
			}

			bool operator==( const vec3_t& vector ) const {
				return x == vector.x && y == vector.y && z == vector.z;
			}

			bool operator!=( const vec3_t& vector ) const {
				return x != vector.x || y != vector.y || z != vector.z;
			}

			vec3_t operator+( const vec3_t& vector ) const {
				return vec3_t( x + vector.x, y + vector.y, z + vector.z );
			}

			vec3_t operator-( const vec3_t& vector ) const {
				return vec3_t( x - vector.x, y - vector.y, z - vector.z );
			}

			vec3_t operator-( ) const {
				return vec3_t( -x, -y, -z );
			}

			vec3_t operator*( float number ) const {
				return vec3_t( x * number, y * number, z * number );
			}

			vec3_t operator/( float number ) const {
				return vec3_t( x / number, y / number, z / number );
			}
		};

		class vec4_t {
		public:
			float x;
			float y;
			float z;
			float w;

			vec4_t( ) { }
			vec4_t( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) { }

			float dot( const vec4_t& );
			float distance( const vec4_t& );

			bool operator==( const vec4_t& vector ) const {
				return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
			}

			bool operator!=( const vec4_t& vector ) const {
				return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
			}

			vec4_t operator+( const vec4_t& vector ) const {
				return vec4_t( x + vector.x, y + vector.y, z + vector.z, w + vector.w );
			}

			vec4_t operator-( const vec4_t& vector ) const {
				return vec4_t( x - vector.x, y - vector.y, z - vector.z, w - vector.w );
			}

			vec4_t operator-( ) const {
				return vec4_t( -x, -y, -z, -w );
			}

			vec4_t operator*( float number ) const {
				return vec4_t( x * number, y * number, z * number, w * number );
			}

			vec4_t operator/( float number ) const {
				return vec4_t( x / number, y / number, z / number, w / number );
			}

			vec4_t& operator+=( const vec4_t& vector ) {
				x += vector.x;
				y += vector.y;
				z += vector.z;
				w += vector.w;
				return *this;
			}

			vec4_t& operator-=( const vec4_t& vector ) {
				x -= vector.x;
				y -= vector.y;
				z -= vector.z;
				w -= vector.w;
				return *this;
			}

			vec4_t& operator*=( float number ) {
				x *= number;
				y *= number;
				z *= number;
				w *= number;
				return *this;
			}

			vec4_t& operator/=( float number ) {
				x /= number;
				y /= number;
				z /= number;
				w /= number;
				return *this;
			}
		};

		struct mat4x4_t {
			mat4x4_t( )
				: m{ { 0, 0, 0, 0 },
					 { 0, 0, 0, 0 },
					 { 0, 0, 0, 0 },
					 { 0, 0, 0, 0 } } { }

			mat4x4_t( const mat4x4_t& ) = default;

			mat4x4_t transpose( );
			bool empty( );

			vec3_t operator*( const vec3_t& vec ) {
				mat4x4_t m{ };

				m[ 3 ][ 0 ] = vec.x;
				m[ 3 ][ 1 ] = vec.y;
				m[ 3 ][ 2 ] = vec.z;

				m[ 0 ][ 0 ] = 1;
				m[ 1 ][ 1 ] = 1;
				m[ 2 ][ 2 ] = 1;


				m[ 0 ][ 3 ] = 0.0f;
				m[ 1 ][ 3 ] = 0.0f;
				m[ 2 ][ 3 ] = 0.0f;
				m[ 3 ][ 3 ] = 1.0f;

				const auto& result = m * ( *this );
				return vec3_t{ result[ 3 ][ 0 ], result[ 3 ][ 1 ], result[ 3 ][ 2 ] };
			}

			mat4x4_t operator*( const mat4x4_t& _m2 ) {
				const auto& _m = *this;

				mat4x4_t out{ };

				out[ 0 ][ 0 ] = _m[ 0 ][ 0 ] * _m2[ 0 ][ 0 ] + _m[ 0 ][ 1 ] * _m2[ 1 ][ 0 ] + _m[ 0 ][ 2 ] * _m2[ 2 ][ 0 ] + _m[ 0 ][ 3 ] * _m2[ 3 ][ 0 ];
				out[ 0 ][ 1 ] = _m[ 0 ][ 0 ] * _m2[ 0 ][ 1 ] + _m[ 0 ][ 1 ] * _m2[ 1 ][ 1 ] + _m[ 0 ][ 2 ] * _m2[ 2 ][ 1 ] + _m[ 0 ][ 3 ] * _m2[ 3 ][ 1 ];
				out[ 0 ][ 2 ] = _m[ 0 ][ 0 ] * _m2[ 0 ][ 2 ] + _m[ 0 ][ 1 ] * _m2[ 1 ][ 2 ] + _m[ 0 ][ 2 ] * _m2[ 2 ][ 2 ] + _m[ 0 ][ 3 ] * _m2[ 3 ][ 2 ];
				out[ 0 ][ 3 ] = _m[ 0 ][ 0 ] * _m2[ 0 ][ 3 ] + _m[ 0 ][ 1 ] * _m2[ 1 ][ 3 ] + _m[ 0 ][ 2 ] * _m2[ 2 ][ 3 ] + _m[ 0 ][ 3 ] * _m2[ 3 ][ 3 ];
				out[ 1 ][ 0 ] = _m[ 1 ][ 0 ] * _m2[ 0 ][ 0 ] + _m[ 1 ][ 1 ] * _m2[ 1 ][ 0 ] + _m[ 1 ][ 2 ] * _m2[ 2 ][ 0 ] + _m[ 1 ][ 3 ] * _m2[ 3 ][ 0 ];
				out[ 1 ][ 1 ] = _m[ 1 ][ 0 ] * _m2[ 0 ][ 1 ] + _m[ 1 ][ 1 ] * _m2[ 1 ][ 1 ] + _m[ 1 ][ 2 ] * _m2[ 2 ][ 1 ] + _m[ 1 ][ 3 ] * _m2[ 3 ][ 1 ];
				out[ 1 ][ 2 ] = _m[ 1 ][ 0 ] * _m2[ 0 ][ 2 ] + _m[ 1 ][ 1 ] * _m2[ 1 ][ 2 ] + _m[ 1 ][ 2 ] * _m2[ 2 ][ 2 ] + _m[ 1 ][ 3 ] * _m2[ 3 ][ 2 ];
				out[ 1 ][ 3 ] = _m[ 1 ][ 0 ] * _m2[ 0 ][ 3 ] + _m[ 1 ][ 1 ] * _m2[ 1 ][ 3 ] + _m[ 1 ][ 2 ] * _m2[ 2 ][ 3 ] + _m[ 1 ][ 3 ] * _m2[ 3 ][ 3 ];
				out[ 2 ][ 0 ] = _m[ 2 ][ 0 ] * _m2[ 0 ][ 0 ] + _m[ 2 ][ 1 ] * _m2[ 1 ][ 0 ] + _m[ 2 ][ 2 ] * _m2[ 2 ][ 0 ] + _m[ 2 ][ 3 ] * _m2[ 3 ][ 0 ];
				out[ 2 ][ 1 ] = _m[ 2 ][ 0 ] * _m2[ 0 ][ 1 ] + _m[ 2 ][ 1 ] * _m2[ 1 ][ 1 ] + _m[ 2 ][ 2 ] * _m2[ 2 ][ 1 ] + _m[ 2 ][ 3 ] * _m2[ 3 ][ 1 ];
				out[ 2 ][ 2 ] = _m[ 2 ][ 0 ] * _m2[ 0 ][ 2 ] + _m[ 2 ][ 1 ] * _m2[ 1 ][ 2 ] + _m[ 2 ][ 2 ] * _m2[ 2 ][ 2 ] + _m[ 2 ][ 3 ] * _m2[ 3 ][ 2 ];
				out[ 2 ][ 3 ] = _m[ 2 ][ 0 ] * _m2[ 0 ][ 3 ] + _m[ 2 ][ 1 ] * _m2[ 1 ][ 3 ] + _m[ 2 ][ 2 ] * _m2[ 2 ][ 3 ] + _m[ 2 ][ 3 ] * _m2[ 3 ][ 3 ];
				out[ 3 ][ 0 ] = _m[ 3 ][ 0 ] * _m2[ 0 ][ 0 ] + _m[ 3 ][ 1 ] * _m2[ 1 ][ 0 ] + _m[ 3 ][ 2 ] * _m2[ 2 ][ 0 ] + _m[ 3 ][ 3 ] * _m2[ 3 ][ 0 ];
				out[ 3 ][ 1 ] = _m[ 3 ][ 0 ] * _m2[ 0 ][ 1 ] + _m[ 3 ][ 1 ] * _m2[ 1 ][ 1 ] + _m[ 3 ][ 2 ] * _m2[ 2 ][ 1 ] + _m[ 3 ][ 3 ] * _m2[ 3 ][ 1 ];
				out[ 3 ][ 2 ] = _m[ 3 ][ 0 ] * _m2[ 0 ][ 2 ] + _m[ 3 ][ 1 ] * _m2[ 1 ][ 2 ] + _m[ 3 ][ 2 ] * _m2[ 2 ][ 2 ] + _m[ 3 ][ 3 ] * _m2[ 3 ][ 2 ];
				out[ 3 ][ 3 ] = _m[ 3 ][ 0 ] * _m2[ 0 ][ 3 ] + _m[ 3 ][ 1 ] * _m2[ 1 ][ 3 ] + _m[ 3 ][ 2 ] * _m2[ 2 ][ 3 ] + _m[ 3 ][ 3 ] * _m2[ 3 ][ 3 ];

				return out;
			}

			float* operator[]( size_t i ) { return m[ i ]; }
			const float* operator[]( size_t i ) const { return m[ i ]; }

			union {
				struct {
					float _11, _12, _13, _14;
					float _21, _22, _23, _24;
					float _31, _32, _33, _34;
					float _41, _42, _43, _44;
				};

				float m[ 4 ][ 4 ];
			};
		};
	}

	namespace unity {
		class color_c {
		public:
			float r, g, b, a;
		public:
			explicit color_c( float _r, float _g, float _b, float _a ) : r( _r ), g( _g ), b( _b ), a( _a ) { }
		};

		class transform_c {
		public:
			math::vec3_t forward( );
			math::vec3_t right( );

			math::vec3_t up( );

			math::vec3_t set_position( math::vec3_t );
			math::vec3_t position( );
		};

		class component_c {
		public:
			static transform_c* transform( void* );

			template< typename _Ty >
			_Ty get( uint64_t );
		};

		class object_c : public component_c {
		public:
			static void dont_destroy_on_load( void* );
		};

		class game_object_c : public object_c {
		public:
			template< typename _Ty >
			_Ty get( uint64_t );

			static void create( void*, sdk::unity::string_c* );
			component_c* add_component( uint64_t );
		};

		class asset_bundle_c {
		public:
			static asset_bundle_c* load_from_file( sdk::unity::string_c* );
			
			template< typename _Ty >
			_Ty load_asset( sdk::unity::string_c*, uint64_t );
		};

		class shader_c {
		public:
			static shader_c* find( sdk::unity::string_c* );
		};

		class material_c {
		public:
			static void create_with_shader( material_c*, shader_c* );

			void set_int( sdk::unity::string_c*, int );
			void set_pass( int );
		};

		class camera_c {
		public:
			static camera_c* main( );

			void set_aspect( float );
			float aspect( );

			static math::vec3_t screen_transform( math::vec3_t );
			static math::mat4x4_t view_matrix( );
		};

		class screen_c {
		public:
			static int width( );
			static int height( );

			static float fps( );
		};

		class time_c {
			static float time( );
		};

		enum class e_key_code {
			none,
			backspace = 8,
			_delete = 127,
			tab = 9,
			clear = 12,
			_return,
			pause = 19,
			escape = 27,
			space = 32,
			keypad0 = 256,
			keypad1,
			keypad2,
			keypad3,
			keypad4,
			keypad5,
			keypad6,
			keypad7,
			keypad8,
			keypad9,
			keypad_period,
			keypad_divide,
			keypad_multiply,
			keypad_minus,
			keypad_plus,
			keypad_enter,
			keypad_equals,
			up_arrow,
			down_arrow,
			right_arrow,
			left_arrow,
			insert,
			home,
			end,
			page_up,
			page_down,
			f1,
			f2,
			f3,
			f4,
			f5,
			f6,
			f7,
			f8,
			f9,
			f10,
			f11,
			f12,
			f13,
			f14,
			f15,
			alpha0 = 48,
			alpha1,
			alpha2,
			alpha3,
			alpha4,
			alpha5,
			alpha6,
			alpha7,
			alpha8,
			alpha9,
			exclaim = 33,
			double_quote,
			hash,
			dollar,
			percent,
			ampersand,
			quote,
			left_paren,
			right_paren,
			asterisk,
			plus,
			comma,
			minus,
			period,
			slash,
			colon = 58,
			semicolon,
			less,
			equals,
			greater,
			question,
			at,
			left_bracket = 91,
			backslash,
			right_bracket,
			caret,
			underscore,
			backquote,
			a,
			b,
			c,
			d,
			e,
			f,
			g,
			h,
			i,
			j,
			k,
			l,
			m,
			n,
			o,
			p,
			q,
			r,
			s,
			t,
			u,
			v,
			w,
			x,
			y,
			z,
			left_curly_bracket,
			pipe,
			right_curly_bracket,
			tilde,
			numlock = 300,
			capslock,
			scrolllock,
			right_shift,
			left_shift,
			right_control,
			left_control,
			right_alt,
			left_alt,
			left_command = 310,
			left_apple = 310,
			left_windows,
			right_command = 309,
			right_apple = 309,
			right_windows = 312,
			altgr,
			help = 315,
			print,
			sysreq,
			_break,
			menu,
			mouse0 = 323,
			mouse1,
			mouse2,
			mouse3,
			mouse4,
			mouse5,
			mouse6,
			joystick_button0,
			joystick_button1,
			joystick_button2,
			joystick_button3,
			joystick_button4,
			joystick_button5,
			joystick_button6,
			joystick_button7,
			joystick_button8,
			joystick_button9,
			joystick_button10,
			joystick_button11,
			joystick_button12,
			joystick_button13,
			joystick_button14,
			joystick_button15,
			joystick_button16,
			joystick_button17,
			joystick_button18,
			joystick_button19,
			joystick1_button0,
			joystick1_button1,
			joystick1_button2,
			joystick1_button3,
			joystick1_button4,
			joystick1_button5,
			joystick1_button6,
			joystick1_button7,
			joystick1_button8,
			joystick1_button9,
			joystick1_button10,
			joystick1_button11,
			joystick1_button12,
			joystick1_button13,
			joystick1_button14,
			joystick1_button15
		};

		enum class e_engine_layers {
			terrain = 8388608,
			world = 65536,
			ragdolls = 512,
			construction = 2097152,
			construction_socket = 4194304,
			craters = 1,
			game_trace = 16384,
			trigger = 262144,
			vehicles_detailed = 8192,
			rain_fall = 1101070337,
			deploy = 1235288065,
			default_deploy_volume_check = 537001984,
			build_line_of_sight_check = 2097152,
			projectile_line_of_sight_check = 2162688,
			projectile_line_of_sight_check_terrain = 10551296,
			meele_line_of_sight_check = 2162688,
			eye_line_of_sight_check = 2162688,
			entity_line_of_sight_check = 1218519041,
			player_buildings = 18874624,
			planner_placement = 161546496,
			solid = 1218652417,
			vis_culling = 10551297,
			altitude_check = 1218511105,
			hab_ground_effect = 1218511105,
			ai_line_of_sight = 1218519297,
			dismount_check = 1486946561,
			ai_placement = 278986753,
			wheel_ray = 1235321089
		};

		class input_c {
		public:
			static math::vec2_t scroll_delta( );
			static bool is_down( e_key_code );
		};

		enum e_event_type : int {
			mouse_down,
			mouse_up,
			mouse_move,
			mouse_drag,
			key_down,
			key_up,
			scroll_wheel,
			repaint,
			layout,
			drag_updated,
			drag_perform,
			drag_exited = 15,
			ignore = 11,
			used,
			validate_command,
			execute_command,
			context_click = 16,
			mouse_enter_window = 20,
			mouse_leave_window
		};

		class event_c {
		public:
			static event_c* current( );
			e_event_type type( );
		};

		typedef struct _rect_t {
			float m_x; 
			float m_y; 
			float m_width; 
			float m_height;

			_rect_t( float x, float y, float width, float height ) : m_x( x ), m_y( y ), m_width( width ), m_height( height ) { }
			_rect_t( ) : m_x( 0 ), m_y( 0 ), m_width( 0 ), m_height( 0 ) { }

			bool contains( math::vec2_t );
		} rect_t, * prect_t;
	}

	namespace drawing {
		class texture2d_c {
		public:
			static texture2d_c* white_texture( );
		};

		class gui_content_c {
		public:
			static gui_content_c* temp( sdk::unity::string_c* );
		};

		class gui_style_c {
		public:
			void set_font_size( int );
			int font_size( );

			math::vec2_t calc_size( gui_content_c* );
		};

		class gui_skin_c {
		public:
			gui_style_c* label( );
		};

		class gui_c {
		public:
			static gui_skin_c* skin( );

			static void set_color( sdk::unity::color_c );
			static sdk::unity::color_c color( );

			static void draw_texture( sdk::unity::rect_t, texture2d_c* );

			static void draw_texture2( sdk::unity::rect_t, texture2d_c*, int, bool, float, sdk::unity::color_c, float, float );
			static void draw_texture3( sdk::unity::rect_t, texture2d_c*, int, bool, float, sdk::unity::color_c, math::vec4_t, math::vec4_t, bool );

			static void label( sdk::unity::rect_t, gui_content_c* content, gui_style_c* );
		};
	}

	namespace gl {
		enum e_primitive_mode : int {
			lines = 1,
			line_strip,
			triangles = 4,
			triangle_strip = 5,
			quads = 7
		};

		class gl_c {
		public:
			static void push( );
			static void pop( );

			static void begin( e_primitive_mode );
			static void end( );

			static void color( unity::color_c );
			static void vertex3( float, float, float );
		};

		void start( e_primitive_mode );
		void end( );
	}

	class base_networkable_c {
	public:
		static uint64_t decrypt( uint64_t );
		static uint64_t decrypt_list( uint64_t );
	};

	class base_player_c {
	public:
		sdk::unity::transform_c* get_bone_transform( int );

		bool is_sleeping( );
		bool is_dead( );
	};
}