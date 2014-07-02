#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

#include <vector>
#include <memory>

//#include <galaxy/sig/connection.hpp>

/*
#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/mat44.hpp>
*/

#include <neb/util/decl.hpp>
#include <gal/std/timestep.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/Camera/View/util/flag.hpp>
#include <neb/util/shared.hpp>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace View {
				/** @brief @Base */
				class base: virtual public neb::std::shared {
					public:
						/** @brief Constructor */
						base(sp::shared_ptr< ::neb::gfx::environ::base > parent);
						/** @brief Load view matrix into GLSL. */
						void						load(sp::shared_ptr< ::neb::glsl::program > p);
						/** @brief Get view matrix. */
						virtual glm::mat4				view() = 0;
						/** @brief Step
						 *
						 * @todo explain when in timeline this occurs and in which thread and why
						 */
						virtual void					step(::gal::std::timestep const & ts) = 0;

						virtual void					connect(
								sp::shared_ptr< ::neb::gfx::window::base > const & window) {}

					public:
						sp::shared_ptr< ::neb::gfx::environ::base >		parent_;

						neb::gfx::camera::view::util::flag			flag_;
				};
			}
		}
	}
}

#endif


