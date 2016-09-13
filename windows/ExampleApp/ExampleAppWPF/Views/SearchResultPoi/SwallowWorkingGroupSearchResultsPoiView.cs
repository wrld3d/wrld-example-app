using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class SwallowWorkingGroupSearchResultsPoiView : SearchResultPoiViewBase
    {
        private Image m_categoryIcon = null;
        private Image m_poiImage = null;
        
        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowWorkingGroupResultModel m_swallowWorkingGroupModel;

        private string m_titleText;
        private string m_description;

        public string TitleText
        {
            get
            {
                return m_titleText;
            }

            set
            {
                m_titleText = value;
                OnPropertyChanged("TitleText");
            }
        }

        public string Description
        {
            get
            {
                return m_description;
            }

            set
            {
                m_description = value;
                OnPropertyChanged("Description");
            }
        }
        
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
            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");

            m_poiImage = (Image)GetTemplateChild("PoiImage");

            m_mainContainer = (FrameworkElement)GetTemplateChild("WorkingGroupPoiContainer");

            base.OnApplyTemplate();
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            m_categoryIcon.Source = SearchResultCategoryMapper.GetIconForCategory(m_model.Category);

            m_swallowWorkingGroupModel = SwallowWorkingGroupResultModel.FromJson(m_model.JsonData);

            m_closing = false;
            
            TitleText = m_model.Title;
            Description = m_swallowWorkingGroupModel.Description;

            m_poiImage.Source = new BitmapImage(new Uri("/Assets/poi_placeholder.png", UriKind.Relative));
            m_poiImage.Stretch = Stretch.Fill;
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
