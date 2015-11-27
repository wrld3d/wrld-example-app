using System;

namespace ExampleAppWPF
{
    public interface ISearchResultPoiView
    {
        void DisplayPoiInfo(Object modelObject, bool isPinned);
    }
}
