using System;
using System.Reflection;

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

    }
}
