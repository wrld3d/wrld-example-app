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
            m_portraitImage = (Image)GetTemplateChild("PortraitImage");
            m_mainContainer = (FrameworkElement)GetTemplateChild("PersonPoiContainer");

            base.OnApplyTemplate();
        }
        
        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;

            m_swallowPersonModel = SwallowPersonResultModel.FromJson(m_model.JsonData);
            
            m_closing = false;

            TitleText = m_model.Title;
            JobTitle = m_swallowPersonModel.DeskCode;
            WorkingGroup = m_swallowPersonModel.WorkingGroup;
            OfficeLocation = m_swallowPersonModel.OfficeLocation.Replace(", ", "," + Environment.NewLine);
            DeskCode = m_model.Subtitle;

            OnPropertyChanged("");

            ShowAll();
        }

        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            if (hasImage)
            {
                m_portraitImage.Source = LoadImageFromByteArray(imgData);
            }
        }
    }
}
