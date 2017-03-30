
#include "../../../Lib/boost/libs/multi_index/include/boost/multi_index_container.hpp"
#include "../../../Lib/boost/libs/multi_index/include/boost/multi_index/hashed_index.hpp"
#include "../../../Lib/boost/libs/multi_index/include/boost/multi_index/random_access_index.hpp"
#include "../../../Lib/boost/libs/multi_index/include/boost/multi_index/mem_fun.hpp"


namespace Utility {
	template <typename T> 
	using FixedList = boost::multi_index<T,
		index_by<
		random_access<>,
		hashed_unique<const_mem_fun<T, Model::Index, &T::index> >
		>
	>;
			
/*	template <typename T, int ArraySize = 4> 
	class FixedList {
	public:
		using reference = &T;
		using pointer = *T;
		using value = T;

	private:
		// Members
		using Array = std::array<value, ArraySize>;
		using List = std::forward_list<Array>;

		List mData;

		stuct ItemLocation {
			List::iterator item;
			std::size_t pos;
		};

		ItemLocation nextItem;

	public:
		class iterator {
			ItemLocation loc;
		};
	
	};
	*/
}