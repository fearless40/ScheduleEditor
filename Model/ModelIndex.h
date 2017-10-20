
#pragma once

#include "Utils/FixedList.h"
using namespace boost::multi_index;

template <class T>
class ModelIndex {

public:



	static const T & Find(Model::Index name)
	{
		auto it = templates.find(name);

		if (it == templates.end())
		{
			throw "Could not find the item specified";
		}
		return *it;

	}

	
	static T Create(Model::Index name)
	{
		// TODO: insert return statement here
		if (templates.find(name) == templates.end()) {
			return T(name);
		}
		else {
			throw "Item already exists in the collection.";
		}
	}

	static void Save(T && pt)
	{
		auto item = templates.find(pt.index());
		if (item == templates.end()) {
			templates.insert(std::move(pt));
		}
		else {
			templates.replace(item, std::move(pt));
		}
	}

	static T Edit(const T & pt)
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