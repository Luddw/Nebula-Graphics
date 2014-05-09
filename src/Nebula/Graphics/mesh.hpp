#ifndef __GLUTPP_MESH_H__
#define __GLUTPP_MESH_H__

#include <map>

#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

/*
#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>
*/

#include <Nebula/Math/geo/polyhedron.hpp>
#include <Nebula/config.hpp>
#include <Nebula/shape/desc.hpp>
#include <Nebula/Graphics/material.hpp>


namespace Neb {
	struct file_header {
		int len_vertices_;
		int len_indices_;
	};
	struct vertex {
		//void		print();

		physx::PxVec3	position;
		physx::PxVec3	normal;
		physx::PxVec2	texcoor;
	};
	class mesh {
		public:
			mesh();
			void				save(char const *);
			void				load(char const *);
			void				construct(math::geo::polyhedron*);

			// draw data
			file_header			fh_;
			Neb::vertex*			vertices_;
			GLushort*			indices_;
	};
}

#endif