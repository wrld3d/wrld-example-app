#include "NavRouteInstructionHelper.h"
#include "NavRouting.h"

#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace Direction
            {
                static const char* DestinationReached = "destination reached";
                static const char* Destination = "destination";
                static const char* Entrance = "entrance";
                static const char *Turn = "turn";
                static const char *Continue = "continue";
                static const char *Take = "take";
                static const char *Enter = "enter";
                static const char *Exit = "exit";
                static const char *EnterBuilding = "enter building";
                static const char *ExitBuilding = "exit building";
                static const char *Approach = "approach";
                static const char *EndOfRoad = "end of road";
                static const char *EndOfRoadIndoors = "end of path";
                static const char *NewName = "new name";
                static const char *Arrive = "arrive";
                static const char *Depart = "depart";
                static const char *UTurn = "make a u-turn";
                static const char* Floor = "floor";
                static const char* Elevator = "elevator";
                static const char* Lift = "lift";
            }

            namespace Preposition {
                static const char* In = "in";
                static const char* Into = "into";
                static const char* Onto = "onto";
                static const char* Through = "through";
                static const char* On = "on";
                static const char* Via = "via";
                static const char* To = "to";
                static const char* At = "at";
            }

            namespace Modifiers
            {
                static const char* UTurn = "uturn";
                static const char* Straight = "straight";
                static const char* Up = "up";
                static const char* Down = "down";
            }

            namespace
            {
                std::string GetDirectionWithOptionalLocation(std::string direction,
                                                             std::string verb,
                                                             std::string locationName)
                {
                    std::stringstream ss;
                    if(locationName.empty())
                    {
                        ss << direction;
                    }
                    else
                    {
                        ss << direction << " " << verb << " " << locationName;
                    }
                    return ss.str();
                }

                std::string GetHumanReadableBearing(double bearing)
                {
                    double div=22.5;
                    std::vector<std::string> directions;
                    directions.push_back("N");
                    directions.push_back("NE");
                    directions.push_back("E");
                    directions.push_back("SE");
                    directions.push_back("S");
                    directions.push_back("SW");
                    directions.push_back("W");
                    directions.push_back("NW");
                    directions.push_back("N");
                    int dirIndex = static_cast<int>(floor(bearing-div)/(div*2))%8;
                    return directions.at(static_cast<unsigned long>(dirIndex));
                }

                std::string GetInstructionForMultifloorStep(const Eegeo::Routes::Webservice::RouteStep& step,
                                                            const Eegeo::Routes::Webservice::RouteStep& nextStep)
                {
                    std::stringstream ss;
                    ss << Direction::Take << " " << step.Directions.Type;
                    std::string direction = ss.str();
                    ss.str(std::string());
                    ss << Direction::Floor << " " << InstructionTokens::NextFloorName;
                    std::string floorName = ss.str();
                    return GetDirectionWithOptionalLocation(direction, Preposition::To, floorName);
                }

                std::string GetInstructionForEnterExitBuilding(const Eegeo::Routes::Webservice::RouteStep& step,
                                                               const Eegeo::Routes::Webservice::RouteStep& nextStep)
                {
                    return GetDirectionWithOptionalLocation(nextStep.IsIndoors ? Direction::EnterBuilding : Direction::ExitBuilding,
                                                            Preposition::Via,
                                                            step.Name);
                }

                std::string GetInstructionForDeparting(const Eegeo::Routes::Webservice::RouteStep& step)
                {
                    std::stringstream ss;
                    std::string verb = step.IsIndoors ? Preposition::Through : Preposition::On;
                    ss << Direction::Depart << " " << GetHumanReadableBearing(step.Directions.BearingAfter);
                    return GetDirectionWithOptionalLocation(ss.str(), verb, step.Name);
                }

                std::string GetInstructionForApproachingEntrance(const Eegeo::Routes::Webservice::RouteStep& step)
                {
                    std::stringstream ss;
                    ss << Direction::Approach << " " << Direction::Entrance;
                    return GetDirectionWithOptionalLocation(ss.str(), Preposition::On, step.Directions.Modifier);
                }

                std::string GetBasicInstruction(const std::string& type,
                                                const std::string& modifier,
                                                const std::string& locationName,
                                                const std::string& prep)
                {
                    std::stringstream directionStream;
                    directionStream << type;
                    if(!modifier.empty())
                    {
                        directionStream << " " << modifier;
                    }

                    return GetDirectionWithOptionalLocation(directionStream.str(),
                                                            prep,
                                                            locationName);
                }

                std::string ConvertDirectionType(const std::string& type, const std::string& modifier, bool indoors)
                {
                    std::string currentType = type;

                    if(currentType == Direction::EndOfRoad && indoors)
                    {
                        return Direction::EndOfRoadIndoors;
                    }

                    if(type == Direction::NewName)
                    {
                        currentType = Direction::Turn;
                    }

                    if(currentType==Direction::Turn)
                    {
                        if(modifier==Modifiers::Straight)
                        {
                            return Direction::Continue;
                        }
                        else if(modifier==Modifiers::UTurn)
                        {
                            return Direction::UTurn;
                        }
                    }

                    return currentType;
                }
            }


            NavRouteFormattedInstructions NavRouteInstructionHelper::GetFormattedInstructionForStep(
                    const Eegeo::Routes::Webservice::RouteData& route,
                    int sectionIndex,
                    int stepIndex)
            {
                const Eegeo::Routes::Webservice::RouteSection& currentSection = route.Sections.at(
                        static_cast<unsigned long>(sectionIndex));
                const Eegeo::Routes::Webservice::RouteStep& currentStep = currentSection.Steps.at(
                        static_cast<unsigned long>(stepIndex));

                std::string locationName = currentStep.Name;

                int nextStepIndex;
                int nextSectionIndex;
                const Eegeo::Routes::Webservice::RouteStep* pNextStep = NULL;
                const Eegeo::Routes::Webservice::RouteStep* pNextNextStep = NULL;
                std::string nextInstructionText;
                if(TryGetNextValidStep(route, sectionIndex, stepIndex, pNextStep, nextSectionIndex, nextStepIndex))
                {
                    TryGetNextValidStep(route, nextSectionIndex, nextStepIndex, pNextNextStep, nextSectionIndex, nextStepIndex);
                    nextInstructionText = GetStandardInstructionTextForStep(*pNextStep,
                                                                            &currentStep,
                                                                        pNextNextStep);
                }

                std::stringstream ss;
                ss << InstructionTokens::Distance << "m - " << nextInstructionText;
                std::string shortInstructionName = ss.str();
                ss.str(std::string());

                ss << Preposition::In << " " << InstructionTokens::Distance << "m " << nextInstructionText;
                std::string fullInstructionText = ss.str();

                std::string iconKey;
                bool isMultiFloor = false;
                int nextFloorId = 0;
                
                if(pNextStep == NULL)
                {
                    fullInstructionText = shortInstructionName = Direction::DestinationReached;
                    iconKey = Direction::Arrive;
                }
                else
                {
                    iconKey = GetIconNameFromType(*pNextStep,
                                                  pNextNextStep,
                                                  &currentStep);
                    
                    if (pNextStep->IsMultiFloor)
                    {
                        isMultiFloor = true;
                        nextFloorId = pNextNextStep->IndoorFloorId;
                    }
                    else if (currentStep.IsMultiFloor)
                    {
                        isMultiFloor = true;
                        nextFloorId = pNextStep->IndoorFloorId;
                    }
                }

                return NavRouteFormattedInstructions(shortInstructionName,
                                                     locationName,
                                                     fullInstructionText,
                                                     iconKey,
                                                     isMultiFloor,
                                                     nextFloorId
                );
            }

            std::string NavRouteInstructionHelper::GetStandardInstructionTextForStep(
                    const Eegeo::Routes::Webservice::RouteStep &step,
                    const Eegeo::Routes::Webservice::RouteStep* pPrevStep,
                    const Eegeo::Routes::Webservice::RouteStep* pNextStep)
            {
                std::string type = step.Directions.Type;
                std::string modifier = step.Directions.Modifier;

                std::stringstream ss;
                if(step.IsMultiFloor && pNextStep != NULL) {
                    return GetInstructionForMultifloorStep(step, *pNextStep);
                }

                if(pPrevStep != NULL && pPrevStep->IsMultiFloor)
                {
                    type = Direction::Exit;
                    modifier = pPrevStep->Directions.Type;
                }

                if(type == Direction::Entrance)
                {
                    // NOTE: Handling a case from route service where we have 2 steps marked 'entrance'
                    if(pNextStep != NULL && pNextStep->Directions.Type != Direction::Entrance)
                    {
                        return GetInstructionForEnterExitBuilding(step, *pNextStep);
                    }
                    else if(pNextStep == NULL)
                    {
                        modifier = Modifiers::Straight;
                    }

                    type = Direction::Turn;
                }

                if(type == Direction::Arrive)
                {
                    if(pNextStep != NULL)
                    {
                        return GetInstructionForApproachingEntrance(step);
                    }
                    else
                    {
                        return GetBasicInstruction(type,
                                                   modifier,
                                                   Direction::Destination,
                                                   Preposition::At);
                    }
                }
                else if(type == Direction::Depart)
                {
                    return GetInstructionForDeparting(step);
                }

                type = ConvertDirectionType(type, modifier, step.IsIndoors);

                bool shouldShowLocationName = !step.IsIndoors || pPrevStep->Name != step.Name;
                return GetBasicInstruction(type,
                                           modifier,
                                           shouldShowLocationName ? step.Name : std::string(),
                                           step.IsIndoors ? Preposition::Into : Preposition::Onto);
            }

            std::string NavRouteInstructionHelper::GetIconNameFromType(const Eegeo::Routes::Webservice::RouteStep& step,
                                                                       const Eegeo::Routes::Webservice::RouteStep* pNextStep,
                                                                       const Eegeo::Routes::Webservice::RouteStep* pPrevStep)
            {
                std::string type = step.Directions.Type;
                std::string modifier = step.Directions.Modifier;

                if (type == Direction::NewName ||
                    type == Direction::Continue ||
                    type == Direction::Arrive)
                {
                    type = Direction::Turn;
                    if(modifier.empty())
                    {
                        modifier = Modifiers::Straight;
                    }
                }

                bool isMultilevel = step.IsMultiFloor && pPrevStep != NULL && pNextStep != NULL;
                bool goingUp = isMultilevel && pNextStep->IndoorFloorId > pPrevStep->IndoorFloorId;

                if(isMultilevel)
                {
                    if (type == Direction::Elevator)
                    {
                        return Direction::Lift;
                    }
                    else
                    {
                        modifier = goingUp ? Modifiers::Up : Modifiers::Down;
                    }
                }

                if(type == Direction::Entrance)
                {
                    if(pNextStep != NULL && pNextStep->Directions.Type != Direction::Entrance)
                    {
                        bool isEnteringBuilding = pNextStep->IsIndoors;
                        return isEnteringBuilding ? Direction::Enter : Direction::Exit;
                    }
                    else if(pNextStep == NULL)
                    {
                        modifier = Modifiers::Straight;
                    }

                    type = Direction::Turn;
                }

                std::replace(type.begin(), type.end(), ' ', '_');
                std::replace(modifier.begin(), modifier.end(), ' ', '_');

                if (type == Direction::Arrive || type == Direction::Depart)
                {
                    return type;
                }

                if (type == Direction::Turn && modifier == Modifiers::Straight)
                {
                    return modifier;
                }

                return (type + "_" + modifier);
            }

            bool NavRouteInstructionHelper::TryGetNextValidStep(const Eegeo::Routes::Webservice::RouteData& route,
                int inSectionIndex,
                int inStepIndex,
                const Eegeo::Routes::Webservice::RouteStep*& pNextStep,
                int &out_sectionIndex,
                int &out_stepIndex) {

                const Eegeo::Routes::Webservice::RouteSection &currentSection = route.Sections.at(
                        static_cast<unsigned long>(inSectionIndex));

                pNextStep = NULL;
                out_stepIndex = inStepIndex;
                out_sectionIndex = inSectionIndex;
                bool reachedEnd = false;

                while (pNextStep == NULL && !reachedEnd) {
                    if (out_stepIndex < currentSection.Steps.size() - 1)
                    {
                        out_stepIndex += 1;
                        pNextStep = &currentSection.Steps.at(static_cast<unsigned long>(out_stepIndex));
                    }
                    else if (out_sectionIndex < route.Sections.size() - 1)
                    {
                        out_sectionIndex += 1;
                        out_stepIndex = 0;
                        pNextStep = &route.Sections.at(
                                static_cast<unsigned long>(out_sectionIndex)).Steps.at(
                                static_cast<unsigned long>(out_stepIndex));
                    }
                    else
                    {
                        reachedEnd = true;
                    }
                }

                return pNextStep != NULL;
            }
        }
    }
}
