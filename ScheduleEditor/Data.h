#pragma once



namespace Model::Data {
	
	bool			hasData(const Model::Resources::Resource * res);
	ResourceData &	Get(const Model::Resources::Resource * res);
	ResourceData &	Create(const Model::Resources::Resource * res);

	/// Triggers an event changed signal
	void			Save(const Model::Data::Range * changed);
	
	/// Holds a group of Ranges. Allowing discontinous data to be stored
	/// It is associated with only one type of resource (the mOwner)
	class ResourceData {
		Index mIndex;

		Model::Resources::Resource * mOwner;



	};
}