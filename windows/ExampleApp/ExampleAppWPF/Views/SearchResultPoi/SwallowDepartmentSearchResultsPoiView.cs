using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public class SwallowDepartmentSearchResultsPoiView : SearchResultPoiViewBase
    {
        private Image m_categoryIcon = null;
        private Image m_poiImage = null;
        
        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowDepartmentResultModel m_swallowDepartmentModel;

        public string TitleText { get; set; }
        public string Description { get; set; }
        
        static SwallowDepartmentSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SwallowDepartmentSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(SwallowDepartmentSearchResultsPoiView)));
        }

        public SwallowDepartmentSearchResultsPoiView(IntPtr nativeCallerPointer)
            : base(nativeCallerPointer)
        {

        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");
            
            m_categoryIcon.Source = StartupResourceLoader.GetBitmap(SearchResultCategoryMapper.GetIconImageName(m_model.Category));

            m_poiImage = (Image)GetTemplateChild("PoiImage");
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            
            m_swallowDepartmentModel = SwallowDepartmentResultModel.FromJson(m_model.JsonData);

            m_closing = false;
            
            TitleText = m_swallowDepartmentModel.Name;
            Description = m_swallowDepartmentModel.Description;

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
