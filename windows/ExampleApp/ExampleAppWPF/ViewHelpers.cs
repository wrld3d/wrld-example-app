using QRCoder;
using System;
using System.Drawing;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    class ViewHelpers
    {
        public static Uri MakeUriForImage(string _imageFilename)
        {
            var assemblyName = Assembly.GetEntryAssembly().GetName().Name;
            var uriString = string.Format("pack://application:,,,/{0};component/Assets/{1}", assemblyName, _imageFilename);
            return new Uri(uriString, UriKind.Absolute);
        }

        public static IEnumerable<T> FindChildrenOfType<T>(UIElementCollection elements) where T : FrameworkElement
        {
            foreach (FrameworkElement element in elements)
            {
                if (element != null && element is T)
                {
                    yield return (T)element;
                }

                foreach (T child in FindChildrenOfType<T>(element))
                {
                    yield return child;
                }
            }
        }

        public static IEnumerable<T> FindChildrenOfType<T>(DependencyObject obj) where T : FrameworkElement
        {
            if (obj == null)
            {
               yield break;
            }

            var numChildren = VisualTreeHelper.GetChildrenCount(obj);
            for (int i = 0; i < numChildren; ++i)
            {
                var child = VisualTreeHelper.GetChild(obj, i);
                if (child != null && child is T)
                {
                    yield return (T)child;
                }
                else
                {
                    foreach (var recChild in FindChildrenOfType<T>(child))
                    {
                        yield return recChild;
                    }
                }
            }
        }

        public static IEnumerable<T> FindVisualChildren<T>(DependencyObject depObj) where T : DependencyObject
        {
            if (depObj != null)
            {
                for (int i = 0; i < VisualTreeHelper.GetChildrenCount(depObj); i++)
                {
                    DependencyObject child = VisualTreeHelper.GetChild(depObj, i);
                    if (child != null && child is T)
                    {
                        yield return (T)child;
                    }

                    foreach (T childOfChild in FindVisualChildren<T>(child))
                    {
                        yield return childOfChild;
                    }
                }
            }
        }

        public static T FindChildByName<T>(FrameworkElement depObj, string name) where T : FrameworkElement
        {
            foreach (var child in FindVisualChildren<T>(depObj))
            {
                if (child.Name == name)
                {
                    return (T)child;
                }
            }
            return null;
        }

        [DllImport("gdi32.dll", EntryPoint = "DeleteObject")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool DeleteObject([In] IntPtr hObject);

        public static BitmapSource GetQRCodeBitmapSourceFromURL(string url, int maxSize)
        {
            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(url, QRCodeGenerator.ECCLevel.L);
            QRCode qrCode = new QRCode(qrCodeData);

            int qrCodeBorderSize = 8;
            int moduleCount = (qrCodeData.ModuleMatrix.Count - qrCodeBorderSize);
            int pixelsPerModule = System.Math.Max((int) System.Math.Floor(maxSize / (float)moduleCount), 1);
            Bitmap bitmap = qrCode.GetGraphic(pixelsPerModule, "0x012b65", "0xffffff", false);

            IntPtr bitmapHandle = bitmap.GetHbitmap();
            BitmapSource bitmapSource;
            try
            {
                bitmapSource = Imaging.CreateBitmapSourceFromHBitmap(bitmapHandle, IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
            }
            finally
            {
                DeleteObject(bitmapHandle);
            }

            return bitmapSource;
        }
    }
}
