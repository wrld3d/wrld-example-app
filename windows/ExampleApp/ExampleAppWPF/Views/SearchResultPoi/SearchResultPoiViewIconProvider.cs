using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public static class SearchResultPoiViewIconProvider
    {
        public static BitmapImage GetIconForCategory(string categoryName)
        {
            var iconImagePath = string.Format("SearchResultPoiView/{0}.png", categoryName);
            StartupResourceLoader.LoadImage(iconImagePath);
            var image = StartupResourceLoader.GetBitmap(iconImagePath);
            Debug.Assert(image != null, string.Format("unable to load image for {0}", categoryName));

            return image;
        }
    }
}
