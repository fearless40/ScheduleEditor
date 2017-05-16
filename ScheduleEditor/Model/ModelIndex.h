
#include "../Utils/FixedList.h"

template <class T>
class ModelIndex {
private:
	static Utility::FixedList<T> templates;

public:



	static const T & Find(Model::Index name)
	{
		// TODO: insert return statement here
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
		T pt(name);
		if (templates.find(name) == templates.end()) {
			return pt;
		}
		else {
			throw "Item already exists in the collection.";
		}
	}

	static void Save(T & pt)
	{
		auto item = templates.find(pt.index());
		if (item == templates.end()) {
			templates.insert(pt);
		}
		else {
			templates.replace(item, pt);
		}
	}

	static T Edit(const T & pt)
	{
		T ret(pt);
		return ret;
	}

	static std::vector<Model::Index> GetAllNames()
	{
		std::vector<Model::Index> ret;
		std::for_each(templates.begin(), templates.end(), [&ret](auto & k) { ret.push_back(k.index()); });
		return ret;
	}

};

template <class T>
Utility::FixedList<T> ModelIndex<T>::templates;