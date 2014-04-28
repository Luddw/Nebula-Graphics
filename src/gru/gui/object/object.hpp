#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <memory>

#include <tinyxml2.h>

//#include <math/color.hpp>

//#include <galaxy/sig/connection.hpp>

#include <gru/master.hpp>

namespace glutpp { namespace gui { namespace object {

	class object {
		public:

			object();
			void				i(int);
			void				load_xml(tinyxml2::XMLElement*);


			//window::window_s		get_window();
			virtual void			draw() = 0;
			void				set_label(char const *);
			virtual int			key_fun(int,int,int,int) = 0;
			virtual int			mouse_button_fun(int,int,int);
			//virtual void			connect();



			int				i_;


			float				x_;
			float				y_;
			float				w_;
			float				h_;

			gru::Color::color<float>	font_color_;
			gru::Color::color<float>	bg_color_;

			bool				active_;

			//std::shared_ptr<jess::signal::connection<int> > connection_key_down_;
			/// key up
			//std::shared_ptr<jess::signal::connection<int> > connection_key_up_;
			/// key_down
			/*virtual int		handle_key(unsigned short,int) = 0;
			  virtual int		handle_key_down(unsigned short) = 0;
			/// key_up
			virtual int		handle_key_up(unsigned short) = 0;*/
			//int			key_down_mask_;
			//int			key_up_mask_;
			size_t				label_length_;
			char *				label_;


			// connections
			struct
			{
				mouse_button_fun_c	mouse_button_fun_;
				key_fun_c		key_fun_;
			} conns_;



	};
}
}
}
#endif

