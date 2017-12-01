#include "pch.h"
#include <locale>
#include <codecvt>
#include <string>
#include "CppUnitTest.h"
#include "../model/resource/Resource.h"
#include "../model/resource/Value.h"
#include "../Model/resource/Type.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//namespace MR = model::Resources;

using Type = model::resource::Type;
using Value = model::resource::Value;
using namespace std::string_literals;

namespace Resources_ResourceTypeOwner {
	
	TEST_CLASS(EventsTest)
	{
	public:
		TEST_METHOD(create_single_value) {
			Type ty;
			auto v = ty.create();
			//v.value() = "Hello"s;
			Assert::AreEqual(v.id(), model::resource::ResourceID(1));
		}

		TEST_METHOD(create_2_resources_check_size) {
			Type ty;
			ty.create();
			ty.create();
			Assert::AreEqual(ty.size(), (std::size_t)2);
		}

		TEST_METHOD(create_2_resources_check_size_rangefor) {
			Type ty;
			ty.create();
			ty.create();
			int count = 0;
			for (auto & x : ty) {
				++count;
			}
			Assert::AreEqual(count, 2);
		}

		TEST_METHOD(create_2_resources_rangefor_check_values) {
			Type ty;
			ty.create();
			ty.create();
			model::resource::ResourceID count = 0;
			for (auto & x : ty) {
				Assert::AreEqual(++count, x.id());
			}
		}

		TEST_METHOD(change_resource_value) {
			Type ty;
			auto v = ty.create();
			v.value() = 12l;
			auto id = v.id();
			ty.change(v);
			auto v2 = *ty.begin();
			Assert::AreEqual(std::get<long>(v2.value()), 12l);
		}
	};
}