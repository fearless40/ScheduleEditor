#include "pch.h"
#include "CppUnitTest.h"
#include "../Model/ModelCollection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Model_ModelCollection {

	struct Test {
		Model::Index mIndex;
		Model::IndexConst index() const noexcept { return mIndex; }
		Test(int index) {
			mIndex = std::to_string(index);
		}

		Test(Model::IndexConst idx) : mIndex(idx) {};
	};

	template <typename T>
	void insert_values(int start, int end, T & t) {
		for (int i = start; i < end; ++i) {
			t.insert(Test{ i });
		}
	}


	TEST_CLASS(PropertiesMap)
	{
	public:
		TEST_METHOD(Create_Unordered) {
			
			Model::ModelCollection<Test> values;
			
			{
				Test t{ "1" };
				values.insert(t);
			}

			{
				Test t{ "2" };
				values.insert(t);
			}

			{
				Test t{ "3" };
				values.insert(t);
			}

			{
				Test t{ "4" };
				values.insert(t);
			}

			{
				Test t{ "5" };
				values.insert(std::move(t));
			}

			Assert::AreEqual(values.find("4")->mIndex, std::string { "4" });
			Assert::IsNull(values.find("10"));
		}

		TEST_METHOD(Erase) {
			Model::ModelCollection<Test> values;
			insert_values(1, 10, values);
			values.erase("5");
			Assert::IsNull(values.find("5"));
		}

		TEST_METHOD(Insert_Many) {
			Model::ModelCollection<Test> values;
			std::vector<Test> add_many;
			for (int i = 0; i < 20; ++i) {
				add_many.emplace_back(i);
			}
			values.insert(std::move(add_many));

			Assert::IsNotNull(values.find("19"));
		}

		TEST_METHOD(Enumerte) {
			Model::ModelCollection<Test> values;
			insert_values(1, 10, values);
			const auto k = values.enumerate_indexs();
			bool ok = false;
			for (int i = 1; i < 10; ++i) {
				ok = std::find(k.begin(), k.end(), std::to_string(i)) != k.end();
				if (!ok) {
					Assert::Fail(L"Not all expected keys found.");
				}
			}
			Assert::IsTrue(true);
			
		}
		

		
	};
}