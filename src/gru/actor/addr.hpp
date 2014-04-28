#ifndef __NEBULA_ACTOR_ADDR_H__
#define __NEBULA_ACTOR_ADDR_H__

//#include <math/transform.hpp>
//#include <math/raw/raw.hpp>

#include <gru/scene/addr.hpp>
//#include <gru/actor/actor.hpp>

namespace glutpp
{
	namespace actor
	{
		typedef gal::network::vector<int> vec_int;
		typedef std::shared_ptr<vec_int> vec_int_s;



		class addr: public gal::network::serial_ext<vec_int, glutpp::scene::addr> {
			public:
				void	load_this(glutpp::actor::actor_s);
				void	load_parent(glutpp::actor::actor_s);

				glutpp::scene::addr_s	get_scene_addr();
				vec_int_s		get_vec();
		};
	}
}

#endif








