//
// Created by david.crooks on 14/03/2018.
//
#pragma once

#include <string>
#include "BidirectionalBus.h"
#include "IAppCameraController.h"

namespace ExampleApp {
    namespace Search {
        namespace SdkModel {
            class IAutocompleteSuggestionQueryPerformer {

            public:
                virtual ~IAutocompleteSuggestionQueryPerformer() {};
                virtual void PerformSuggestionsQuery(const std::string& query) = 0;
                virtual void Cancel() = 0;
            };
        }
    }
}