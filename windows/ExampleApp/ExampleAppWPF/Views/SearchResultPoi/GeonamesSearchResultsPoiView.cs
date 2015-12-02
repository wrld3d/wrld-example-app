using System;
using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class GeoNamesSearchResultsPoiView : SearchResultPoiViewBase
    {
        private ExampleApp.SearchResultModelCLI m_model;

        public string Title { get; set; }
        public string Country { get; set; }
        
        static GeoNamesSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(GeoNamesSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(GeoNamesSearchResultsPoiView)));
        }

        public GeoNamesSearchResultsPoiView(IntPtr nativeCallerPointer)
            : base(nativeCallerPointer)
        {

        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            Image categoryIcon = (Image)GetTemplateChild("CategoryIcon");

            categoryIcon.Source = StartupResourceLoader.GetBitmap(SearchResultCategoryMapper.GetIconImageName(m_model.Category));

            m_portraitImage = (Image)GetTemplateChild("PortraitImage");
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            
            m_closing = false;

            Title = m_model.Title;
            Country = m_model.Subtitle;

            m_isPinned = isPinned;

            ShowAll();
        }

        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            // No image for this view type
        }
    }
}
