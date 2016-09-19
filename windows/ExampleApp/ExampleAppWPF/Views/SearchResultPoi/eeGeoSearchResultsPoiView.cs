using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public class eeGeoSearchResultsPoiView : SearchResultPoiViewBase
    {
        private TextBlock m_titleView = null;
        private Image m_poiImage = null;
        
        private string m_phoneText;
        private string m_addressText;
        private string m_titleText;
        private string m_poiViewRatingCountText;
        private string m_reviewText;
        private string m_humanReadableTagsText;
        private ImageSource m_tagIcon;
        private ImageSource m_ratingsImage;
        private Visibility m_ratingCountVisibility;
        private string m_url;
        private FrameworkElement m_reviewsIcon;

        private ControlClickHandler m_yelpReviewImageClickHandler;
        
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
        public string ReviewText
        {
            get
            {
                return m_reviewText;
            }
            set
            {
                m_reviewText = value;
                OnPropertyChanged("ReviewText");
            }
        }
        public string HumanReadableTagsText
        {
            get
            {
                return m_humanReadableTagsText;
            }
            set
            {
                m_humanReadableTagsText = value;
                OnPropertyChanged("HumanReadableTagsText");
            }
        }
        
        public ImageSource TagIcon
        {
            get
            {
                return m_tagIcon;
            }
            set
            {
                m_tagIcon = value;
                OnPropertyChanged("TagIcon");
            }
        }
        
        static eeGeoSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(eeGeoSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(eeGeoSearchResultsPoiView)));
        }

        public eeGeoSearchResultsPoiView(IntPtr nativeCallerPointer)
            : base(nativeCallerPointer)
        {
        }

        public override void OnApplyTemplate()
        {
            m_titleView = (TextBlock)GetTemplateChild("Title");
            
            m_poiImage = (Image)GetTemplateChild("PoiImage");

            var yelpButton = (Image)GetTemplateChild("WebVendorLinkStyle");

            m_mainContainer = (FrameworkElement)GetTemplateChild("SearchresultsPoiViewContainer");

            m_reviewsIcon = (FrameworkElement)GetTemplateChild("ReviewsIcon");

            var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;
            var screenWidth = mainGrid.ActualWidth;

            m_yelpReviewImageClickHandler = new ControlClickHandler(yelpButton, HandleWebLinkButtonClicked);
            
            base.OnApplyTemplate();
        }

        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            ExampleApp.SearchResultModelCLI model = modelObject as ExampleApp.SearchResultModelCLI;

            m_closing = false;

            TitleText = model.Title;
            HumanReadableTagsText = string.Join(Environment.NewLine, model.HumanReadableTags);
            ReviewText = model.Subtitle;
            TagIcon = SearchResultPoiViewIconProvider.GetIconForTag(model.IconKey);

            ShowAll();
        }
        
        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            m_poiImage.Source = LoadImageFromByteArray(imgData);
            m_poiImage.Visibility = Visibility.Visible;
        }
        
        public void HandleWebLinkButtonClicked(object sender, MouseEventArgs e)
        {
            if (!string.IsNullOrEmpty(m_url))
            {
                Process.Start(m_url);
            }
        }
    }
}
