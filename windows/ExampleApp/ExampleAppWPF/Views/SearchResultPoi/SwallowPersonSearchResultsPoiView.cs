using System;
using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class SwallowPersonSearchResultsPoiView : SearchResultPoiViewBase
    {
        private Image m_categoryIcon = null;
        private Image m_portraitImage = null;
        private Grid m_addressGroup = null;
        private Border m_innerDetailsDivider = null;
        private Grid m_descriptionGroup = null;
        private TextBlock m_jobTitleText = null;
        private TextBlock m_workingGroupText = null;
        private TextBlock m_deskCodeText = null;
        
        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowPersonResultModel m_swallowPersonModel;
        
        public string TitleText { get; set; }
        public string JobTitle { get; set; }
        public string WorkingGroup { get; set; }
        public string TagList { get; set; }
        public string OfficeLocation { get; set; }
        public string DeskCode { get; set; }
        
        static SwallowPersonSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SwallowPersonSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(SwallowPersonSearchResultsPoiView)));
        }

        public SwallowPersonSearchResultsPoiView(IntPtr nativeCallerPointer, bool isInKioskMode)
            : base(nativeCallerPointer, isInKioskMode)
        {

        }

        public override void OnApplyTemplate()
        {
            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");
            m_portraitImage = (Image)GetTemplateChild("PortraitImage");
            m_addressGroup = (Grid)GetTemplateChild("AddressGroup");
            m_innerDetailsDivider = (Border)GetTemplateChild("InnerDetailsDivider");
            m_descriptionGroup = (Grid)GetTemplateChild("DescriptionGroup");
            m_jobTitleText = (TextBlock)GetTemplateChild("JobTitleText");
            m_workingGroupText = (TextBlock)GetTemplateChild("WorkingGroupText");
            m_deskCodeText = (TextBlock)GetTemplateChild("DeskCodeText");
            m_mainContainer = (FrameworkElement)GetTemplateChild("PersonPoiContainer");

            base.OnApplyTemplate();
        }
        
        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            m_categoryIcon.Source = IconProvider.GetIconForTag(m_model.IconKey, m_isInKioskMode);

            m_swallowPersonModel = SwallowPersonResultModel.FromJson(m_model.JsonData);
            
            m_closing = false;

            TitleText = m_model.Title;

            OfficeLocation = m_swallowPersonModel.OfficeLocation;
            m_addressGroup.Visibility = Visibility.Collapsed;
            m_innerDetailsDivider.Visibility = Visibility.Collapsed;
            if(OfficeLocation != null && OfficeLocation != "")
            {
                OfficeLocation = OfficeLocation.Replace(", ", "," + Environment.NewLine);
                m_addressGroup.Visibility = Visibility.Visible;

                if(m_isInKioskMode)
                {
                    m_innerDetailsDivider.Visibility = Visibility.Visible;
                }
            }

            JobTitle = m_model.Subtitle;
            m_jobTitleText.Visibility = JobTitle != null && JobTitle != "" ? Visibility.Visible : Visibility.Collapsed;

            WorkingGroup = m_swallowPersonModel.WorkingGroup;
            m_workingGroupText.Visibility = WorkingGroup != null && WorkingGroup != "" ? Visibility.Visible : Visibility.Collapsed;

            DeskCode = m_swallowPersonModel.DeskCode;
            m_deskCodeText.Visibility = DeskCode != null && DeskCode != "" ? Visibility.Visible : Visibility.Collapsed;

            bool descriptionIsVisible = false;
            descriptionIsVisible |= m_jobTitleText.Visibility == Visibility.Visible;
            descriptionIsVisible |= m_workingGroupText.Visibility == Visibility.Visible;
            descriptionIsVisible |= m_deskCodeText.Visibility == Visibility.Visible;
            m_descriptionGroup.Visibility = descriptionIsVisible ? Visibility.Visible : Visibility.Collapsed;

            TagList = m_model.HumanReadableTags[0];
            for(int i = 1; i < m_model.HumanReadableTags.Length; ++i)
            {
                TagList += ", " + m_model.HumanReadableTags[i];
            }

            OnPropertyChanged("");

            ShowAll();

            base.DisplayCustomPoiInfo(modelObject);
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
