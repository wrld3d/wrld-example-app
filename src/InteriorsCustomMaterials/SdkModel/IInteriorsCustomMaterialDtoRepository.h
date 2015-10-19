#include "Interiors.h"
#include "Types.h"
#include "InteriorsCustomMaterials.h"

#include <string>
#include <map>

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            class IInteriorsCustomMaterialDtoRepository
            {
            public:
                virtual ~IInteriorsCustomMaterialDtoRepository() {;}
                
                virtual void Add(const InteriorsCustomMaterialDto& interiorMaterialDto) = 0;
                virtual bool Contains(const std::string& materialKey) const = 0;
                virtual InteriorsCustomMaterialDto Get(const std::string& materialKey) const = 0;
            };
        }
    }
}