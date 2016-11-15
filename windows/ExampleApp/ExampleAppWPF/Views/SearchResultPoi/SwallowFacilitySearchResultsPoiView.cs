using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class SwallowFacilitySearchResultsPoiView : SearchResultPoiViewBase
    {
        private Image m_categoryIcon = null;
        private Image m_poiImage = null;
        
        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowFacilityResultModel m_swallowFacilityModel;

        public string TitleText { get; set; }
        public string Description { get; set; }
        
        static SwallowFacilitySearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SwallowFacilitySearchResultsPoiView), new FrameworkPropertyMetadata(typeof(SwallowFacilitySearchResultsPoiView)));
        }

        public SwallowFacilitySearchResultsPoiView(IntPtr nativeCallerPointer)
            : base(nativeCallerPointer)
        {

        }

        public override void OnApplyTemplate()
        {
            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");

            m_poiImage = (Image)GetTemplateChild("PoiImage");

            m_mainContainer = (FrameworkElement)GetTemplateChild("FacilityPoiContainer");

            base.OnApplyTemplate();
        }
        
        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            m_categoryIcon.Source = SearchResultPoiViewIconProvider.GetIconForTag(m_model.IconKey);

            m_swallowFacilityModel = SwallowFacilityResultModel.FromJson(m_model.JsonData);

            m_closing = false;
            
            TitleText = m_model.Title;
            Description = m_swallowFacilityModel.Description;

            m_poiImage.Source = new BitmapImage(new Uri("/Assets/poi_placeholder.png", UriKind.Relative));
            m_poiImage.Stretch = Stretch.Fill;
            OnPropertyChanged("");

            ShowAll();
        }

        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            if (hasImage)
            {
                m_poiImage.Source = LoadImageFromByteArray(imgData);
                m_poiImage.Stretch = Stretch.UniformToFill;
            }
        }
    }
}
