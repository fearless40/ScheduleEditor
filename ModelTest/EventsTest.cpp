#include "pch.h"
#include "CppUnitTest.h"
#include "../Model/Model.h"
#include "../Model/Resources.h"
#include "../Model/Properties.h"
#include "../Model/Properties.PropertyMap.h"
#include "../Model/Data.Event.h"
#include "../Model/Data.Detail/Events.h"
#include "../Model/Data.Detail/EventsEditor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Model::Time::HourMinute>(const Model::Time::HourMinute & t) {
	return std::to_wstring(t.hour) + std::wstring{ ':' } +std::to_wstring(t.minute);
}

namespace Events_Details
{
	auto GenerateEvents(Model::Data::Detail::Events & evt) {
		std::vector<Model::Data::Detail::EventHandle> handles;
		handles.reserve(90);
		auto ed = evt.edit();
		for (unsigned int dayValue = 1; dayValue < 11; ++dayValue) {
			for (unsigned int hourValue = 1; hourValue < 10; ++hourValue) {
				auto d = date::year{ 2017 } / date::month{ 1 } / date::day{ dayValue };
				auto handle1 = ed.create(d, Model::Time::HourMinute{ (unsigned char)dayValue, (unsigned char)hourValue }, Model::Time::Duration{ 30 }, nullptr);
				handles.push_back(handle1);
			}
		}

		ed.commit_changes_only_memory();
		return handles;
	}
	

