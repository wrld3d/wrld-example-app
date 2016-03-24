#include "IOSMenuReactionModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            IOSMenuReactionModel::IOSMenuReactionModel()
            {
            }


            IOSMenuReactionModel::~IOSMenuReactionModel()
            {
            }

            bool IOSMenuReactionModel::GetShouldCloseMenu() const
            {
                return true;
            }

            bool IOSMenuReactionModel::GetShouldOpenMenu() const
            {
                return true;
            }
        }
    }
}
