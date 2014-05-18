#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <Nebula/Actor/Actor.hh>

namespace Neb {
	namespace Actor {
		namespace RigidActor {
			class Base: virtual public Neb::Actor::Actor::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s);

					virtual void					init();

					/*virtual void					step_local(double);
					  virtual void					step_remote(double);*/

					virtual void					setupFiltering();

					virtual Neb::Actor::Base_s			get_projectile() = 0;

					virtual void					create_physics() = 0;
					virtual void					init_physics() = 0;

					virtual void					print_info();
			};
			class Local:
				virtual public Neb::Actor::RigidActor::Base,
				virtual public Neb::Actor::Actor::Local
			{
				public:
					virtual void		stepRigidBodyDerived(double);
			};
			class Remote:
				virtual public Neb::Actor::RigidActor::Base,
				virtual public Neb::Actor::Actor::Remote
			{
				public:
					virtual void		stepRigidBodyDerived(double);
			};
		}
	}
}

#endif








