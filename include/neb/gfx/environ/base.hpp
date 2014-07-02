#ifndef NEBULA_GFX_ENVIRON_BASE_HPP
#define NEBULA_GFX_ENVIRON_BASE_HPP

#include <gal/std/timestep.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/environ/util/cast.hpp>
#include <neb/gfx/Viewport.hpp>

namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class base:
		virtual public neb::gfx::environ::util::cast
	{
		public:
			virtual ~base() {}


			virtual void		init();
			virtual void		step(gal::std::timestep const & ts);


			virtual void		resize(int w, int h);


			virtual void		render(sp::shared_ptr<neb::gfx::context::base> context) = 0;
		public:	
			/** @brief %Viewport
			 * 
			 * sub-rectangle within target
			 */
			neb::gfx::Viewport					viewport_;


			sp::weak_ptr<neb::gfx::drawable::base>			drawable_;
	};


}}}


#endif
