#ifndef NEBULA_TYPED_HPP
#define NEBULA_TYPED_HPP

#include <boost/serialization/split_member.hpp>

namespace Neb {
	/** @brief Typed */
	class Typed {
		public:
			/** @brief Destructor */
			virtual ~Typed() {}
			/** @brief Hash Code */
			long int &		hash_code() { return hash_code_; }
		private:
			/** @brief Hash Code */
			static long int		hash_code_;
	};
	/** @brief Factory */
	template<class T> class Factory {
		public:
			typedef void* (*allocptr)();
			
			Factory() {}
			virtual ~Factory() = 0;
			
			void*					alloc(long hash_code) {
				auto it = map_.find(hash_code);
				if(it == map_.cend()) {
					throw 0;
				} else {
					return (*(it->second))();
				}
			}
			
			static boost::shared_ptr< Factory<T> >		global() {
				if(!global_) {
					throw 0;
				}
				return global_;
			};
		private:
			static boost::shared_ptr< Factory<T> >		global_;
			static std::map<long int, allocptr>		map_;
	};
	/** @brief WrapperTyped */
	template<class T> class WrapperTyped {
		public:
			/** @brief Destructor */
			virtual ~WrapperTyped() {}
			/** @brief Serialize */
			template<class Archive> void		load(Archive & ar, unsigned int const & version) {
				long int hash_code;
				ar >> boost::serialization::make_nvp("hash_code", hash_code);
				ptr_.reset((T*)Neb::Factory<T>::global()->alloc(hash_code));
				ar >> boost::serialization::make_nvp("object", *ptr_);
			}
			template<class Archive> void		save(Archive & ar, unsigned int const & version) const {
				ar << boost::serialization::make_nvp("hash_code", ptr_->hash_code());
				ar << boost::serialization::make_nvp("object", *ptr_);
			}
			BOOST_SERIALIZATION_SPLIT_MEMBER();
		public:
			/** @brief Object */
			boost::shared_ptr<T>			ptr_;
	};
}

#endif


