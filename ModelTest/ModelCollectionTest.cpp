#include "pch.h"
#include "CppUnitTest.h"
#include "../Model/ModelCollection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Model_ModelCollection {


	TEST_CLASS(PropertiesMap)
	{
	public:
		TEST_METHOD(Create) {
			struct Test {
				Model::Index mIndex;
				Model::IndexConst index() const noexcept { return mIndex; }
			};
			
			Model::ModelCollection<Test> values;
			
			{
				Test t{ "1" };
				values.save(t);
			}

			{
				Test t{ "2" };
				values.save(t);
			}

			{
				Test t{ "3" };
				values.save(t);
			}

			{
				Test t{ "4" };
				values.save(t);
			}

			{
				Test t{ "5" };
				values.save(std::move(t));
			}

			Assert::AreEqual(values.find("4")->mIndex, std::string { "4" });
			Assert::IsNull(values.find("10"));
		}
	};
}