
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/window/Base.hh>


void					neb::gfx::app::__gfx::__init() {

	vector<std::string> fontfiles({
		"/usr/share/fonts/msttcorefonts/cour.ttf",
		"/usr/share/fonts/truetype/msttcorefonts/cour.ttf"});

	// font
	//FT_Library ft;
	if(FT_Init_FreeType(&ft_))
	{
		printf("could not find freetype library\n");
		exit(0);
	}

	int result = 1;
	for(auto s : fontfiles) {
		result = FT_New_Face(ft_, s.c_str(), 0, &face_);
		if(result) {
			::std::cout << "Could not open font " << s << ::std::endl;
		} else {
			break;
		}
	}

	if(result) {
		printf("Count not open any fonts\n");
		abort();
	}


	// glfw

	glfwSetErrorCallback(static_error_fun);
	glfwInit();
	

	flag_.set(neb::core::app::util::flag::INIT_GLFW);
	
}
void				neb::gfx::app::__gfx::release() {
}
void				neb::gfx::app::__gfx::step(gal::etc::timestep const & ts) {
	
	neb::gfx::window::util::parent::step(ts);

	//neb::gfx::context::util::parent::step(ts);

	neb::gfx::gui::layout::util::parent::step(ts);
}
void				neb::gfx::app::__gfx::render()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	neb::gfx::window::util::parent::render();

	//neb::gfx::context::util::parent::render();

}
void				neb::gfx::app::__gfx::init_glew() {

	if(!flag_.any(neb::core::app::util::flag::INIT_GLEW)) {

		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			printf("GLEW: %s\n", glewGetErrorString(err));
			exit(EXIT_FAILURE);
		}

		flag_.set(neb::core::app::util::flag::INIT_GLEW);
	}
}
//void							neb::gfx::app::__gfx::release() {
//}
weak_ptr<neb::gfx::app::__gfx>				neb::gfx::app::__gfx::global() {
	auto app(dynamic_pointer_cast<neb::gfx::app::__gfx>(g_app_));
	assert(app);
	return app;
}
weak_ptr<neb::gfx::window::base>			neb::gfx::app::__gfx::get_window(GLFWwindow* window) {
	auto it = windows_glfw_.find(window);
	assert(it != windows_glfw_.cend());
	assert(it->second);
	return it->second;
}
void							neb::gfx::app::__gfx::static_error_fun(int error, char const * description) {
	printf("%s\n", description);
	abort();
}
void							neb::gfx::app::__gfx::static_window_pos_fun(GLFWwindow* window, int x, int y){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::__gfx::global().lock()->get_window(window).lock();

	w->callback_window_pos_fun(window,x,y);
}
void							neb::gfx::app::__gfx::static_window_size_fun(GLFWwindow* window, int width, int h){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::__gfx::global().lock()->get_window(window).lock();

	w->callback_window_size_fun(window, width, h);
}
void							neb::gfx::app::__gfx::static_window_close_fun(GLFWwindow* window){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::__gfx::global().lock()->get_window(window).lock();

	w->callback_window_close_fun(window);
}
void							neb::gfx::app::__gfx::static_window_refresh_fun(GLFWwindow* window) {
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::__gfx::global().lock()->get_window(window).lock();

	w->callback_window_refresh_fun(window);
}
void							neb::gfx::app::__gfx::static_mouse_button_fun(GLFWwindow* window, int button, int action, int mods){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::__gfx::global().lock()->get_window(window).lock();

	w->callback_mouse_button_fun(window, button, action, mods);
}
void							neb::gfx::app::__gfx::static_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::__gfx::global().lock()->get_window(window).lock();

	w->callback_key_fun(window, key, scancode, action, mods);
}
void							neb::gfx::app::__gfx::staticCharFun(GLFWwindow* window, unsigned int codepoint) {
	auto w = neb::gfx::app::__gfx::global().lock()->get_window(window).lock();
	w->callbackCharFun(window, codepoint);
}
std::weak_ptr<neb::gfx::gui::layout::base>		neb::gfx::app::__gfx::createLayout()
{
	auto self(dynamic_pointer_cast<neb::gfx::app::__gfx>(shared_from_this()));

	auto layout = std::make_shared<neb::gfx::gui::layout::base>(self);

	neb::gfx::gui::layout::util::parent::insert(layout);

	layout->init();

	return layout;
}
std::weak_ptr<neb::gfx::window::base>			neb::gfx::app::__gfx::createWindow()
{
	auto self(std::dynamic_pointer_cast<neb::gfx::app::__gfx>(shared_from_this()));
	
	auto window = std::make_shared<neb::gfx::window::base>(self);
	
	neb::gfx::window::util::parent::insert(window);

	window->__init();
	
	return window;
}













