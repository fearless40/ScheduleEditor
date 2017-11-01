
#pragma once

#include "model.h"
#include <utility>
#include <unordered_map>
#include <boost\signals2.hpp>
//#include <boost\container\flat_map.hpp>
//using namespace boost::multi_index;


namespace model {

	template<typename T>
	model::IndexConst getIndex(const T & t) {
		return t.index();
	}

	template<typename T>
	model::IndexConst getIndex(const std::unique_ptr<T> & t) {
		return t->index();
	}
	
	
	model::IndexConst getIndex(model::IndexConst idx) {
		return idx;
	}

	struct modelCollection_TagVector {};
	struct modelCollection_TagUnordered {};

	template <class T, class tag = modelCollection_TagUnordered >
	class IndexedCollection {
		using Set = std::unordered_map<model::Index, T>;

		Set mItems;

	public:
		using OnAddSignal = boost::signals2::signal<void(T*)>;
		using OnRemoveSignal = boost::signals2::signal<void(std::shared_ptr<T> oldValue)>;

		auto begin() const { return mItems.begin(); }
		auto end() const { return mItems.end(); }
		auto size() const { return mItems.size(); }

		const T * find(model::IndexConst idx) const {
			auto item = mItems.find(model::Index{ idx });
			if (item != mItems.end()) {
				return &item->second;
			}
			return nullptr;
		}

		bool insert(T && value) {
			auto[it, inserted] = mItems.insert(
			std::pair<model::IndexConst, T &&>{ model::getIndex(value), std::move(value) });
			if (inserted) {
				_onAdd(&it->second);
			}
			return inserted;
		}

		bool insert(const T & value) {
			auto[it, inserted] = mItems.insert(
			std::pair<model::IndexConst, const T &>{ model::getIndex(value), value });
			if (inserted) {
				_onAdd(&it->second);
			}
			return inserted;
		}

		void erase(model::IndexConst idx) {
			auto it = mItems.find(model::Index{ idx });
			if ( it != mItems.end()) {
				std::shared_ptr<T> old = std::make_shared<T>(it->second);
				mItems.erase(it);
				_onRemove(old);
			}
		}

		void insert(std::vector<T> && values) {
			mItems.reserve(values.size() + mItems.size());
			for (auto && x : values) {
				mItems.insert(
					std::pair<model::IndexConst, T &&>{ model::getIndex(x), std::move(x) });
			}
		}

		const std::vector<model::IndexConst> enumerate_indexs() const {
			std::vector<model::IndexConst> values{ mItems.size() };
			std::transform(mItems.begin(), mItems.end(), std::back_inserter(values),
				[](auto & x) { return getIndex(x.second); });
			return values;
		}

		auto onAdd(typename OnAddSignal::slot_type t) {
			return _onAdd.connect(t);
		}

		void onAddDisconnect(boost::signals2::connection c) {
			_onAdd.disconnect(c);
		}

		auto onRemove(typename OnAddSignal::slot_type t) {
			return _onRemove.connect(t);
		}

		void onRemoveDisconnect(boost::signals2::connection c) {
			_onRemove.disconnect(c);
		}


	protected:
		OnAddSignal _onAdd;
		OnRemoveSignal _onRemove;
	};

	template <class T>
	class modelCollection<T, modelCollection_TagVector>{

		//using Set = boost::container::flat_map<model::Index,std::unique_ptr<T>>;
		using Set = std::vector<std::unique_ptr<T>>;

		Set mItems;

		void _push_back(T && item) {
			mItems.push_back(std::move(std::make_unique<T>(item)));
		}

		auto _find(model::IndexConst idx) const {
			return std::lower_bound(mItems.begin(), mItems.end(), idx,
				[](auto && a, auto && b) {
				return getIndex(a) < getIndex(b);
			});
		}

		void _sort() {
			std::sort(mItems.begin(), mItems.end());
		}


	public:
		const T * find(model::IndexConst idx) const {
			
			if (const auto it = _find(idx); it != mItems.end() && getIndex(*it) == idx) {
				return it->get();
			}
			return nullptr;
		}

		bool save(T && value) {
			_push_back(std::move(value));
			_sort();
			return true;
		}

		bool save(const T & value) {
			mItems.push_back(std::make_unique<T>(value));
			_sort();
			return true;
		}

		void erase(model::IndexConst idx) {
			mItems.erase(_find(idx));
			_sort();
		}

		void save(std::vector<T> && values) {
			mItems.reserve(values.size() + mItems.size());
			for (auto & x : values) {
				_push_back(std::move(x));
			}
			_sort();
		}

		const std::vector<model::IndexConst> enumerate_indexs() const {
			std::vector<model::IndexConst> values{ mItems.size() };
			std::transform(mItems.begin(), mItems.end(), std::back_inserter{ values },
				[](auto & x) { return x->get()->index(); });
			return values;
		}

	};
}