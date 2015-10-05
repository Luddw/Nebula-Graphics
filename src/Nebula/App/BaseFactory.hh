#ifndef NEBULA_APP_BASE_FACTORY_HH
#define NEBULA_APP_BASE_FACTORY_HH

#include <memory>

#include <Nebula/Types.hh>

#include <Nebula/Util/Factory.hh>

#include <Nebula/Graphics/Types.hh>

#include <Nebula/Scene/Util/Types.hh>
#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Shape/Util/Types.hh>

#include <Nebula/Message/Types.hh>

namespace Neb {
	namespace App {
		class BaseFactory {
			public:
				template<typename T> using pointer = std::shared_ptr<T>;

				typedef pointer< Neb::Factory<Neb::Graphics::Window::Base> >			Window_Base;
				typedef pointer< Neb::Factory<Neb::Graphics::GUI::Object::Base> >		GUI_Object;
				typedef pointer< Neb::Factory<Neb::Scene::Base> >				Scene_Base;
				typedef pointer< Neb::Factory<Neb::Actor::Base> >				Actor_Base;
				typedef pointer< Neb::Factory<Neb::Shape::Base> >				Shape_Base;
				typedef pointer< Neb::Factory<Neb::Light::Base> >				Light_Base;
			public:
				virtual ~BaseFactory() {}

				template<class T> std::shared_ptr< Neb::Factory<T> >		getFactoryDefault();

				static BaseFactory_s						global();

				/** @brief Factories */
				struct {
					Window_Base			window_base_;
					GUI_Object			gui_object_base_;
					Scene_Base			scene_base_;
					Actor_Base			actor_base_;
					Shape_Base			shape_base_;
					Light_Base			light_base_;
				} factories_;
			protected:
				/** %brief global app object */
				static Neb::App::BaseFactory_s					g_app_;

		};

		template<> std::shared_ptr< Neb::Factory<Neb::Graphics::Window::Base> >		BaseFactory::getFactoryDefault<Neb::Graphics::Window::Base>();
		template<> std::shared_ptr< Neb::Factory<Neb::Graphics::GUI::Object::Base> >	BaseFactory::getFactoryDefault<Neb::Graphics::GUI::Object::Base>();
		template<> std::shared_ptr< Neb::Factory<Neb::Scene::Base> >			BaseFactory::getFactoryDefault<Neb::Scene::Base>();
		template<> std::shared_ptr< Neb::Factory<Neb::Actor::Base> >			BaseFactory::getFactoryDefault<Neb::Actor::Base>();
		template<> std::shared_ptr< Neb::Factory<Neb::Shape::Base> >			BaseFactory::getFactoryDefault<Neb::Shape::Base>();
		template<> std::shared_ptr< Neb::Factory<Neb::Light::Base> >			BaseFactory::getFactoryDefault<Neb::Light::Base>();
		
		template<> std::shared_ptr< Neb::Factory<Neb::Message::Base> >			BaseFactory::getFactoryDefault<Neb::Message::Base>();

	}
}

#endif



