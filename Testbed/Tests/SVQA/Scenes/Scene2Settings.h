#pragma once
#pragma once

#include "Settings.h"

namespace svqa
{
	struct Scene2Settings : Settings
	{
		typedef std::shared_ptr<Scene2Settings> Ptr;

		Scene2Settings() {}

        bool includeDynamicObjects;
        int  min_mean_max_random;

        void to_json(json& j) {
            j.emplace("includeDynamicObjects", this->includeDynamicObjects);
            j.emplace("min_mean_max_random",   this->min_mean_max_random);
            Settings::to_json(j);
        }

        void from_json(const json& j) {
            Settings::from_json(j);
            j.at("includeDynamicObjects").get_to(this->includeDynamicObjects);
            j.at("min_mean_max_random").get_to(this->min_mean_max_random);
        }
	};
}
