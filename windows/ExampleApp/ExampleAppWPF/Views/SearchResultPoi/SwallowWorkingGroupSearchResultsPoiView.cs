using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public class SwallowWorkingGroupSearchResultsPoiView : SearchResultPoiViewBase
    {
        private Image m_categoryIcon = null;
        private Image m_poiImage = null;
        
        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowWorkingGroupResultModel m_swallowWorkingGroupModel;

        public string TitleText { get; set; }
        public string Description { get; set; }
        
        static SwallowWorkingGroupSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SwallowWorkingGroupSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(SwallowWorkingGroupSearchResultsPoiView)));
        }

        public SwallowWorkingGroupSearchResultsPoiView(IntPtr nativeCallerPointer)
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
            
            m_swallowWorkingGroupModel = SwallowWorkingGroupResultModel.FromJson(m_model.GetJsonData());

            m_closing = false;
            
            TitleText = m_model.GetTitle();
            Description = m_swallowWorkingGroupModel.Description;

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
