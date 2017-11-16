#include "pch.h"
#include <memory>
#include <algorithm>

#include "model.h"
#include "property\Schema.h"
#include "Resource.h"
#include "Value.h"
#include "Type.h"

using namespace model::resource;
namespace model::resource {


	// Kept for uniqueptr
	Type::Type() {};
	Type::Type(const model::IndexConst index) : mIndex(index) {};
	Type::Type(const model::IndexConst index, model::property::Schema & pTemplate) : mIndex(index), mPropTemp(&pTemplate) { }
	Type::~Type() {};

	Value & Type::create()
	{
		auto res = std::make_unique<Value>(*this, getNextID());
		mItems.push_back(std::move(res));
		_onAdd(mItems.back().get());
		return *mItems.back();
	}

	Value & Type::create(model::property::Map && map)
	{
		auto res = std::make_unique<Value>(*this, getNextID(), std::move(map));
		mItems.push_back(std::move(res));
		_onAdd(mItems.back().get());
		return *mItems.back();
	}

	Value & Type::load(ResourceID id, bool isDeleted, model::property::Map && map)
	{
		auto res = std::make_unique<Value>(*this, id, std::move(map));
		if (id >= mNextID) {
			mNextID = id + 1;
		}
		if (isDeleted) res->markAsDeleted();
		mItems.push_back(std::move(res));
		_onAdd(mItems.back().get());
		return *mItems.back();
	}

	void Type::remove(const Value & r)
	{
		if (auto it = _find(r); it != mItems.end()) {
			std::shared_ptr<Value> old = std::move(*it);
			mItems.erase(it);
			_onRemove(old);
		}

	}

	void Type::change(const Value & r)
	{
		auto item = _find(r);
		if (item == mItems.end()) return;
		std::shared_ptr<Value> oldValue = std::make_shared<Value>( *item->get());
		(*item)->copy_values(r);
		_onChange(oldValue, item->get());
	}


	std::vector<std::unique_ptr<Value>>::iterator Type::_find(const Value & r)
	{
		if (&(r.resource_type()) != this) {
			return mItems.end();
		}

		return std::find_if(mItems.begin(), mItems.end(), [&](const auto & v) {
			if (v->id() == r.id()) {
				return true;
			}
			else {
				return false;
			}
		});

		
	}

	ResourceID Type::getNextID()
	{
		auto ret = mNextID;
		++mNextID;
		return ret;
	}




}