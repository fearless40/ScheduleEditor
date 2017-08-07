#pragma once

namespace Model::Data::Detail {
	
	/// Holds the days in a Month
	class Month {
		date::month mMonth{ 0 };
		std::vector<Day> mDays;

	public:
		Month() = default;
		Month(date::month m) : mMonth(m) {};
		Month(Month && m) = default;
		Month(const Month & m) = default;
		Month & operator = (const Month & m) = default;


		class Editor : public ModifierT<Month> {
		public:
			Editor(Month & m) : ModifierT(m) {}
			Day * add(date::day d);
			void	remove(date::day d);
			void	reserve(std::size_t sz);
		};

		// Event helper
		const Event * event_find(EventHandle evt) const;

		// Day finder
		const Day * find(date::day d) const;
		bool  has(date::day d) const;

		// Informational 
		date::month month() const noexcept;
		date::day	first() const;
		date::day	last()	const;
		//date::days	span() const;

		// Interator interface
		auto begin() const;
		auto end() const;
		
		// Edit interface
		Editor edit() const;

		// Lockable interface
		bool lock(LockType type);
		void unlock(LockType type);

		// Sorting interface
		void sort();
	};
}