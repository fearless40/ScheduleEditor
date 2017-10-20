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

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Model::Time::HourMinute>(const Model::Time::HourMinute & t) { return L"FuckOff"; }

namespace ModelTest
{
	

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
			Assert::AreSame(evt.begin()->start, Model::Time::HourMinute { 12, 20 });
			
		}

    };
}