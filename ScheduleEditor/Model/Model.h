#pragma once

namespace Model {
	using Index = std::string;


	template <class BaseType, class Owner> 
	class SmartHandle {
	public:
		using type = BaseType;
		
	protected:
		Owner::index_type mIndex;
		const Owner & owner;
		

	public:
		const type  & operator * () const {
			return owner.lookup(mIndex);
		}

		type  & operator * () {
			return owner.lookup(mIndex);
		}

		operator (const type &) () const {
			return owner.lookup(mIndex);
		}

		operator (type &) () {
			return owner.lookup(mIndex);
		}


	};

}