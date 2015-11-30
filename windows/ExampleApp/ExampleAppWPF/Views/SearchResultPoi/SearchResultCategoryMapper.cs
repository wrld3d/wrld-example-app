using System.Collections.Generic;

namespace ExampleAppWPF
{
    public static class SearchResultCategoryMapper
    {
        private static Dictionary<string, string> CategoryToIconIndex;

        static SearchResultCategoryMapper()
        {
            CategoryToIconIndex = new Dictionary<string, string>();

            CategoryToIconIndex.Add("caf\u00E9/pub", "coffee.png");
            CategoryToIconIndex.Add("coffee", "coffee.png");

            CategoryToIconIndex.Add("restaurant", "restaurant.png");
            CategoryToIconIndex.Add("restaurants", "restaurant.png");
            CategoryToIconIndex.Add("fast food", "restaurant.png");
            CategoryToIconIndex.Add("food", "restaurant.png");

            CategoryToIconIndex.Add("nightlife", "nightlife.png");
            CategoryToIconIndex.Add("night life", "nightlife.png");

            CategoryToIconIndex.Add("park", "park.png");
            CategoryToIconIndex.Add("parks", "park.png");

            CategoryToIconIndex.Add("theatre", "theatre.png");
            CategoryToIconIndex.Add("theater", "theatre.png");

            CategoryToIconIndex.Add("hotel", "hotel.png");
            CategoryToIconIndex.Add("hotels", "hotel.png");
            CategoryToIconIndex.Add("hotel/motel", "hotel.png");

            CategoryToIconIndex.Add("bank", "bank.png");
            CategoryToIconIndex.Add("banks", "bank.png");

            CategoryToIconIndex.Add("museum", "museum.png");
            CategoryToIconIndex.Add("museums", "museum.png");
            CategoryToIconIndex.Add("arts", "museum.png");
            
            CategoryToIconIndex.Add("meeting_room", "meetingroom.png");
            
            CategoryToIconIndex.Add("working_group", "workinggroup.png");
            CategoryToIconIndex.Add("department", "workinggroup.png");

            CategoryToIconIndex.Add("stationery", "stationery.png");

            CategoryToIconIndex.Add("toilets", "toilets.png");

            CategoryToIconIndex.Add("print_station", "printstation.png");
        }

        public static string GetIconImageName(string categoryName)
        {
            string imageName = null;
            CategoryToIconIndex.TryGetValue(categoryName, out imageName);

            if (imageName == null)
            {
                return "none.png";
            }
            else
            {
                return imageName;
            }
        }
    }
}
