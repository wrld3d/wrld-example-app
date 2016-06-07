using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF.Views.SearchMenu
{
    static class SearchMenuResultIconProvider
    {
        public static BitmapImage GetIconForCategory(string categoryName)
        {
            var iconImagePath = string.Format("icon1_{0}.png", string.IsNullOrEmpty(categoryName) ? "misc" : categoryName);
            StartupResourceLoader.LoadImage(iconImagePath);
            var image = StartupResourceLoader.GetBitmap(iconImagePath);
            Debug.Assert(image != null, string.Format("unable to load image for {0}", categoryName));

            return image;
        }

    }
}

