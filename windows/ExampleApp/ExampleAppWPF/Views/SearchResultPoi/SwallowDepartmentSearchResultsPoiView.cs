using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

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
            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");

            m_poiImage = (Image)GetTemplateChild("PoiImage");

            m_mainContainer = (FrameworkElement)GetTemplateChild("DepartmentPoiContainer");

            base.OnApplyTemplate();
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            m_categoryIcon.Source = SearchResultCategoryMapper.GetIconForCategory(m_model.Category);

            m_swallowDepartmentModel = SwallowDepartmentResultModel.FromJson(m_model.JsonData);

            m_closing = false;
            
            TitleText = m_model.Title;
            Description = m_swallowDepartmentModel.Description + m_model.Subtitle;

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
                m_poiImage.Stretch = Stretch.Uniform;
            }
        }
    }
}
