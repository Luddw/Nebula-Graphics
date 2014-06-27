#include <Galaxy-Log/log.hpp>

#include <neb/debug.hh>
#include <neb/core/shape/base.hpp>
//#include <neb/Physics.hh>

#include <PhysX/app/base.hpp>
#include <PhysX/core/scene/base.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/rigiddynamic/base.hpp>
#include <PhysX/core/actor/rigiddynamic/base.hpp>
#include <PhysX/util/convert.hpp>

phx::core::actor::rigiddynamic::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	phx::core::actor::base(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::rigidactor::base(parent),
	phx::core::actor::rigidbody::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
}
void			phx::core::actor::rigiddynamic::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	assert(px_actor_);
	auto pxrd = px_actor_->isRigidDynamic();
	pxrd->setLinearDamping(0.01);
}
void			phx::core::actor::rigiddynamic::base::create_physics() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	if(px_actor_ != NULL) {
		if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << "been here!";
		return;
	}

	auto scene = sp::dynamic_pointer_cast<phx::core::scene::base>(getScene());

	auto p(getPose());	
	physx::PxTransform pose(
			phx::util::convert(vec3(p.pos_)),
			phx::util::convert(p.rot_)
			);
	
	
	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic = phx::app::base::global()->px_physics_->createRigidDynamic(pose);

	if (!px_rigid_dynamic)
	{
		printf("create actor failed!");
		exit(1);
	}

	px_actor_ = px_rigid_dynamic;

	px_rigid_dynamic->setLinearVelocity(phx::util::convert(velocity_), true);

	// userData
	auto sft = shared_from_this();
	auto uc = sft.use_count();


	px_rigid_dynamic->userData = isActorBase().get();


	assert(uc == sft.use_count());

	// debug
	assert(this == shared_from_this().get());
	assert(this == isActorBase().get());
	assert(this == isPxActorRigidDynamicBase().get());
	assert(sp::dynamic_pointer_cast<phx::core::actor::rigidbody::base>(shared_from_this()));
	

	// add PxActor to PxScene
	assert(scene->px_scene_);
	scene->px_scene_->addActor(*px_rigid_dynamic);

	assert(px_actor_);
}
void			phx::core::actor::rigiddynamic::base::init_physics() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	assert(px_actor_);	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	assert(px_rigid_dynamic);

	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, density_);
	
	setupFiltering();
}



