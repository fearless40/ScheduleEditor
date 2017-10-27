#include "pch.h"
#include <locale>
#include "CppUnitTest.h"

#include "../Model/Properties.PropertyMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Properties_PropertiesMap {

	namespace P = Model::Properties;
	using PMap = Model::Properties::PropertyMap;
	using Prop = Model::Properties::Property;

	TEST_CLASS(PropertiesMap)
	{
	public:
		TEST_METHOD(Create) {
			PMap pmap;
		}

		TEST_METHOD(insert_values) {
			PMap pmap;
			pmap.insert("YoMama", 0L);
			Assert::AreEqual(pmap.size(), std::size_t{ 1 });
		}

		TEST_METHOD(insert_values_2) {
			PMap pmap;
			pmap.insert("YoMama", 0L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			Assert::AreEqual(pmap.size(), std::size_t{ 2 });
		}

		TEST_METHOD(operator_get_value) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			Assert::AreEqual(std::get<long>(pmap["YoMama"]), 120l);
		}

		TEST_METHOD(find_value) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			auto item = pmap.find("YoMama");
			Assert::AreEqual(item->key, P::Key{ "YoMama" });
			//Assert::AreEqual(item, pmap.begin());
		}

		TEST_METHOD(asString_value) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			Assert::AreEqual(pmap.asString("YoMama"), Model::string{ L"120" });
		}

		TEST_METHOD(operator_get_fail) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			try {
				auto value = pmap["IDOntExsit"];
			}
			catch (...) {
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(insert_change) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			pmap.insert("YoMama_Joke",  L"NotFunny" );
			//pmap["YoMama_Joke"] = L"NotFunny";
			Assert::AreEqual(std::get<Model::string>(pmap["YoMama_Joke"]), Model::string{ L"NotFunny" });
		}

		TEST_METHOD(operator_get_change) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			//pmap.insert("YoMama_Joke", L"NotFunny");
			pmap["YoMama_Joke"] =  L"NotFunny" ;
			Assert::AreEqual(std::get<Model::string>(pmap["YoMama_Joke"]), Model::string{ L"NotFunny" });
		}

		TEST_METHOD(as_value) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			Assert::AreEqual(pmap.as<long>("YoMama"),120L);
		}

		TEST_METHOD(as_default) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			Assert::AreEqual(pmap.as<long>("YoDog", 150L), 150L);
		}

		TEST_METHOD(erase) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			pmap.erase("YoMama_Joke");
			Assert::AreEqual(pmap.has("YoMama_Joke"), false);
		}

		TEST_METHOD(erase_advanced) {
			PMap pmap;
			pmap.insert("YoMama", 120L);
			pmap.insert("YoMama_Joke", L"Your moma so fat she wears high heels and comes back with flip flops");
			pmap.insert("YoMama2", 120.8);
			pmap.erase("YoMama_Joke");
			Assert::AreEqual(pmap.has("YoMama_Joke"), false);
		}
	};
}

