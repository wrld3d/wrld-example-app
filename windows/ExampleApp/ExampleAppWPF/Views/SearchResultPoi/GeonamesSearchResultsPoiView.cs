using System;
using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class GeoNamesSearchResultsPoiView : SearchResultPoiViewBase
    {
        private ExampleApp.SearchResultModelCLI m_model;

        private Image m_categoryIcon;
        private string m_title;
        private string m_country;

        public string Title
        {
            get
            {
                return m_title;
            }

            set
            {
                if (m_country != value)
                {
                    m_title = value;
                    OnPropertyChanged("Title");
                }
            }
        }

        public string Country
        {
            get
            {
                return m_country;
            }

            set
            {
                if (m_country != value)
                {
                    m_country = value;
                    OnPropertyChanged("Country");
                }
            }
        }
        
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
            m_categoryIcon.Source = SearchResultPoiViewIconProvider.GetIconForCategory(m_model.Category);

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