    TEST_CLASS(EventsTest)
    {
    public:
        TEST_METHOD(CreateEventsClass)
		{
			Model::Data::Detail::Events evt;
        }

		TEST_METHOD(Add1EventItem) {
			Model::Data::Detail::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			ed.create(d, Model::Time::HourMinute{ 12,20 }, Model::Time::Duration{ 30 }, nullptr);
			ed.commit_changes_only_memory();
			Assert::AreEqual(evt.size(), (std::size_t)1);
		}

		TEST_METHOD(Add2EventItems) {
			Model::Data::Detail::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			ed.create(d, Model::Time::HourMinute{ 12,20 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 14,00 }, Model::Time::Duration{ 30 }, nullptr);

			ed.commit_changes_only_memory();
			Assert::AreEqual(evt.size(), (std::size_t)2);
		}

		TEST_METHOD(Add2EventItemsSortedCheck) {
			Model::Data::Detail::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			ed.create(d, Model::Time::HourMinute{ 12,20 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 14,00 }, Model::Time::Duration{ 30 }, nullptr);

			ed.commit_changes_only_memory();
			Assert::AreEqual(evt.begin()->start, Model::Time::HourMinute { 12, 20 });
		}

		TEST_METHOD(Add4EventItemsSortedCheck) {
			Model::Data::Detail::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			ed.create(d, Model::Time::HourMinute{ 12,20 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 14,00 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 8,00 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 7,00 }, Model::Time::Duration{ 30 }, nullptr);

			ed.commit_changes_only_memory();
			Assert::AreEqual(evt.begin()->start, Model::Time::HourMinute { 7, 0 });
			
			auto last = evt.end() - 1;
			Assert::AreEqual(last->start, Model::Time::HourMinute{ 14,0 });
		}

		TEST_METHOD(CheckFind) {
			Model::Data::Detail::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			auto handle1 = ed.create(d, Model::Time::HourMinute{ 12,20 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 14,00 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 8,00 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 7,00 }, Model::Time::Duration{ 30 }, nullptr);

			ed.commit_changes_only_memory();
			
			auto foundItem = evt.find(handle1);

			Assert::IsTrue(foundItem != nullptr);
			Assert::AreEqual(foundItem->start, Model::Time::HourMinute { 12, 20 });
			Assert::IsTrue(evt.has(handle1));
		}

		TEST_METHOD(CheckFind_CannotFind) {
			Model::Data::Detail::Events evt;
			auto ed = evt.edit();
			auto d = date::year{ 2017 } / 11 / 1;
			auto handle1 = ed.create(d, Model::Time::HourMinute{ 12,20 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 14,00 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 8,00 }, Model::Time::Duration{ 30 }, nullptr);
			ed.create(d, Model::Time::HourMinute{ 7,00 }, Model::Time::Duration{ 30 }, nullptr);

			ed.commit_changes_only_memory();

			// handle1 to impossible value
			handle1.value = 34;
			auto foundItem = evt.find(handle1);
			Assert::IsTrue(foundItem == nullptr);
		}

		TEST_METHOD(begin_date__end_date) {
			Model::Data::Detail::Events evt;
			auto ed = evt.edit();
			for (unsigned int monthValue = 1; monthValue < 11; ++monthValue) {
				for (unsigned int dayValue = 1; dayValue < 10; ++dayValue) {
					auto d = date::year{ 2017 } / date::month{ monthValue } / date::day{ dayValue };
					auto handle1 = ed.create(d, Model::Time::HourMinute{ (unsigned char)monthValue, (unsigned char)dayValue }, Model::Time::Duration{ 30 }, nullptr);
				}
			}

			ed.commit_changes_only_memory();

			auto start = evt.begin_date(date::year{ 2017 } / 3 / 3);
			auto end = evt.end_date(date::year{ 2017 } / 9 / 9);

			Assert::AreEqual(start->start, Model::Time::HourMinute{ 3,3 });
			Assert::AreEqual(end->start, Model::Time::HourMinute{ 10,1 });
		}

		TEST_METHOD(remove) {
			Model::Data::Detail::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit(); 
			ed.remove(handles[0]);
			ed.remove(handles[1]);

			ed.commit_changes_only_memory();
			
			Assert::AreEqual(handles.size() - 2, evt.size());
			Assert::AreEqual(evt.begin()->start, Model::Time::HourMinute { 1, 3 });
		}

		TEST_METHOD(remove_day) {
			Model::Data::Detail::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit();
			ed.remove_day(date::year{ 2017 } / 1 / 3);

			ed.commit_changes_only_memory();

			Assert::AreEqual(handles.size() - 9, evt.size());
		}

		TEST_METHOD(change) {
			Model::Data::Detail::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit();
			
			ed.change(*handles.begin(), (Model::Resources::Resource*) 1);
			ed.change(handles[25], (Model::Resources::Resource*) 25);

			ed.commit_changes_only_memory();

			Assert::AreEqual((int)evt.begin()->value, 1);
			Assert::AreEqual((int)evt.find(handles[25])->value, 25);
		}

		TEST_METHOD(move) {
			Model::Data::Detail::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit();

			auto handle = ed.move(handles[0], date::year(2017) / 12 / 1);
			
			ed.commit_changes_only_memory();

			Assert::IsNull(evt.find(handles[0]));
			Assert::AreEqual(evt.find(handle)->start, Model::Time::HourMinute { 1, 1 });
		}

		TEST_METHOD(all_changes_at_once) {
			Model::Data::Detail::Events evt;
			auto handles = GenerateEvents(evt);

			auto ed = evt.edit();

			auto handle0 = ed.move(handles[0], date::year(2017) / 12 / 1);
			ed.remove(handles[1]);
			ed.remove(handles[2]);

			ed.change(handles[3], (Model::Resources::Resource*) 1);
			
			auto d = date::year{ 2017 } / 11 / 1;
			auto handle1 = ed.create(d, Model::Time::HourMinute{ 12,20 }, Model::Time::Duration{ 30 }, nullptr);

			ed.commit_changes_only_memory();

			Assert::IsNull(evt.find(handles[0]));
			Assert::IsNull(evt.find(handles[1]));
			Assert::IsNull(evt.find(handles[2]));
			Assert::AreEqual(evt.find(handle0)->start, Model::Time::HourMinute { 1, 1 });
			Assert::AreEqual(evt.find(handle1)->start, Model::Time::HourMinute { 12, 20 });
			Assert::AreEqual((int)evt.find(handles[3])->value, 1);

		}

    };
}