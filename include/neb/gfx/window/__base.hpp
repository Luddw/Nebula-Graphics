#ifndef __GRU_WINDOW___BASE_H__
#define __GRU_WINDOW___BASE_H__

#include <neb/core/itf/shared.hpp>

namespace neb {
	namespace gfx {
		namespace window {
			class __base: virtual public neb::itf::shared
			{
				public:
					virtual void		render() = 0;
			};
		}
	}
}


#endif










