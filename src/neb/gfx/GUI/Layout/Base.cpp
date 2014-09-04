
#include <string>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/decl.hpp>

#include <neb/gfx/window/Base.hh>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/gui/object/Base.hh>
#include <neb/gfx/gui/object/edittext.hh>
#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/util/log.hpp>

neb::gfx::gui::layout::base::base(std::shared_ptr<neb::gfx::gui::layout::util::parent> parent): parent_(parent) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

}
void neb::gfx::gui::layout::base::init() {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	//jess::clog << NEB_FUNCSIG << std::endl;
}
void		neb::gfx::gui::layout::base::step(gal::etc::timestep const & ts) {
		LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

}
void		neb::gfx::gui::layout::base::draw(std::shared_ptr<neb::gfx::context::base> context, std::shared_ptr<neb::gfx::glsl::program::base> program) {
	
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	typedef neb::gfx::gui::object::util::parent O;

	auto lamb = [&] (O::map_type::pointer p) {
		auto object = std::dynamic_pointer_cast<neb::gfx::gui::object::base>(p);
		assert(object);
		object->draw(program);
	};

	O::map_.for_each(lamb);

}
void neb::gfx::gui::layout::base::connect(std::shared_ptr<neb::gfx::window::base> const & window) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	conns_.key_fun_ = window->sig_.key_fun_.connect(
			10,
			::std::bind(&neb::gfx::gui::layout::base::key_fun,
				this,
				::std::placeholders::_1,
				::std::placeholders::_2,
				::std::placeholders::_3,
				::std::placeholders::_4,
				::std::placeholders::_5
				));
	conns_.charFun_ = window->sig_.charFun_.connect(
			10,
			::std::bind(&neb::gfx::gui::layout::base::charFun,
				this,
				::std::placeholders::_1,
				::std::placeholders::_2
				));

	conns_.mouse_button_fun_ = window->sig_.mouse_button_fun_.connect(
			10,
			::std::bind(&neb::gfx::gui::layout::base::mouse_button_fun,
				this,
				::std::placeholders::_1,
				::std::placeholders::_2,
				::std::placeholders::_3,
				::std::placeholders::_4
				));

}
int		neb::gfx::gui::layout::base::key_fun(std::shared_ptr<neb::gfx::window::base> const & window, int key, int scancode, int action, int mode) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	typedef neb::gfx::gui::object::util::parent O;

	//O::map_.for_each_int<0>([&] (O::map_type::iterator<0> it) {
	for(O::map_type::iterator it = O::map_.begin(); it != O::map_.end(); ++it) {
		auto object = std::dynamic_pointer_cast<neb::gfx::gui::object::base>(it->second.ptr_);
		assert(object);

		if(object->key_fun(window, key, scancode, action, mode)) return 1;
	};

	return 0;
}
int		neb::gfx::gui::layout::base::charFun(
		shared_ptr<neb::gfx::window::base> const & window,
		unsigned int codepoint) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	typedef neb::gfx::gui::object::util::parent O;

	for(O::map_type::iterator it = O::map_.begin(); it != O::map_.end(); ++it) {
		auto object = dynamic_pointer_cast<neb::gfx::gui::object::base>(it->second.ptr_);
		assert(object);

		if(object->charFun(window, codepoint)) return 1;
	};

	return 0;
}
int neb::gfx::gui::layout::base::mouse_button_fun(std::shared_ptr<neb::gfx::window::base> const & window, int button, int action, int mods) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(window);

	switch(action) {
		case GLFW_PRESS:
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					search(window, button, action, mods);
					break;
			}
			break;
		default:
			return 0;
	}

	return 0;
}
int			neb::gfx::gui::layout::base::search(std::shared_ptr<neb::gfx::window::base> const & window, int button, int action, int mods) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(window);

	double x, y;
	int w, h;
	glfwGetCursorPos(window->window_, &x, &y);
	glfwGetWindowSize(window->window_, &w, &h);

	printf("%f %f %i %i\n", x, y, w, h);

	x = x / (float)w * 2.0 - 1.0;
	y = y / (float)h * 2.0 - 1.0;

	printf("%f %f\n", x, y);

	typedef neb::gfx::gui::object::util::parent O;

	std::shared_ptr<neb::gfx::gui::object::base> object;
	std::shared_ptr<neb::gfx::gui::object::base> objecttmp;

	auto lamb = [&] (O::map_type::pointer p) {
		objecttmp = std::dynamic_pointer_cast<neb::gfx::gui::object::base>(p);
		assert(objecttmp);
		printf("object %f %f %f %f\n",
				objecttmp->x_,
				objecttmp->y_,
				objecttmp->w_,
				objecttmp->h_);	

		if(x <   objecttmp->x_) return O::map_type::CONTINUE;
		if(x > ( objecttmp->x_ + objecttmp->w_)) return O::map_type::CONTINUE;
		if(y >  -objecttmp->y_) return O::map_type::CONTINUE;
		if(y < (-objecttmp->y_ - objecttmp->h_)) return O::map_type::CONTINUE;

		object = objecttmp;

		return O::map_type::BREAK;
	};

	O::map_.for_each_int(lamb);

	if(object) return object->mouse_button_fun(window, button, action, mods);

	return 0;
}
weak_ptr<neb::gfx::gui::object::terminal>		neb::gfx::gui::layout::base::createObjectTerminal() {
	auto term = sp::make_shared<neb::gfx::gui::object::terminal>();
	insert(term);
	term->init();
	return term;
}


