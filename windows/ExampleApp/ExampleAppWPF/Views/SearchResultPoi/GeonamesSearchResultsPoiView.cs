using System;
using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class GeoNamesSearchResultsPoiView : SearchResultPoiViewBase
    {
        private ExampleApp.SearchResultModelCLI m_model;

        private Image m_categoryIcon;

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

            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");
            m_mainContainer = (FrameworkElement)GetTemplateChild("GeoNamesResultView");
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;

            Image categoryIcon = (Image)GetTemplateChild("CategoryIcon");
            categoryIcon.Source = StartupResourceLoader.GetBitmap(SearchResultCategoryMapper.GetIconImageName(m_model.Category));
            m_categoryIcon.Source = StartupResourceLoader.GetBitmap(SearchResultCategoryMapper.GetIconImageName(m_model.Category));

            m_closing = false;

            Title = m_model.Title;
            Country = m_model.Subtitle;

            ShowAll();
        }

        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            // No image for this view type
        }
    }
}
