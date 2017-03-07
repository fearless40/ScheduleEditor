#include "pch.h"
#include <variant>
#include <string>
#include "Model.h"
#include "PropertyMap.h"

namespace Model {
	namespace Properties {


		PropertyTemplate * Model::Properties::CreateTemplate(std::string templateid)
		{
			return nullptr;
		}

		PropertyMap CreateMap(std::string templateid)
		{
			return PropertyMap();
		}

		PropertyMap Model::Properties::CreateMap(PropertyTemplate * temp)
		{
			return PropertyMap();
		}

		const PropertyTemplate * Model::Properties::FindTemplate(std::string templateid)
		{
			return nullptr;
		}

		void PropertyMap::add(std::string key, Property prop)
		{
		}

		void PropertyMap::remove(std::string key)
		{
		}

	}
}