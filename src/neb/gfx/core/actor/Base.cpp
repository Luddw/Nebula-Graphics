#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/core/scene/base.hpp>

#include <neb/core/timer/actor/Base.hpp>

//#include <neb/gfx/window/util/signals.hpp>
#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/util/log.hpp>

//neb::gfx::core::actor::base::base()

/*neb::gfx::core::actor::base::base(std::shared_ptr<neb::fnd::core::actor::util::parent> parent):
	gal::stl::child<neb::fnd::core::actor::base
	neb::fnd::core::actor::base(parent)
{
	LOG(lg, neb::fnd::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}*/
neb::gfx::core::actor::base::~base() {
	LOG(lg, neb::fnd::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}
void				neb::gfx::core::actor::base::draw(
		neb::gfx::glsl::program::base const * const & program,
		neb::fnd::math::pose const & pose)
{
	LOG(lg, neb::fnd::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	auto npose = pose * pose_;

	typedef neb::fnd::core::actor::util::parent A;
	typedef neb::fnd::core::shape::util::parent S;

	A::map_.for_each([&] (A::map_type::pointer p) {
			auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(p);
			assert(actor);
			actor->draw(program, npose);
			});

	S::map_.for_each([&] (S::map_type::pointer p) {
			auto shape = std::dynamic_pointer_cast<neb::gfx::core::shape::base>(p);
			assert(shape);
			shape->draw(program, npose);
			});


}
void				neb::gfx::core::actor::base::drawDebug(
		neb::gfx::glsl::program::base const * const & program,
		neb::fnd::math::pose const & pose)
{
	LOG(lg, neb::fnd::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	auto npose = pose * pose_;

	typedef neb::fnd::core::actor::util::parent A;
	typedef neb::fnd::core::shape::util::parent S;

	A::map_.for_each([&] (A::map_type::pointer p) {
			auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(p);
			assert(actor);
			actor->drawDebug(program, npose);
			});

	S::map_.for_each([&] (S::map_type::pointer p) {
			auto shape = std::dynamic_pointer_cast<neb::gfx::core::shape::base>(p);
			assert(shape);
			shape->drawDebug(program, npose);
			});


}
void				neb::gfx::core::actor::base::drawHF(
		neb::gfx::glsl::program::base const * const & program,
		neb::fnd::math::pose const & pose)
{
	LOG(lg, neb::fnd::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	auto npose = pose * pose_;

	typedef neb::fnd::core::actor::util::parent A;
	typedef neb::fnd::core::shape::util::parent S;

	A::map_.for_each([&] (A::map_type::pointer p) {
			auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(p);
			assert(actor);
			actor->drawHF(program, npose);
			});

	S::map_.for_each([&] (S::map_type::pointer p) {
			auto shape = std::dynamic_pointer_cast<neb::gfx::core::shape::base>(p);
			assert(shape);
			shape->drawHF(program, npose);
			});


}




