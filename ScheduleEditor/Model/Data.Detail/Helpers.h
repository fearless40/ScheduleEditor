#pragma once

namespace Model::Data::Detail {
	enum class LockType {
		Read,
		Write
	};
	
	struct NoLock {};
	struct YesLock {};
	
	template<typename LockAble, typename ShouldLock = YesLock>
	class ModifierT {};

	template<typename LockAble>
	class ModifierT<LockAble, YesLock> {
	protected:
		bool mIsValid{ false };
		bool mChanged{ false };
		LockType locktype;
		LockAble & owner;
	public:
		ModifierT(LockAble & t, LockType lt = LockType::Write) : owner(t), locktype(lt) {
			mIsValid = owner.lock(lt);
		}

		~ModifierT() {
			if (mIsValid && mChanged) {
				owner.sort();
			}
			if (mIsValid)
			{
				owner.unlock(locktype);
			}
		}
		bool isValid() const { return mIsValid; }
		bool hasChanged() const { return mChanged; }
	};

	template<typename LockAble>
	class ModifierT<LockAble, NoLock> {
		bool mChanged{ false; }
		LockAble & owner;
	public:
		ModifierT(LockAble & t, LockType lt = LockType::Write) : owner(t) {
			
		}
		~ModifierT() {
			
		}
		bool isValid() const { return true; }
		bool hasChanged() const { return mChanged; }
	};

	class Years;
	class Months;
	class Days;
	class DayEvents;
}