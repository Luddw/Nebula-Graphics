#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_LOCAL_HPP__

#include <Nebula/Actor/Actor/Local.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor {
		

namespace rigidactor {
			class local:
				virtual public neb::core::actor::rigidactor::Base,
				virtual public neb::core::actor::actor::local
			{
				public:
					virtual void				step(neb::core::TimeStep const & ts);
			};


}		}
	}
}

#endif








