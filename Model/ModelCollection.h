
#pragma once

#include "Model.h"
#include <utility>
#include <unordered_map>
//#include <boost\container\flat_map.hpp>
//using namespace boost::multi_index;

namespace Model {

	template<typename T>
	Model::IndexConst getIndex(const T & t) {
		return t.index();
	}

	template<typename T>
	Model::IndexConst getIndex(const std::unique_ptr<T> & t) {
		return t->index();
	}
	
	
	Model::IndexConst getIndex(Model::IndexConst idx) {
		return idx;
	}

	struct ModelCollection_TagVector {};
	struct ModelCollection_TagUnordered {};

	template <class T, class tag = ModelCollection_TagUnordered >
	class ModelCollection {
		using Set = std::unordered_map<Model::Index, T>;

		Set mItems;

	public:
		const T * find(Model::IndexConst idx) const {
			auto item = mItems.find(Model::Index{ idx });
			if (item != mItems.end()) {
				return &item->second;
			}
			return nullptr;
		}

		bool save(T && value) {
			[[maybe_unused]] auto[where, inserted] = mItems.insert(
			std::pair<Model::IndexConst, T &&>{ Model::getIndex(value), std::move(value) });
			return inserted;
		}

		bool save(const T & value) {
			[[maybe_unused]]auto[where, inserted] = mItems.insert(
			std::pair<Model::IndexConst, const T &>{ Model::getIndex(value), value });
			return inserted;
		}

		void erase(Model::IndexConst idx) {
			mItems.erase(Model::Index{ idx });
		}

		void save(std::vector<T> && values) {
			mItems.reserve(values.size() + mItems.size());
			for (auto && x : values) {
				mItems.insert(
					std::pair<Model::IndexConst, T &&>{ Model::getIndex(x), std::move(x) });
			}
		}

		const std::vector<Model::IndexConst> enumerate_indexs() const {
			std::vector<Model::IndexConst> values{ mItems.size() };
			std::transform(mItems.begin(), mItems.end(), std::back_inserter(values),
				[](auto & x) { return getIndex(x.second); });
			return values;
		}
	};

	template <class T>
	class ModelCollection<T, ModelCollection_TagVector>{

		//using Set = boost::container::flat_map<Model::Index,std::unique_ptr<T>>;
		using Set = std::vector<std::unique_ptr<T>>;

		Set mItems;

		void _push_back(T && item) {
			mItems.push_back(std::move(std::make_unique<T>(item)));
		}

		auto _find(Model::IndexConst idx) const {
			return std::lower_bound(mItems.begin(), mItems.end(), idx,
				[](auto && a, auto && b) {
				return getIndex(a) < getIndex(b);
			});
		}

		void _sort() {
			std::sort(mItems.begin(), mItems.end());
		}


	public:
		const T * find(Model::IndexConst idx) const {
			
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

		void erase(Model::IndexConst idx) {
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

		const std::vector<Model::IndexConst> enumerate_indexs() const {
			std::vector<Model::IndexConst> values{ mItems.size() };
			std::transform(mItems.begin(), mItems.end(), std::back_inserter{ values },
				[](auto & x) { return x->get()->index(); });
			return values;
		}

	};
	/*
	// first == true if the item is in the collection
	[[nodiscard]] static std::pair<bool,const T &> Find(Model::Index name)
	{
		auto it = templates.find(name);

		if (it == templates.end())
		{
			return { false, T{Model::NullIndex} };
		}
		return { true,*it };
	}

	// first == true if the item does not exist in the collection
	[[nodiscard]] static std::pair<bool,T> Create(Model::Index name)
	{
		// TODO: insert return statement here
		if (templates.find(name) == templates.end()) {
			return { true,T{name } };
		};
		return { false, T{Model::NullIndex} };
	}

	// False if the item was not inserted. True otherwise
	static bool Save(T && pt)
	{
		if (pt.index() == Model::NullIndex)
			return false;
		auto item = templates.find(pt.index());
		if (item == templates.end()) {
			templates.insert(std::move(pt));
		}
		else {
			templates.replace(item, std::move(pt));
		}
		return true;
	}

	[[nodiscard]] static T Edit(const T & pt)
	{
		T ret(pt);
		return ret;
	}

	static std::vector<Model::Index> Indexs_GetAll()
	{
		std::vector<Model::Index> ret;
		std::for_each(templates.begin(), templates.end(), [&ret](auto & k) { ret.push_back(k.index()); });
		return ret;
	}
private:


	static Utility::FixedList<T> templates;

};

template <class T>
Utility::FixedList<T> ModelIndex<T>::templates;
*/
}