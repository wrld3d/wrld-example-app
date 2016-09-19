using System.Diagnostics;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF.Views.SearchMenu
{
    static class SearchMenuResultIconProvider
    {
        public static BitmapImage GetIconForTag(string tagName)
        {
            var iconImagePath = string.Format("icon1_{0}.png", string.IsNullOrEmpty(tagName) ? "misc" : tagName);
            StartupResourceLoader.LoadImage(iconImagePath);
            var image = StartupResourceLoader.GetBitmap(iconImagePath);
            Debug.Assert(image != null, string.Format("unable to load image for {0}", tagName));

            return image;
        }

    }
}

