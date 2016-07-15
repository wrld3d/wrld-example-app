using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public static class StartupResourceLoader
    {
        private static Dictionary<string, BitmapImage> m_resources;
        private static string ProgramDataPath;

        static StartupResourceLoader()
        {
            m_resources = new Dictionary<string, BitmapImage>();

            LoadImage("Yelp", "stars_0_0.png");
            LoadImage("Yelp", "stars_1_0.png");
            LoadImage("Yelp", "stars_1_5.png");
            LoadImage("Yelp", "stars_2_0.png");
            LoadImage("Yelp", "stars_2_5.png");
            LoadImage("Yelp", "stars_3_0.png");
            LoadImage("Yelp", "stars_3_5.png");
            LoadImage("Yelp", "stars_4_0.png");
            LoadImage("Yelp", "stars_4_5.png");
            LoadImage("Yelp", "stars_5_0.png");
            LoadImage("Yelp", "yelp_logo.png");
            LoadImage("Yelp", "yelp_reviews.png");

            LoadImage("button_add_pin_off.png");
            LoadImage("button_close_off.png");
            LoadImage("button_remove_pin_off.png");

            LoadImage("arrow3_down.png");

            ProgramDataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData), "eeGeo_Ltd", System.Diagnostics.Process.GetCurrentProcess().ProcessName, "Resources");
        }

        public static void Init()
        {}

        public static Image GetImage(string name)
        {
            BitmapImage bitmap = null;
            m_resources.TryGetValue(name, out bitmap);

            var img = new Image();
            img.Source = bitmap;
            return img;
        }

        public static BitmapImage GetBitmap(string name)
        {
            BitmapImage bitmap = null;
            m_resources.TryGetValue(name, out bitmap);

            return bitmap;
        }

        private static bool CanOpenPath(string filePath, out Uri uri)
        {
            uri = null;

            try
            {
                uri = new Uri(filePath);
            }
            catch(UriFormatException)
            {
                return false;
            }

            return File.Exists(filePath);
        }

        public static void LoadImage(params string[] pathAndName)
        {
            BitmapImage key = null;
            m_resources.TryGetValue(pathAndName[pathAndName.Length - 1], out key);

            if (key != null)
                return;

            var filePath = Path.Combine(pathAndName);
            Uri uri = null;

            if (!CanOpenPath(Path.Combine(Environment.CurrentDirectory, "Resources", filePath), out uri) && 
                !CanOpenPath(Path.Combine(ProgramDataPath, filePath), out uri))
            {
                System.Windows.MessageBox.Show("Cannot find Path: " + filePath, "Path Not Found", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
                return;
            }

            BitmapImage bitmap = new BitmapImage(uri);

            m_resources.Add(pathAndName[pathAndName.Length - 1], bitmap);
        }
    }
}
