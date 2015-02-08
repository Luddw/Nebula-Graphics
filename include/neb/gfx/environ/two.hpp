#ifndef NEBULA_GFX_ENVIRON_TWO_HPP
#define NEBULA_GFX_ENVIRON_TWO_HPP

#include <neb/core/environ/Two.hpp>

#include <neb/gfx/environ/base.hpp>

namespace neb { namespace gfx { namespace environ {
	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable
	 */
	class two:
		virtual public neb::fnd::environ::Two,
		virtual public neb::gfx::environ::base
	{
		public:
			virtual void		render(
					std::shared_ptr<neb::gfx::context::base> context);
			//std::shared_ptr<neb::gfx::drawable::two>		drawable_;
	};
}}}

#endif
