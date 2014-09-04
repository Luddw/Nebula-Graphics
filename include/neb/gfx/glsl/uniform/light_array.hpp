#ifndef NEB_GFX_GLSL_LIGHT_ARRAY_HPP
#define NEB_GFX_GLSL_LIGHT_ARRAY_HPP

#include <neb/gfx/glsl/uniform/array.hpp>


namespace neb { namespace gfx { namespace glsl { namespace uniform {
	template<int I> class locations;
	class light_array: public array<
			   glm::vec3,	//  0	position
			   glm::vec4,	//  1	ambient
			   glm::vec4,	//  2	diffuse
			   glm::vec4,	//  3	specular
			   float,	//  4	atten const
			   float,	//  5	atten linear
			   float,	//  6	atten quad
			   glm::vec3,	//  7	spot direction
			   float,	//  8	spot cutoff
			   float,	//  9	spot exponent
			   glm::mat4,	// 10	shadow vpb matrix 0
			   glm::mat4,	// 11	shadow vpb matrix 1
			   glm::mat4,	// 12	shadow vpb matrix 2
			   glm::mat4,	// 13	shadow vpb matrix 3
			   glm::mat4,	// 14	shadow vpb matrix 4
			   glm::mat4,	// 15	shadow vpb matrix 5
			   glm::vec3,	// 16	shadow sampler 0
			   glm::vec3,	// 17	shadow sampler 1
			   int		// 18	type
						   >
	{
		public:
			light_array() {}
			void		set_pos(int i, glm::vec3 const & pos) {
				set<0>(i, pos);
			}
			void		set_spot_direction(int i, glm::vec3 const & pos) {
				set<7>(i, pos);
			}
			void		set_shadow_vpb_0(int i, glm::mat4 const & v) { set<10>(i, v); }
			void		set_shadow_vpb_1(int i, glm::mat4 const & v) { set<11>(i, v); }
			void		set_shadow_vpb_2(int i, glm::mat4 const & v) { set<12>(i, v); }
			void		set_shadow_vpb_3(int i, glm::mat4 const & v) { set<13>(i, v); }
			void		set_shadow_vpb_4(int i, glm::mat4 const & v) { set<14>(i, v); }
			void		set_shadow_vpb_5(int i, glm::mat4 const & v) { set<15>(i, v); }
			void		set_shadow_sampler_0(int i, glm::vec3 const & v) { set<16>(i, v); }
			void		set_shadow_sampler_1(int i, glm::vec3 const & v) { set<17>(i, v); }
	};
	class light_locations: public light_array::loc_type {
		public:
			void		init(std::shared_ptr<neb::gfx::glsl::program::threed> program);
	};
}}}}



#endif

