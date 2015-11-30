using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public class SwallowMeetingRoomSearchResultsPoiView : SearchResultPoiViewBase
    {
        private Image m_categoryIcon = null;
        private Image m_poiImage = null;
        
        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowMeetingRoomResultModel m_swallowMeetingRoomModel;

        public string TitleText { get; set; }
        public string Availability { get; set; }
        
        static SwallowMeetingRoomSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SwallowMeetingRoomSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(SwallowMeetingRoomSearchResultsPoiView)));
        }

        public SwallowMeetingRoomSearchResultsPoiView(IntPtr nativeCallerPointer)
            : base(nativeCallerPointer)
        {

        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");
            if(m_model != null)
            {
                m_categoryIcon.Source = StartupResourceLoader.GetBitmap(SearchResultCategoryMapper.GetIconImageName(m_model.GetCategory()));
            }

            m_poiImage = (Image)GetTemplateChild("PoiImage");
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            
            m_swallowMeetingRoomModel = SwallowMeetingRoomResultModel.FromJson(m_model.GetJsonData());

            m_closing = false;
            
            TitleText = m_swallowMeetingRoomModel.Name;
            Availability = m_swallowMeetingRoomModel.Availability;

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
