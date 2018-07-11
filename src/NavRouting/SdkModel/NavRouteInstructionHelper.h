
#pragma once

#include "RouteData.h"
#include <string>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {

            // This thing should be done to the platform route data model!

            struct NavRouteFormattedInstructions
            {
            public:
                NavRouteFormattedInstructions(const std::string& shortInstructionName,
                                              const std::string& instructionLocation,
                                              const std::string& instructionDirection,
                                              const std::string& iconKey)
                : NavRouteFormattedInstructions(shortInstructionName,
                                                instructionLocation,
                                                instructionDirection,
                                                iconKey,
                                                false,
                                                0)
                {
                }
                
                NavRouteFormattedInstructions(const std::string& shortInstructionName,
                                              const std::string& instructionLocation,
                                              const std::string& instructionDirection,
                                              const std::string& iconKey,
                                              bool isMultifloor,
                                              int nextFloorId)
                {
                    m_shortInstructionName=shortInstructionName;
                    m_instructionLocation=instructionLocation;
                    m_instructionDirection=instructionDirection;
                    m_iconKey=iconKey;
                    m_isMultifloor = isMultifloor;
                    m_nextFloorId = nextFloorId;
                }

                const std::string& GetShortInstructionName() const { return m_shortInstructionName; }
                const std::string& GetInstructionLocation() const { return m_instructionLocation; }
                const std::string& GetInstructionDirection() const { return m_instructionDirection; }
                const std::string& GetIconKey() const { return m_iconKey; }
                
                bool GetIsMultiFloor() const { return m_isMultifloor; }
                int GetNextFloorId() const { return m_nextFloorId; }

            private:

                std::string m_shortInstructionName;   // "10m - Turn left"
                std::string m_instructionLocation;    // "WRLD Office"
                std::string m_instructionDirection;   // "In 10m, Turn right onto Brown St"
                std::string m_iconKey;                // "turn_left"

                bool m_isMultifloor;
                int m_nextFloorId;
            };

            class NavRouteInstructionHelper
            {

            public:
                NavRouteInstructionHelper() {};

                static NavRouteFormattedInstructions GetFormattedInstructionForStep(const Eegeo::Routes::Webservice::RouteData& route,
                    int sectionIndex,
                    int stepIndex);

            private:


                static std::string GetStandardInstructionTextForStep(const Eegeo::Routes::Webservice::RouteStep &step,
                                                                     const Eegeo::Routes::Webservice::RouteStep* pPrevStep,
                                                                     const Eegeo::Routes::Webservice::RouteStep* pNextStep);

                static std::string GetIconNameFromType(const Eegeo::Routes::Webservice::RouteStep& step,
                                                       const Eegeo::Routes::Webservice::RouteStep* pNextStep,
                                                       const Eegeo::Routes::Webservice::RouteStep* pPrevStep);

                static bool TryGetNextValidStep(const Eegeo::Routes::Webservice::RouteData& route,
                                                                    int inSectionIndex,
                                                                    int inStepIndex,
                                                                    const Eegeo::Routes::Webservice::RouteStep*& pNextStep,
                                                                    int &out_sectionIndex,
                                                                    int &out_stepIndex);
            };
        }
    }
}
