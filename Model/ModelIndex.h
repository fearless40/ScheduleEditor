
#pragma once
#include <utility>
#include <boost\container\flat_map.hpp>
//using namespace boost::multi_index;

template <class T>
class ModelIndex {
	template<typename T>
	struct less {
		bool operator () (const T & lhs, const T & rhs) {
			return lhs.index() < rhs.index();
		}
	};

	using Set = boost::container::flat_map<Model::Index,std::unique_ptr<T>>;

	Set mItems;
public:
	const T * find(Model::IndexConst idx) {
		if (auto it = mItems.find(idx); it != mItems.end()) {
			return it->second->get();
		}
		else {
			return nullptr;
		}
	}

	bool save(T && value) {
		auto new_value = std::make_unique<T>(std::move(value));
		mItems[new_value->index()] = std::move(new_value);
	}

	bool save(std::vector<T> && values) {
		mItems.reserve(values.size() + mItems.size());
		for (auto & x : values) {
			save(std::move(x));
		}
	}

	const std::vector<Model::IndexConst> enumerate_indexs() {
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