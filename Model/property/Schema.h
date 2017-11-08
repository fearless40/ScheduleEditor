#pragma once

#include <vector>
#include "Property.h"

namespace model::property {
	
	

	class Schema {
	public:
		using PropertyDefinitions = std::vector<Definition>;

		Schema();
		Schema(const Schema & pt) = default;
		Schema(Schema && pt) = default;
		Schema(Index index) : mIndex(index) {}
		Schema & operator = (const Schema & pt) = default;

		model::Index index() const { return mIndex; }

		auto cbegin() const { return mIndex.cbegin(); }
		auto cend() const { return mIndex.cend(); }

		auto begin() { return mIndex.begin(); }
		auto end() { return mIndex.end(); }

		void string_add(Key name, model::string defaultvalue, bool mandatory = false);
		void long_add(Key name, long defaultvalue, long min, long max, bool mandatory = false);
		void double_add(Key name, double defaultvalue, double min, double max, bool mandatory = false);
		void bool_add(Key name, bool defaultvalue, bool mandatory = false);
		
		void remove(Key name);

		/// Validates a propertymap and returns true if the propertymap matches the definition in the template
		bool validate(const Map & map) const;

		/// Makes the PropertyMap valid by adding memebers and changing values if out of range
		void make_valid(Map & map) const;

	

	private:

		PropertyDefinitions::iterator find(Key index);

		PropertyDefinitions mDefs;

		// Used to look it up 
		model::Index mIndex;

			
	};


}
