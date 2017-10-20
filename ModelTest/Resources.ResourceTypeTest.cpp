#include "pch.h"
#include <locale>
#include <codecvt>
#include "CppUnitTest.h"
#include "../Model/Resources.Resource.h"
#include "../Model/Resources.ResourceType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace MR = Model::Resources;

template <> 
static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<MR::ResourceType>(MR::ResourceType* q) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(q->index());
}

namespace Resources_ResourceTypeOwner {
	
	TEST_CLASS(EventsTest)
	{
	public:
		TEST_METHOD(create_and_retrieve) {
			auto r = MR::ResourceTypeOwner::Create("yomama");
			MR::ResourceTypeOwner::Save(std::move(r));
			auto & r1 = MR::ResourceTypeOwner::Find("yomama");
			Assert::AreEqual(r1.index(), Model::Index("yomama"));
		}

		TEST_METHOD(create_and_retrieve_resources) {
			auto r = MR::ResourceTypeOwner::Create("yomama");
			r.create();
			r.create();
			r.create();
			MR::ResourceTypeOwner::Save(std::move(r));
			auto & r1 = MR::ResourceTypeOwner::Find("yomama");
			Assert::AreEqual(r1.index(), Model::Index("yomama"));
			Assert::AreEqual(r1.size(), (std::size_t)3);
		}

	};
}