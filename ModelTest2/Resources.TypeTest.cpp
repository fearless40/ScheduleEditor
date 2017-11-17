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

		TEST_METHOD(create_and_retrieve_resources) {
			
		}

	};
}