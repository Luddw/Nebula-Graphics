#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <map>

#include <glm/glm.hpp>

#include <neb/core/input/sink.hpp>
#include <neb/core/input/util/decl.hpp>
#include <neb/core/gui/layout/Base.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/gui/object/Base.hh>
#include <neb/gfx/gui/object/util/decl.hpp>
#include <neb/gfx/gui/object/util/parent.hpp>
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/tmp/Child.hpp>
//#include <neb/gfx/window/Base.hh>

namespace neb { namespace gfx { namespace gui { namespace layout {
	/** @brief %Base */
	class base:
		virtual public neb::fnd::gui::layout::Base,
		virtual public neb::gfx::drawable::base,
		virtual public neb::gfx::gui::object::util::parent,
		virtual public neb::gfx::tmp::Child<neb::gfx::gui::layout::util::parent>,
		virtual public neb::fnd::input::sink
	{
		public:
			using CHILD::get_fnd_app;
			//using CHILD::get_gfx_app;
			typedef neb::gfx::gui::layout::util::parent parent_t;
			base();
			virtual ~base() {}
			virtual void				init(parent_t * const & p);
			virtual void				release() {}
			/** @brief Main Loop @{ */
			virtual void					step(gal::etc::timestep const & ts);
			virtual void					draw(RenderDesc const &);
			/** @} */
			void						connect(
					std::shared_ptr<neb::fnd::input::source> const & window);
			int						search(
					std::shared_ptr<neb::fnd::input::source> const &,
					int button,
					int action,
					int mods);
			int						mouseButtonFun(
					std::shared_ptr<neb::fnd::input::source> const &,int button, int action, int mods);
			int						keyFun(
					std::shared_ptr<neb::fnd::input::source> const &,int,int,int,int);
			int						charFun(
					std::shared_ptr<neb::fnd::input::source> const &,
					unsigned int codepoint);
			std::weak_ptr<neb::gfx::gui::object::terminal>	createObjectTerminal();
			glm::mat4x4					ortho_;
	};
}}}}

#endif
