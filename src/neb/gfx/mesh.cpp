#include <iostream>
#include <iomanip>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <gal/log/log.hpp>

#include <neb/core/math/geo/polyhedron.hh>
#include <neb/core/util/debug.hpp>

#include <neb/gfx/core/mesh.hh>
#include <neb/gfx/util/log.hpp>

neb::gfx::mesh::mesh() {
	printf("%s\n",__PRETTY_FUNCTION__);
}
neb::gfx::mesh::~mesh() {
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::gfx::mesh::construct(math::geo::polyhedron* poly) {

	auto tris = poly->triangles();
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	LOG(lg, neb::gfx::sl, info) << "tris: " << tris.size();


	
	for(size_t i = 0; i < (3 * tris.size()); ++i) {
		indices_.push_back(i);
	}
	
	
	for(auto t : tris) {
		assert(t);
		for(int i = 0; i < 3; ++i) {
			assert(t->v_[i]);
			vertices_.push_back(*(t->v_[i]));
		}
	}

	LOG(lg, neb::gfx::sl, info) << "vertices: " << vertices_.size();
	LOG(lg, neb::gfx::sl, info) << "indices:  " << indices_.size();


}
void		neb::gfx::mesh::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	/*std::string filename = std::string(GLUTPP_OBJECT_DIR) + "/" + name;
	
	FILE * fp;
	
	std::cout << "load file " << filename << std::endl;

	fp = fopen(filename.c_str(), "rb");

	if (fp <= 0) {
		perror("fopen");
		abort();
	}*/
	
	ar & vertices_;
	ar & indices_;
	
	
	LOG(lg, neb::gfx::sl, info) << "vertices: " << vertices_.size();
	LOG(lg, neb::gfx::sl, info) << "indices:  " << indices_.size();

}
void		neb::gfx::mesh::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	ar & vertices_;
	ar & indices_;
	
	
	LOG(lg, neb::gfx::sl, info) << "vertices: " << vertices_.size();
	LOG(lg, neb::gfx::sl, info) << "indices:  " << indices_.size();

}
void		neb::gfx::mesh::print(int sl) {
	LOG(lg, neb::gfx::sl, (severity_level)sl) << "mesh";

	for(auto v : vertices_) {
		v.print(sl);
	}	
}





