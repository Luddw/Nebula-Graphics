#ifndef NEB_GFX_CORE_SCENE_BASE_HPP
#define NEB_GFX_CORE_SCENE_BASE_HPP


#include <vector>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <gal/etc/flag.hpp>
#include <gal/stl/map.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/math/serialization/glm.hpp>
#include <neb/core/core/actor/util/parent.hpp>
#include <neb/core/core/scene/base.hpp>

#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/glsl/uniform/light_array.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>


typedef weak_ptr<neb::core::core::actor::base> wbase;

namespace neb { namespace gfx { namespace core { namespace scene {

	/** 
	 * @ingroup group_core
	 * @brief base
	 */
	class base:
		virtual public neb::core::core::scene::base,
		virtual public neb::gfx::drawable::base
	{
		public:
			base();
			virtual ~base();
			void					__init(parent_t * const & p);
			void					init_light();
			virtual void				release();
			void					step(::gal::etc::timestep const & ts);


			void					resize(int w, int h);

			void					draw(gfx::RenderDesc const &);
			void					drawMesh(gfx::RenderDesc const &);
			void					drawMeshHF(gfx::RenderDesc const &);
			void					drawMeshInst(gfx::RenderDesc const &);
			void					drawPhysxVisualization(gfx::RenderDesc const &);
			void					drawDebug(gfx::RenderDesc const &);

		public:
			virtual void				load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
			virtual void				save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
			/** @name convenience functions
			 * @{
			 */
			/** @brief create rigiddynamic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			virtual weak_ptr<neb::core::core::actor::base>		createActorRigidStaticUninitialized() = 0;
			/** @brief create rigidstatic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			virtual weak_ptr<neb::core::core::actor::base>		createActorRigidDynamicUninitialized() = 0;
			/** @} */




			// rendering data

			struct
			{
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3;
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3_HF;
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3_inst;
			} _M_programs;

			// one for static, one for dynamic
			std::shared_ptr<neb::gfx::glsl::uniform::light_array>		light_array_[2];

			std::shared_ptr<neb::gfx::texture>				tex_shadow_map_;

			// standard meshes
			struct {
				std::shared_ptr<neb::gfx::mesh::instanced>		cuboid_;
			} meshes_;



	};
}}}}

#endif

