using System;
using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class GeoNamesSearchResultsPoiView : SearchResultPoiViewBase
    {
        private ExampleApp.SearchResultModelCLI m_model;

        private Image m_tagIcon;
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

        public GeoNamesSearchResultsPoiView(IntPtr nativeCallerPointer, bool isInKioskMode)
            : base(nativeCallerPointer, isInKioskMode)
        {

        }

        public override void OnApplyTemplate()
        {
            m_tagIcon = (Image)GetTemplateChild("TagIcon");

            m_mainContainer = (FrameworkElement)GetTemplateChild("GeoNamesResultView");

            base.OnApplyTemplate();
        }

        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            m_tagIcon.Source = IconProvider.GetIconForTag(m_model.IconKey, m_isInKioskMode);

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
