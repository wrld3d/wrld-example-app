using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

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
            base.OnApplyTemplate();

            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");

            m_categoryIcon.Source = StartupResourceLoader.GetBitmap(SearchResultCategoryMapper.GetIconImageName(m_model.GetCategory()));

            m_poiImage = (Image)GetTemplateChild("PoiImage");
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            
            m_swallowFacilityModel = SwallowFacilityResultModel.FromJson(m_model.GetJsonData());

            m_closing = false;
            
            TitleText = m_swallowFacilityModel.Name;
            Description = m_swallowFacilityModel.Description;

            IsPinned = isPinned;

            ShowAll();
        }

        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            m_poiImage.Source = LoadImageFromByteArray(imgData);
            m_poiImage.Visibility = Visibility.Visible;
        }
    }
}
