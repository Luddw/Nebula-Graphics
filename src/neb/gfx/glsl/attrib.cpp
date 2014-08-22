#include <stdio.h>

#include <GL/glew.h>

#include <gal/log/log.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/program/base.hpp>

neb::gfx::glsl::attrib::attrib():
	o_(-1),
	o_bind_(-1)
{}
void	neb::gfx::glsl::attrib::init(char const * name, GLuint o_bind)
{
	name_ = name;
	o_bind_ = o_bind;
	
	LOG(lg, neb::gfx::sl, debug) << "attrib " << name_;
	
}
int	neb::gfx::glsl::attrib::locate(std::shared_ptr<neb::gfx::glsl::program::base> p) {
	glBindAttribLocation(p->o_, o_bind_, name_);
	checkerror("glBindAttribLocation");
	
	o_ = glGetAttribLocation(p->o_, name_);
	
	checkerror("glGetAttribLocation");

	/*
	if(o_ == -1)
	{
		printf("could not find attrib '%s'\n", name_);
		exit(0);
	}
	*/
	return o_;
}
void	neb::gfx::glsl::attrib::enable()
{
	LOG(lg, neb::gfx::sl, debug) << "enable attrib " << name_;

	glEnableVertexAttribArray(o_);

	checkerror("glEnableVertexAttribArray");
}
void	neb::gfx::glsl::attrib::disable()
{
	glDisableVertexAttribArray(o_);

	checkerror("glDisableVertexAttribArray");
}

