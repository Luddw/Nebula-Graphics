#include <gal/log/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/light/spot.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/glsl/program/base.hpp>


neb::gfx::core::light::spot::spot(std::shared_ptr<neb::core::core::light::util::parent> parent):
	neb::core::core::light::base(parent),
	neb::gfx::core::light::base(parent, 1),
	spot_direction_(vec3(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
}
void			neb::gfx::core::light::spot::load(
		neb::core::core::light::util::count & light_count,
		neb::core::pose const & pose) {

/*	neb::gfx::core::light::base::load(light_count.spot, pose);
	
	auto p = neb::gfx::app::__gfx_glsl::global().lock()->current_program();
	
	vec4 spot_direction(spot_direction_,0.0);

	spot_direction = pose.rot_ * spot_direction;

	p->get_uniform_vector("lights_spot.atten_const")->load(light_count.spot, atten_const_);
	p->get_uniform_vector("lights_spot.atten_linear")->load(light_count.spot, atten_linear_);
	p->get_uniform_vector("lights_spot.atten_quad")->load(light_count.spot, atten_quad_);


	p->get_uniform_vector("lights_spot.spot_direction")->load(light_count.spot, spot_direction);
	p->get_uniform_vector("lights_spot.spot_cutoff")->load(light_count.spot, spot_cutoff_);
	p->get_uniform_vector("lights_spot.spot_exponent")->load(light_count.spot, spot_exponent_);
	p->get_uniform_vector("lights_spot.spot_light_cos_cutoff")->load(light_count.spot, spot_light_cos_cutoff_);

	light_count.spot++;
	*/
}








