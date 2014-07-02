#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>

#include <gal/log/log.hpp>

#include <neb/debug.hh>

#include <neb/app/Base.hh>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/gfx/glsl/attrib.hh>

#include <neb/free.hh>

void			neb::draw_quad(
		sp::shared_ptr<neb::glsl::program> p,
		float x,
		float y,
		float w,
		float h,
		neb::Color::color<float> color) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;


	//GLint uniform_color = glGetUniformLocation(program, "color");
	//GLint attribute_coord = glGetAttribLocation(program, "coord");
	/*
	// vbo
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	GLfloat box[4][4] = 
	{
	{x,     -y    , 0, 0},
	{x + w, -y    , 1, 0},
	{x,     -y - h, 0, 1},
	{x + w, -y - h, 1, 1},
	};

	glUniform4fv(uniform_color, 1, color);


	glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	*/

	glUseProgram(0);

	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glColor4fv(color);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glLoadIdentity();

		glBegin(GL_QUADS);

		glVertex2f(x,  y);
		glVertex2f(x+w,y);
		glVertex2f(x+w,y+h);
		glVertex2f(x,  y+h);

		glEnd();
	}
	glPopMatrix();

}
void		neb::draw_text(
		sp::shared_ptr<neb::glsl::program> p,
		float x, float y, float sx, float sy, neb::Color::color<float> color, ::std::string text)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;

	const char * c;

	//auto p = neb::app::base::global()->use_program(neb::program_name::e::TEXT);

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug)
		<< ::std::setw(8) << x
		<< ::std::setw(8) << y
		<< text;

	// face
	FT_Face& face  = neb::app::base::global()->face_;
	


	FT_Set_Pixel_Sizes(face, 0, 48);

	if(FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		printf("Could not load character 'X'\n");
		exit(1);
	}

	FT_GlyphSlot g = face->glyph;


	/*
	   GLint uniform_tex = glGetUniformLocation(program, "tex");
	   GLint uniform_color = glGetUniformLocation(program, "color");
	   GLint attribute_coord = glGetAttribLocation(program, "coord");

	   if(uniform_tex == -1)
	   {
	   printf("tex not found\n");
	//exit(0);
	}
	if(uniform_color == -1)
	{
	printf("color not found\n");
	exit(0);
	}
	if(attribute_coord == -1)
	{
	printf("coord not found\n");
	exit(0);
	}
	 */

	//printf("tex   = %i\n",uniform_tex);
	//printf("color = %i\n",uniform_color);
	//printf("coord = %i\n",attribute_coord);

	// color
	p->get_uniform_scalar("font_color")->load(color);

	// texture
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	p->get_uniform_scalar("tex")->load(0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	auto attrib_coord = p->get_attrib(neb::attrib_name::e::COOR);

	// vbo
	GLuint vbo;
	glGenBuffers(1, &vbo);
	attrib_coord->enable();//glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// this line fucks everything up -- not anymore! needed to bind attrib location using layout in shader
	glVertexAttribPointer(attrib_coord->o_, 4, GL_FLOAT, GL_FALSE, 0, 0);




	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);




	for(c = text.c_str(); *c; c++) {
		if(FT_Load_Char(face, *c, FT_LOAD_RENDER)) continue;

		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_ALPHA,
				g->bitmap.width,
				g->bitmap.rows,
				0,
				GL_ALPHA,
				GL_UNSIGNED_BYTE,
				g->bitmap.buffer
			    );

		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		GLfloat box[4][4] = 
		{
			{x2,     -y2    , 0, 0},
			{x2 + w, -y2    , 1, 0},
			{x2,     -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};

		//printf("glyph %i %i %i\n",g->bitmap.width,g->bitmap.rows,(int)sizeof box);
		//printf("%6.3f %6.3f %6.3f %6.3f\n", x2, y2, w, h);
		//print(g->bitmap.buffer, g->bitmap.width, g->bitmap.rows);


		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (g->advance.x >> 6) * sx;
		y += (g->advance.y >> 6) * sy;
	}


	checkerror("unknown");


	attrib_coord->disable();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}
int		isExtensionSupported(const char *extension) {
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;

	/* Extension names should not have spaces. */
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;
	extensions = glGetString(GL_EXTENSIONS);
	/* It takes a bit of care to be fool-proof about parsing the
	   OpenGL extensions string. Don't be fooled by sub-strings,
	   etc. */
	start = extensions;
	for (;;)
	{
		//printf("%s\n",start);

		where = (GLubyte *) strstr((const char *) start, extension);
		if (!where)
			break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return 1;
		start = terminator;
	}
	return 0;
}
int isSupported(const char *extension) {
	if(isExtensionSupported(extension))
	{
		printf("%s is supported\n",extension);
		return 1;
	}

	printf("%s is not supported\n",extension);
	exit(0);

}
void CheckExt()
{
	isSupported("GL_ARB_vertex_shader");
	isSupported("GL_ARB_fragment_shader");
}


void	checkerror(char const * msg) {

	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		unsigned char const * str = gluErrorString(err);
		printf("%s: %s\n",msg,str);
		throw 0;
	}
}
bool	isGLError() {
	return (glGetError() != GL_NO_ERROR);
}


