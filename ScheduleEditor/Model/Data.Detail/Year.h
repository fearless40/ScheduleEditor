#pragma once 

namespace Model::Data::Detail {
	
	/// Holds the months in a year
	class Year {
		date::year mYear;
		std::array<Month, 12> mMonths;

	public:
		Year() = default;
		Year(date::year yr) : mYear(yr) {};
		Year(const Year & y) = default;
		Year(Year && y) = default;

		Year & operator = (const Year & y) = default;

		class Editor : public ModifierT<Year> {
		public:
			Editor(Year & yr) : ModifierT(yr) {};
			~Editor() {}
			Days * add(date::month mt);
			void	remove(date::month mt);
			void	reserve(std::size_t sz);
		};

		// Event interface helper
		const Event * event_find(EventHandle evt) const;

		// Day finder
		const Days * find(date::month m) const;
		bool has(date::month m) const;

		// Information
		date::year	year() const noexcept;
		date::month	first() const noexcept;
		date::month last() const noexcept;
		//date::months span() const noexcept;
		
		// Interator interface
		auto begin() const;
		auto end() const;

		// Edit interface
		Editor edit() const;

		// Lockable interface
		bool lock(LockType type);
		void unlock(LockType type);

		// Sorting interface
		// In this class does nothing but if the implementation changes it may switch to doing something!
		void sort(); 
	};


	// Operators needed for std::algorythm
	bool operator < (const Year & m1, const Year & m2) {
		return m1.year() < m2.year();
	}

	bool operator < (const Year & m1, const date::year & y) {
		return m1.year() < y;
	}

	bool operator < (const date::year & y, const Year & m1) {
		return y < m1.year();
	}
}