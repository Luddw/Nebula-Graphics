#ifndef NEBULA_UTIL_PARENT_HH
#define NEBULA_UTIL_PARENT_HH

#include <Nebula/Types.hh>
#include <Nebula/Util/Map.hh>
#include <Nebula/Util/WrapperTyped.hh>

namespace Neb {
	namespace Util {
		template<class T> class Parent: virtual public Neb::Util::Shared {
			public:
				typedef T				__type_type;
				typedef std::shared_ptr<T>		__shared_type;
				typedef Neb::WrapperTyped<T>		__wrapper_type;
				typedef typename Neb::Map<T>		map_type;

				Parent();

				void					insert(__shared_type s);

				__shared_type				get(Neb::Util::index_type i) {
					return map_.find(i);
				}
				void					release(Neb::Util::index_type i) {
					auto me = std::dynamic_pointer_cast< Neb::Util::Parent<T> >(shared_from_this());
					
					boost::thread t(boost::bind(
							&Neb::Util::Parent<T>::release_thread,
							me,
							i
							));
					
					t.detach();
				}
			private:
				void					release_thread(Neb::Util::index_type i) {
					map_.release(i);
				}
			public:
				void					clear() {
					map_.clear();
				}

			
				map_type				map_;
		};
	}
}

#endif



