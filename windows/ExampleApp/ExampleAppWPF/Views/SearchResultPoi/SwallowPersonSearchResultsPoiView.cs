using System;
using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class SwallowPersonSearchResultsPoiView : SearchResultPoiViewBase
    {
        private Image m_portraitImage = null;
        
        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowPersonResultModel m_swallowPersonModel;
        
        public string TitleText { get; set; }
        public string JobTitle { get; set; }
        public string WorkingGroup { get; set; }
        public string OfficeLocation { get; set; }
        public string DeskCode { get; set; }
        
        static SwallowPersonSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SwallowPersonSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(SwallowPersonSearchResultsPoiView)));
        }

        public SwallowPersonSearchResultsPoiView(IntPtr nativeCallerPointer)
            : base(nativeCallerPointer)
        {

        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            
            m_portraitImage = (Image)GetTemplateChild("PortraitImage");
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;

            m_swallowPersonModel = SwallowPersonResultModel.FromJson(m_model.JsonData);
            
            m_closing = false;

            TitleText = m_model.Title;
            JobTitle = m_swallowPersonModel.JobTitle;
            WorkingGroup = m_swallowPersonModel.WorkingGroup;
            OfficeLocation = m_swallowPersonModel.OfficeLocation;
            DeskCode = m_swallowPersonModel.DeskCode;

            ShowAll();
        }

        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            m_portraitImage.Source = LoadImageFromByteArray(imgData);
            m_portraitImage.Visibility = Visibility.Visible;
        }
    }
}
