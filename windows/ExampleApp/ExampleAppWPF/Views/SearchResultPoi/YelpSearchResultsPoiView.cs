using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class YelpSearchResultsPoiView : SearchResultPoiViewBase
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
        private ImageSource m_placeholderImage;

        private ControlClickHandler m_yelpReviewImageClickHandler;
        private Image m_yelpButton;

        public string PhoneText
        {
            get
            {
                return m_phoneText;
            }
            set
            {
                m_phoneText = value;
                OnPropertyChanged("PhoneText");
            }
        }
        public string AddressText
        {
            get
            {
                return m_addressText;
            }
            set
            {
                m_addressText = value;
                OnPropertyChanged("AddressText");
            }
        }

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
        public string PoiViewRatingCountText
        {
            get
            {
                return m_poiViewRatingCountText;
            }
            set
            {
                m_poiViewRatingCountText = value;
                OnPropertyChanged("PoiViewRatingCountText");
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
        
        public ImageSource RatingsImage
        {
            get
            {
                return m_ratingsImage;
            }
            set
            {
                m_ratingsImage = value;
                OnPropertyChanged("RatingsImage");
            }
        }
        
        public Visibility RatingCountVisibility
        {
            get
            {
                return m_ratingCountVisibility;
            }
            set
            {
                m_ratingCountVisibility = value;
                OnPropertyChanged("RatingCountVisibility");
            }
        }

        public string Url
        {
            get
            {
                return m_url;
            }
            set
            {
                m_url = value;
                OnPropertyChanged("Url");
            }
        }

        static YelpSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(YelpSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(YelpSearchResultsPoiView)));
        }

        public YelpSearchResultsPoiView(IntPtr nativeCallerPointer)
            : base(nativeCallerPointer)
        {

        }

        public override void OnApplyTemplate()
        {
            m_titleView = (TextBlock)GetTemplateChild("Title");
            
            m_poiImage = (Image)GetTemplateChild("PoiImage");

            m_yelpButton = (Image)GetTemplateChild("WebVendorLinkStyle");

            m_mainContainer = (FrameworkElement)GetTemplateChild("SearchresultsPoiViewContainer");

            m_reviewsIcon = (FrameworkElement)GetTemplateChild("ReviewsIcon");

            var scrollViewr = (ScrollViewer)GetTemplateChild("MainScrollViewr");

            scrollViewr.ManipulationBoundaryFeedback += OnBoundaryFeedback;

            var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;
            var screenWidth = mainGrid.ActualWidth;

            m_yelpReviewImageClickHandler = new ControlClickHandler(m_yelpButton, HandleWebLinkButtonClicked);

            base.OnApplyTemplate();
        }

        private void OnBoundaryFeedback(object sender, ManipulationBoundaryFeedbackEventArgs e)
        {
            e.Handled = true;
        }

        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            ExampleApp.SearchResultModelCLI model = modelObject as ExampleApp.SearchResultModelCLI;

            YelpResultModel yelpResultModel = YelpResultModel.FromResultModel(model);
            var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;
            var screenWidth = mainGrid.ActualWidth;

            m_closing = false;

            TitleText = model.Title;
            AddressText = model.Subtitle.Replace(", ", "," + Environment.NewLine);
            PhoneText = yelpResultModel.Phone;
            HumanReadableTagsText = string.Join(Environment.NewLine, model.HumanReadableTags);
            ReviewText = string.Join(Environment.NewLine, yelpResultModel.Reviews);
            TagIcon = SearchResultPoiViewIconProvider.GetIconForTag(model.IconKey);
            PoiViewRatingCountText = yelpResultModel.ReviewCount > 0 ? yelpResultModel.ReviewCount.ToString() : string.Empty;
            RatingsImage = null;

            if (yelpResultModel.ReviewCount > 0 && !string.IsNullOrEmpty(yelpResultModel.RatingsImageUrl))
            {
                RatingsImage = new BitmapImage(ViewHelpers.MakeUriForImage(string.Format("{0}.png", yelpResultModel.RatingsImageUrl)));
            }

            RatingCountVisibility = !string.IsNullOrEmpty(yelpResultModel.RatingsImageUrl) && yelpResultModel.ReviewCount > 0 ? Visibility.Visible : Visibility.Collapsed;
            Url = yelpResultModel.WebUrl;
            
            if(string.IsNullOrEmpty(ReviewText))
            {
                m_reviewsIcon.Visibility = Visibility.Hidden;
            }
            else
            {
                m_reviewsIcon.Visibility = Visibility.Visible;
            }

            m_placeholderImage = new BitmapImage(new Uri("/ExampleAppWPF;component/Assets/poi_placeholder.png", UriKind.Relative));
            m_poiImage.Source = m_placeholderImage;

            ShowAll();
        }
        
        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            var image = LoadImageFromByteArray(imgData);
            m_poiImage.Source = image ?? m_placeholderImage;
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
