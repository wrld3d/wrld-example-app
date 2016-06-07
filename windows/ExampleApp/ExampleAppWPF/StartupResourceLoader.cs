using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public static class StartupResourceLoader
    {
        private static Dictionary<string, BitmapImage> m_resources;

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

        public static void LoadImage(params string[] pathAndName)
        {
            BitmapImage key = null;
            m_resources.TryGetValue(pathAndName[pathAndName.Length - 1], out key);

            if (key != null)
                return;

            var path = System.IO.Path.Combine(pathAndName);
            path = System.IO.Path.Combine(Environment.CurrentDirectory, "Resources", path);

            Uri uri = null;
            try
            {
                uri = new Uri(path);
            }
            catch(System.Exception)
            {
                System.Windows.MessageBox.Show("Cannot find Path: " + path, "Path Not Found", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
                return;
            }

            BitmapImage bitmap = null;

            try
            {
                bitmap = new BitmapImage(uri);
            }
            catch (System.IO.IOException e)
            {
                System.Windows.MessageBox.Show("Cannot find file: " + path, "File Not Found", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
                return;
            }

            m_resources.Add(pathAndName[pathAndName.Length - 1], bitmap);
        }
    }
}
