#pragma once

namespace Model::Data::Detail {
	
	/// Holds the events in a Day
	class Day {
		date::day mDay;
		std::vector<Model::Data::Detail::Event> mEvents;

	public:

		class Editor : public ModifierT<Day> {
		public:
			Editor(Day & d) : ModifierT(d) {}
			Model::Data::Detail::Event * add(unsigned short minutes_since_midnight);
			void remove(EventHandle evt);
			void reserve(std::size_t sz);
		};

		// Event find interface
		const Event * event_find(EventHandle evt) const;

		// Finder
		const Event * find(EventHandle evt) const;
		bool  has(EventHandle evt) const;

		// Informational 
		date::day	day() const noexcept;
		EventHandle first() const;
		EventHandle last() const;
		
		// Interator interface
		auto begin() const { return mEvents.cbegin(); }
		auto end() const { return mEvents.cend(); }

		// Edit interface
		Editor edit() const;

		// Lockable interface
		bool lock(LockType type);
		void unlock(LockType type);

		// Sorting interface
		void sort();

	};
}