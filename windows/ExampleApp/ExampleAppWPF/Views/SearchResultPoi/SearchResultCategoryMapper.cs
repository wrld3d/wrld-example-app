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

            CategoryToIconIndex.Add("restaurant", "restaurants.png");
            CategoryToIconIndex.Add("restaurants", "restaurants.png");
            CategoryToIconIndex.Add("fast food", "restaurants.png");
            CategoryToIconIndex.Add("food", "restaurants.png");

            CategoryToIconIndex.Add("nightlife", "nightlife.png");
            CategoryToIconIndex.Add("night life", "nightlife.png");

            CategoryToIconIndex.Add("park", "parks.png");
            CategoryToIconIndex.Add("parks", "parks.png");

            CategoryToIconIndex.Add("theatre", "theatre.png");
            CategoryToIconIndex.Add("theater", "theatre.png");

            CategoryToIconIndex.Add("hotel", "hotels.png");
            CategoryToIconIndex.Add("hotels", "hotels.png");
            CategoryToIconIndex.Add("hotel/motel", "hotels.png");

            CategoryToIconIndex.Add("bank", "financialservices.png");
            CategoryToIconIndex.Add("banks", "financialservices.png");

            CategoryToIconIndex.Add("museum", "museums.png");
            CategoryToIconIndex.Add("museums", "museums.png");
            CategoryToIconIndex.Add("arts", "museums.png");
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
