#pragma once
#include <boost\iterator\indirect_iterator.hpp>
#include <boost\signals2.hpp>
#include "Model.h"
#include "Resource.h"
#include "property\Schema.h"
#include "property\InheritPropertyMap.h"



namespace model::resource  {
	
	/// Owns a group of resources and defines the type of resource
	/// Owned by: self, obtain by using static functions
	class Type : public model::property::InheritPropertyMap
	{
	public:
		using IndirectAdaptor = boost::indirect_iterator<std::vector<std::unique_ptr<Value>>::iterator, Value &>;
		using ConstIndirectAdaptor = boost::indirect_iterator<std::vector<std::unique_ptr<Value>>::const_iterator, const Value &>;
		using OnChangeSignal = boost::signals2::signal< void(std::shared_ptr<Value> oldValue, const Value const * changedValue) >;
		using OnAddSignal = boost::signals2::signal< void(const Value const * newResource) >;
		using OnRemoveSignal = boost::signals2::signal< void(std::shared_ptr<Value> removedResource)>;


		model::IndexConst index() const { return mIndex;  }


		auto cbegin() const { return ConstIndirectAdaptor(mItems.cbegin()); }
		auto cend() const { return ConstIndirectAdaptor(mItems.cend());  }

		auto begin() { return IndirectAdaptor(mItems.begin()); }
		auto end() { return IndirectAdaptor(mItems.end()); }

		auto begin() const { return cbegin(); }
		auto end() const { return cend(); }

		size_t size() const { return mItems.size(); }

		Value & create();
		Value & create(model::property::Map && map);
		Value & load(ResourceID id, bool isDeleted, model::property::Map && map);
		void remove(const Value & r);
		void change(const Value & r);
		

		/// Set a new PropertyTemplate to the class.
		void mapconstraint(const model::property::Schema & propt) {
			mPropTemp = &propt;
		}
		
		const model::property::Schema * mapconstraint() const {
			return mPropTemp;
		}

		//const auto & properties() const { return mProperties; }
		//auto & properties() { return mProperties; }

		Type();
		~Type();
		Type(const model::IndexConst index);
		Type(const model::IndexConst index, model::property::Schema& pTemplate); 
		Type(Type &&) = default;
		Type & operator = (Type &&) = default;

		auto onChange(OnChangeSignal::slot_type slot) {
			return _onChange.connect(slot);
		}

		void onChangeDisconnect(boost::signals2::connection c) {
			_onChange.disconnect(c);
		}

		auto onAdd(OnAddSignal::slot_type slot) {
			return _onAdd.connect(slot);
		}

		void onAddDisconnect(boost::signals2::connection c) {
			_onAdd.disconnect(c);
		}
		auto onRemove(OnRemoveSignal::slot_type slot) {
			return _onRemove.connect(slot);
		}

		void onRemoveDisconnect(boost::signals2::connection c) {
			_onRemove.disconnect(c);
		}


	private:

		std::vector<std::unique_ptr<Value>>::iterator _find(const Value & r);
		//std::vector<std::unique_ptr<Resource>>::iterator _find(const Resource & r);

		model::Index mIndex{ model::NullIndex };
		
		// Todo: determine if having a vector here is better or a list. A list allows direct memory access without having to worry about a resource being moved.
		// The vector is much faster iteration at the cost of greater difficluty coding as it is safe for reading at the same time but not editing. It would therefore
		// require mutexs and such to get it to work.
		std::vector<std::unique_ptr<Value>> mItems;

		/// Optional holds a pointer to a PropertyTemplate. Allows one to apply a template to each of the sub resource
		/// included in the group
		const model::property::Schema * mPropTemp{ nullptr };
		
		ResourceID mNextID{ 1 };

		ResourceID getNextID();

		OnChangeSignal _onChange;
		OnAddSignal _onAdd;
		OnRemoveSignal _onRemove;
	};

	
}