#ifndef __DRAW_H__
#define __DRAW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>

#include <neb/core/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/util/decl.hpp>

namespace neb {
	namespace glsl {
		class shader;

		class program: public sp::enable_shared_from_this<program> {
			public:
				program(neb::program_name::e name);
				void	init();
				void	add_shader(char const *, GLenum);
				void	add_shaders(::std::vector<neb::glsl::shader>);
				void	compile();
				void	use();
				void	locate();
				void	scanUniforms();

				void	add_attrib(neb::attrib_name::e, char const *, GLuint);
				void	add_uniform_scalar(::std::string, GLenum);
				void	add_uniform_vector(::std::string, ::std::string, GLenum);
				
				
				::std::shared_ptr<neb::glsl::attrib>					get_attrib(int);
				::std::shared_ptr<neb::glsl::Uniform::Scalar::base>			get_uniform_scalar(::std::string);
				::std::shared_ptr<neb::glsl::Uniform::Vector::base>			get_uniform_vector(::std::string);

				//std::shared_ptr<neb::glsl::uniform>	get_uniform(int,int);

				GLuint	o_;
				
				::std::map< ::std::string, sp::shared_ptr<neb::glsl::Uniform::Scalar::base> >		uniform_scalar_;
				::std::map< ::std::string, sp::shared_ptr<neb::glsl::Uniform::Vector::base> >		uniform_vector_;

				::std::map<int, sp::shared_ptr<attrib> >						attrib_;
				neb::program_name::e									name_;
		};
	}
}
#endif
