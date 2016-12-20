using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class YelpSearchResultsPoiView : SearchResultPoiViewBase
    {
        private bool m_isInKioskMode;

        private TextBlock m_titleView = null;
        private Image m_poiImage = null;
        
        private string m_phoneText;
        private string m_addressText;
        private string m_titleText;
        private string m_poiViewRatingCountText;
        private string m_reviewText;
        private string m_qrCodeStyleText;
        private string m_qrCodeText;
        private string m_humanReadableTagsText;
        private ImageSource m_tagIcon;
        private Image m_ratingsImage;
        private Visibility m_ratingCountVisibility;
        private string m_url;
        private FrameworkElement m_reviewsIcon;
        private ImageSource m_placeholderImage;
        private ScrollViewer m_contentContainer;
        private Image m_headerFade;
        private Image m_footerFade;
        private Grid m_previewImageSpinner;
        private Grid m_poiImageContainer;
        private Grid m_imageGradient;
        private Grid m_poiImageAndGradientContainer;
        private Grid m_detailsContainer;
        private double m_detailsContainerHeight;

        private Storyboard m_scrollFadeInAnim;
        private Storyboard m_scrollFadeOutAnim;

        private ControlClickHandler m_yelpReviewImageClickHandler;
        private Image m_yelpButton;

        private RepeatButton m_scrollDownButton;
        private RepeatButton m_scrollUpButton;

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
        public string QRCodeText
        {
            get
            {
                return m_qrCodeText;
            }
            set
            {
                m_qrCodeText = value;
                OnPropertyChanged("QRCodeText");
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
        
        public Image RatingsImage
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

        public YelpSearchResultsPoiView(IntPtr nativeCallerPointer, bool isInKioskMode)
            : base(nativeCallerPointer)
        {
            m_isInKioskMode = isInKioskMode;
        }

        public override void OnApplyTemplate()
        {
            m_titleView = (TextBlock)GetTemplateChild("Title");
            
            m_poiImage = (Image)GetTemplateChild("PoiImage");

            m_yelpButton = (Image)GetTemplateChild("WebVendorLinkStyle");

            m_mainContainer = (FrameworkElement)GetTemplateChild("SearchresultsPoiViewContainer");

            m_reviewsIcon = (FrameworkElement)GetTemplateChild("ReviewsIcon");

            m_contentContainer = (ScrollViewer)GetTemplateChild("ContentContainer");

            m_contentContainer.ManipulationBoundaryFeedback += OnBoundaryFeedback;

            m_contentContainer.ScrollChanged += OnSearchResultsScrolled;

            m_headerFade = (Image)GetTemplateChild("HeaderFade");

            m_footerFade = (Image)GetTemplateChild("FooterFade");

            m_previewImageSpinner = (Grid)GetTemplateChild("PreviewImageSpinner");

            m_poiImageContainer = (Grid)GetTemplateChild("PoiImageContainer");

            m_imageGradient = (Grid)GetTemplateChild("ImageGradient");

            m_ratingsImage = (Image)GetTemplateChild("RatingImage");

            m_poiImageAndGradientContainer = (Grid)GetTemplateChild("PoiImageAndGradientContainer");

            m_detailsContainer = (Grid)GetTemplateChild("DetailsContainer");

            m_detailsContainerHeight = (double)Application.Current.Resources["YelpPOIViewDetailsContainerHeight"];

            m_qrCodeStyleText = (string)Application.Current.Resources["YelpPOIViewQRCodeText"];

            m_scrollUpButton = (RepeatButton)GetTemplateChild("YelpPOIViewScrollUpButton");
            m_scrollUpButton.Click += HandleScrollUpButtonClicked;

            m_scrollDownButton = (RepeatButton)GetTemplateChild("YelpPOIViewScrollDownButton");
            m_scrollDownButton.Click += HandleScrollDownButtonClicked;

            m_scrollFadeInAnim = ((Storyboard)Template.Resources["ScrollFadeIn"]).Clone();
            m_scrollFadeOutAnim = ((Storyboard)Template.Resources["ScrollFadeOut"]).Clone();

            var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;
            var screenWidth = mainGrid.ActualWidth;

            m_yelpReviewImageClickHandler = new ControlClickHandler(m_yelpButton, HandleWebLinkButtonClicked);

            base.OnApplyTemplate();
        }
        private void OnSearchResultsScrolled(object sender, RoutedEventArgs e)
        {
            if (m_contentContainer.VerticalOffset == m_contentContainer.ScrollableHeight)
            {
                if(m_headerFade.Opacity <= 0)
                {
                    m_scrollFadeInAnim.Begin(m_headerFade);
                    m_scrollFadeInAnim.Begin(m_scrollUpButton);
                }

                if(m_footerFade.Opacity >= 1)
                {
                    m_scrollFadeOutAnim.Begin(m_footerFade);
                    m_scrollFadeOutAnim.Begin(m_scrollDownButton);
                }
            }
            else if(m_contentContainer.VerticalOffset == 0)
            {
                if (m_headerFade.Opacity >= 1)
                {
                    m_scrollFadeOutAnim.Begin(m_headerFade);
                    m_scrollFadeOutAnim.Begin(m_scrollUpButton);
                }

                if(m_footerFade.Opacity <= 0)
                {
                    m_scrollFadeInAnim.Begin(m_footerFade);
                    m_scrollFadeInAnim.Begin(m_scrollDownButton);
                }
            }
            else
            {
                if (m_headerFade.Opacity <= 0)
                {
                    m_scrollFadeInAnim.Begin(m_headerFade);
                    m_scrollFadeInAnim.Begin(m_scrollUpButton);
                }

                if (m_footerFade.Opacity <= 0)
                {
                    m_scrollFadeInAnim.Begin(m_footerFade);
                    m_scrollFadeInAnim.Begin(m_scrollDownButton);
                }
            }
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
            HumanReadableTagsText = string.Join(", ", model.HumanReadableTags);
            ReviewText = string.Join(Environment.NewLine, yelpResultModel.Reviews);
            QRCodeText = string.Format(m_qrCodeStyleText, TitleText);
            TagIcon = SearchResultPoiViewIconProvider.GetIconForTag(model.IconKey);
            PoiViewRatingCountText = yelpResultModel.ReviewCount > 0 ? yelpResultModel.ReviewCount.ToString() : string.Empty;
            RatingsImage.Source = null;

            m_contentContainer.ScrollToTop();

            if (yelpResultModel.ReviewCount > 0 && !string.IsNullOrEmpty(yelpResultModel.RatingsImageUrl))
            {
                RatingsImage.Source = new BitmapImage(ViewHelpers.MakeUriForImage(string.Format("{0}{1}.png", yelpResultModel.RatingsImageUrl, m_isInKioskMode ? "@kiosk" : "")));
            }

            if (string.IsNullOrEmpty(yelpResultModel.ImageUrl))
            {
                m_previewImageSpinner.Visibility = Visibility.Hidden;
                m_imageGradient.Visibility = Visibility.Collapsed;
                m_poiImageAndGradientContainer.Visibility = Visibility.Collapsed;
                m_detailsContainer.Height = Double.NaN;
            }
            else
            {
                m_previewImageSpinner.Visibility = Visibility.Visible;
                m_imageGradient.Visibility = Visibility.Visible;
                m_poiImageAndGradientContainer.Visibility = Visibility.Visible;
                m_detailsContainer.Height = m_detailsContainerHeight;
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

            m_poiImageContainer.Visibility = Visibility.Visible;
            
            m_poiImage.Visibility = Visibility.Hidden;

            ShowAll();
        }
        
        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            if(hasImage)
            {
                m_poiImageContainer.Visibility = Visibility.Visible;
                m_poiImage.Source = LoadImageFromByteArray(imgData);
                m_poiImage.Visibility = Visibility.Visible;
            }
            m_previewImageSpinner.Visibility = Visibility.Hidden;
        }
        
        public void HandleWebLinkButtonClicked(object sender, MouseEventArgs e)
        {
            if (!string.IsNullOrEmpty(m_url))
            {
                Process.Start(m_url);
            }
        }

        public void HandleScrollUpButtonClicked(object sender, RoutedEventArgs e)
        {
            m_contentContainer.ScrollToVerticalOffset(m_contentContainer.VerticalOffset - 10);
        }

        public void HandleScrollDownButtonClicked(object sender, RoutedEventArgs e)
        {
            m_contentContainer.ScrollToVerticalOffset(m_contentContainer.VerticalOffset + 10);
        }
    }
}
