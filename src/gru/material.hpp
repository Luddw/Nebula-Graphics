#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <tinyxml2.h>

//#include <math/raw/raw.h>
//#include <math/color.hpp>

#include <gru/Color/Color.hpp>

namespace glutpp {
	namespace material {


		struct raw
		{
			raw();
			void				load(tinyxml2::XMLElement*);

			gru::Color::color<float>	ambient_;
			gru::Color::color<float>	diffuse_;
			gru::Color::color<float>	specular_;
			gru::Color::color<float>	emission_;
			float				shininess_;
		};

		class material
		{
			public:
				material();
				void		init();
				void		load();
				void		step(double);

				raw		raw_;
		};
	}
}

#endif
