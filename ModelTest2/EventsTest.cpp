#include "pch.h"
#include "CppUnitTest.h"
#include <string_view>
#include <string>
#include "../model/model.h"
#include "../model/resource/Value.h"
#include "../model/property/Property.h"
#include "../model/property/Map.h"
#include "../model/event/Event.h"
#include "../model/event/Events.h"
#include "../model/event/EventsEditor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<model::time::HourMinute>(const model::time::HourMinute & t) {
	return std::to_wstring(t.hour) + std::wstring{ ':' } +std::to_wstring(t.minute);
}

namespace Events_Details
{
	auto GenerateEvents(model::event::Events & evt) {
		std::vector<model::event::EventHandle> handles;
		handles.reserve(90);
		auto ed = evt.edit();
		for (unsigned int dayValue = 1; dayValue < 11; ++dayValue) {
			for (unsigned int hourValue = 1; hourValue < 10; ++hourValue) {
				auto d = date::year{ 2017 } / date::month{ 1 } / date::day{ dayValue };
				auto handle1 = ed.create(d, model::time::HourMinute{ (unsigned char)dayValue, (unsigned char)hourValue }, model::time::Duration{ 30 }, nullptr);
				handles.push_back(handle1);
			}
		}

		ed.changes_commit();
		return handles;
	}
	

    TEST_CLASS(EventsTest)
    {
    public:
        TEST_METHOD(CreateEventsClass)
		{
			model::event::Events evt;
        }

		TEST_METHOD(Add1EventItem) {
			model::event::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			ed.create(d, model::time::HourMinute{ 12,20 }, model::time::Duration{ 30 }, nullptr);
			ed.changes_commit();
			Assert::AreEqual(evt.size(), (std::size_t)1);
		}

		TEST_METHOD(Add2EventItems) {
			model::event::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			ed.create(d, model::time::HourMinute{ 12,20 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 14,00 }, model::time::Duration{ 30 }, nullptr);

			ed.changes_commit();
			Assert::AreEqual(evt.size(), (std::size_t)2);
		}

		TEST_METHOD(Add2EventItemsSortedCheck) {
			model::event::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			ed.create(d, model::time::HourMinute{ 12,20 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 14,00 }, model::time::Duration{ 30 }, nullptr);

			ed.changes_commit();
			Assert::AreEqual(evt.begin()->start, model::time::HourMinute { 12, 20 });
		}

		TEST_METHOD(Add4EventItemsSortedCheck) {
			model::event::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			ed.create(d, model::time::HourMinute{ 12,20 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 14,00 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 8,00 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 7,00 }, model::time::Duration{ 30 }, nullptr);

			ed.changes_commit();
			Assert::AreEqual(evt.begin()->start, model::time::HourMinute { 7, 0 });
			
			auto last = evt.end() - 1;
			Assert::AreEqual(last->start, model::time::HourMinute{ 14,0 });
		}

		TEST_METHOD(CheckFind) {
			model::event::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			auto handle1 = ed.create(d, model::time::HourMinute{ 12,20 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 14,00 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 8,00 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 7,00 }, model::time::Duration{ 30 }, nullptr);

			ed.changes_commit();
			
			auto foundItem = evt.find(handle1);

			Assert::IsTrue(foundItem != nullptr);
			Assert::AreEqual(foundItem->start, model::time::HourMinute { 12, 20 });
			Assert::IsTrue(evt.has(handle1));
		}

		TEST_METHOD(CheckFind_CannotFind) {
			model::event::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			auto handle1 = ed.create(d, model::time::HourMinute{ 12,20 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 14,00 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 8,00 }, model::time::Duration{ 30 }, nullptr);
			ed.create(d, model::time::HourMinute{ 7,00 }, model::time::Duration{ 30 }, nullptr);

			ed.changes_commit();

			// handle1 to impossible value
			handle1.value = 34;
			auto foundItem = evt.find(handle1);
			Assert::IsTrue(foundItem == nullptr);
		}

		TEST_METHOD(begin_date__end_date) {
			model::event::Events evt;
			auto ed = evt.edit();
			for (unsigned int monthValue = 1; monthValue < 11; ++monthValue) {
				for (unsigned int dayValue = 1; dayValue < 10; ++dayValue) {
					auto d = date::year{ 2017 } / date::month{ monthValue } / date::day{ dayValue };
					auto handle1 = ed.create(d, model::time::HourMinute{ (unsigned char)monthValue, (unsigned char)dayValue }, model::time::Duration{ 30 }, nullptr);
				}
			}

			ed.changes_commit();

			auto start = evt.begin_date(date::year{ 2017 } / 3 / 3);
			auto end = evt.end_date(date::year{ 2017 } / 9 / 9);

			Assert::AreEqual(start->start, model::time::HourMinute{ 3,3 });
			Assert::AreEqual(end->start, model::time::HourMinute{ 10,1 });
		}

		TEST_METHOD(remove) {
			model::event::Events evt;
			auto handles = GenerateEvents(evt);
			Assert::AreEqual(handles.size(), evt.size());

			auto ed = evt.edit(); 
			ed.remove(handles[0]);
			ed.remove(handles[1]);

			ed.changes_commit();
			
			Assert::AreEqual(handles.size() - 2, evt.size());
			Assert::AreEqual(evt.begin()->start, model::time::HourMinute { 1, 3 });
		}

		TEST_METHOD(remove_day) {
			model::event::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit();
			ed.remove_day(date::year{ 2017 } / 1 / 3);

			ed.changes_commit();

			Assert::AreEqual(handles.size() - 9, evt.size());
		}

		TEST_METHOD(change) {
			model::event::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit();
			
			ed.change(*handles.begin(), (model::resource::Value*) 1);
			ed.change(handles[25], (model::resource::Value*) 25);

			ed.changes_commit();

			Assert::AreEqual((int)evt.begin()->value, 1);
			Assert::AreEqual((int)evt.find(handles[25])->value, 25);
		}

		TEST_METHOD(move) {
			model::event::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit();

			auto handle = ed.move(handles[0], date::year(2017) / 12 / 1);
			
			ed.changes_commit();

			Assert::IsNull(evt.find(handles[0]));
			Assert::AreEqual(evt.find(handle)->start, model::time::HourMinute { 1, 1 });
		}

		TEST_METHOD(all_changes_at_once) {
			model::event::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit();

			auto handle0 = ed.move(handles[0], date::year(2017) / 12 / 1);
			ed.remove(handles[1]);
			ed.remove(handles[2]);

			ed.change(handles[3], (model::resource::Value*) 1);
			
			auto d = date::year{ 2017 } / 11 / 1;
			auto handle1 = ed.create(d, model::time::HourMinute{ 12,20 }, model::time::Duration{ 30 }, nullptr);

			ed.changes_commit();

			Assert::IsNull(evt.find(handles[0]));
			Assert::IsNull(evt.find(handles[1]));
			Assert::IsNull(evt.find(handles[2]));
			Assert::AreEqual(evt.find(handle0)->start, model::time::HourMinute { 1, 1 });
			Assert::AreEqual(evt.find(handle1)->start, model::time::HourMinute { 12, 20 });
			Assert::AreEqual((int)evt.find(handles[3])->value, 1);

		}

    };
}