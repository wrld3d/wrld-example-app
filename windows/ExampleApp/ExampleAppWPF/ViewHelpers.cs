using System;
using System.Reflection;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media;
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
    }
}
