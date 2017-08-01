
namespace Model::Data::Detail {

	using namespace Model;

	/// Event interface into the heirarchy of Years->Months->Days->DayEvents
	class Events {
		std::unique_ptr<Years> mYears;
		const Data::DataStore &  mOwner;

	public:
		Events(Data::DataStore & owner);
		~Events();

		// Const Interface
		const Event * event_find(EventHandle evt) const;


		// Modification interface
		EventHandle		add(Model::Data::Event evt);
		void			remove(EventHandle eHandle);
		EventHandle		change(EventHandle eHandle, Model::Data::Event evt)


	};
}
