using System.Diagnostics;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public static class IconProvider
    {
        public static BitmapImage GetIconForTag(string tagName, bool isInKioskmode)
        {
            string scaleTag = isInKioskmode ? "@1.5x" : "";
            var iconImagePath = string.Format("icon1_{0}{1}.png", string.IsNullOrEmpty(tagName) ? "pin" : tagName, scaleTag);
            StartupResourceLoader.LoadImage(iconImagePath);
            var image = StartupResourceLoader.GetBitmap(iconImagePath);
            Debug.Assert(image != null, string.Format("unable to load image for {0}", tagName));

            return image;
        }
    }
}
