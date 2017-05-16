#include "stdafx.h"
#include "CppUnitTest.h"
#include <unordered_map>
#include <variant>

#include "../ScheduleEditor/Model/Model.h"
#include "../ScheduleEditor/Model/Properties.h"
#include "../ScheduleEditor/Model/Properties.PropertyMap.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{		
	TEST_CLASS(PropertyMap)
	{
	public:
		
		TEST_METHOD(PropertyMapCreation)
		{
			// TODO: Your test code here
			Model::Properties::PropertyMap map;
		}

	};
}