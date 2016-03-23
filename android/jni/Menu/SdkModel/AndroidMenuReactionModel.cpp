#include "AndroidMenuReactionModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            AndroidMenuReactionModel::AndroidMenuReactionModel()
            {
            }


            AndroidMenuReactionModel::~AndroidMenuReactionModel()
            {
            }

            bool AndroidMenuReactionModel::GetShouldCloseMenu() const
            {
                return true;
            }

            bool AndroidMenuReactionModel::GetShouldOpenMenu() const
            {
                return true;
            }
        }
    }
}
