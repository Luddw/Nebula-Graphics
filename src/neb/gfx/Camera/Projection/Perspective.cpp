#include <stdio.h>
#include <assert.h>
#include <iomanip>

#include <GL/glew.h>

#include <Galaxy-Log/log.hpp>

//#include <math/quat.hpp>
//#include <math/mat44.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/debug.hh>
#include <neb/app/Base.hh>
#include <neb/core/actor/base.hpp>
//#include <neb/gfx/window/Base.hh>
//#include <neb/core/scene/base.hpp>
#include <neb/gfx/Camera/Projection/Perspective.hh>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/glsl/Uniform/scalar.hpp>

neb::gfx::Camera::Projection::base::base(sp::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		neb::gfx::Camera::Projection::base::load(sp::shared_ptr<neb::glsl::program> p) {
	
	
	//glViewport(0, 0, parent_->viewport_.w_, parent_->viewport_.h_);
	
	p->get_uniform_scalar("proj")->load(proj());
}
void		neb::gfx::Camera::Projection::base::step(gal::std::timestep const & ts) {

}


neb::gfx::Camera::Projection::Perspective::Perspective(sp::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::Camera::Projection::base(parent),
	fovy_(45.0f),
	zn_(2.0f),
	zf_(10000.0f)
{

}
/*void		neb::gfx::Camera::Projection::Perspective::init(RENDERABLE_S renderable) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	renderable_ = renderable;
}*/
mat4		neb::gfx::Camera::Projection::Perspective::proj() {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "fovy" << ::std::setw(8) << fovy_;
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "aspect" << ::std::setw(8) << parent_->viewport_.aspect_;
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "zn" << ::std::setw(8) << zn_;
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "zf" << ::std::setw(8) << zf_;
	
	mat4 ret = glm::perspective(fovy_, parent_->viewport_.aspect_, zn_, zf_);
	
	//ret.print();
	
	return ret;
}
void		neb::gfx::Camera::Projection::Perspective::step(gal::std::timestep const & ts) {

}








