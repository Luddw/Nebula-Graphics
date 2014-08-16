//#include <neb/app/base.hpp>
#include <neb/gfx/Camera/View/Base.hh>
#include <neb/gfx/glsl/program.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>

neb::gfx::Camera::View::base::base(std::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		neb::gfx::Camera::View::base::load(std::shared_ptr<neb::glsl::program> p) {
	
	p->get_uniform_scalar("view")->load(view());
}


