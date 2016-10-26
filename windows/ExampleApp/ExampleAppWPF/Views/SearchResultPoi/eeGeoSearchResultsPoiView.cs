using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Navigation;

namespace ExampleAppWPF
{
    public class eeGeoSearchResultsPoiView : SearchResultPoiViewBase
    {
        private TextBlock m_titleView = null;
        private Image m_poiImage = null;
        
        private string m_phoneText;
        private string m_addressText;
        private string m_webAddressText;
        private string m_titleText;
        private string m_descriptionText;
        private string m_humanReadableTagsText;
        private string m_facebookText;
        private string m_twitterText;
        private string m_emailText;
        private ImageSource m_tagIcon;
        private FrameworkElement m_reviewsIcon;
        private Grid m_phoneDetailsContainer;
        private Grid m_addressDetailsContainer;
        private Grid m_webDetailsContainer;
        private Grid m_descriptionContainer;
        private Grid m_poiImageContainer;
        private Image m_facebookIcon;
        private Image m_twitterIcon;
        private Image m_emailIcon;
        private Image m_linkedInIcon;
        private Image m_slackIcon;
        private Image m_footerFade;
        private WrapPanel m_socialLinkIconsContainer;
        private Border m_detailsDivider;
        private Border m_tagsDivider;
        private Border m_poiImageDivider;
        private ScrollViewer m_contentContainer;
        private Grid m_previewImageSpinner;

        private ControlClickHandler m_yelpReviewImageClickHandler;

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
        public string WebAddressText
        {
            get
            {
                return m_webAddressText;
            }
            set
            {
                m_webAddressText = value;
                OnPropertyChanged("WebAddressText");
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
        public string DescriptionText
        {
            get
            {
                return m_descriptionText;
            }
            set
            {
                m_descriptionText = value;
                OnPropertyChanged("DescriptionText");
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

            m_phoneDetailsContainer = (Grid)GetTemplateChild("PhoneDetailsContainer");

            m_addressDetailsContainer = (Grid)GetTemplateChild("AddressDetailsContainer");

            m_webDetailsContainer = (Grid)GetTemplateChild("WebDetailsContainer");
            m_webDetailsContainer.MouseDown += WebLinkClicked;

            m_facebookIcon = (Image)GetTemplateChild("SocialIcon_FB");
            m_facebookIcon.MouseDown += FacebookIconClick;

            m_twitterIcon = (Image)GetTemplateChild("SocialIcon_Twitter");
            m_twitterIcon.MouseDown += TwitterIconClick;

            m_emailIcon = (Image)GetTemplateChild("SocialIcon_Mail");
            m_emailIcon.MouseDown += EmailIconClick;

            m_linkedInIcon = (Image)GetTemplateChild("SocialIcon_LinkedIn");

            m_slackIcon = (Image)GetTemplateChild("SocialIcon_Slack");

            m_socialLinkIconsContainer = (WrapPanel)GetTemplateChild("SocialLinkIcons");

            m_detailsDivider = (Border)GetTemplateChild("DetailsDivider");

            m_tagsDivider = (Border)GetTemplateChild("TagsDivider");

            m_descriptionContainer = (Grid)GetTemplateChild("DescriptionContainer");

            m_poiImageContainer = (Grid)GetTemplateChild("PoiImageContainer");

            m_poiImageDivider = (Border)GetTemplateChild("PoiImageDivider");

            m_contentContainer = (ScrollViewer)GetTemplateChild("ContentContainer");

            m_contentContainer.ScrollChanged += OnSearchResultsScrolled;

            m_footerFade = (Image)GetTemplateChild("FooterFade");

            m_previewImageSpinner = (Grid)GetTemplateChild("PreviewImageSpinner");

            var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;
            var screenWidth = mainGrid.ActualWidth;
            
            base.OnApplyTemplate();
        }
        // Validating urls here although the url's should be validated in the poi tool before reaching this.
        private bool TryCreateWebLink(string urlText, out Uri uri)
        {
           return Uri.TryCreate(urlText, UriKind.Absolute, out uri)
            && (uri.Scheme == Uri.UriSchemeHttp || uri.Scheme == Uri.UriSchemeHttps);
        }

        private void FacebookIconClick(object sender, MouseButtonEventArgs e)
        {
            Uri uri;
            if (TryCreateWebLink(m_facebookText, out uri))
            {
                System.Diagnostics.Process.Start(uri.ToString());
            }
        }

        private void TwitterIconClick(object sender, MouseButtonEventArgs e)
        {
            Uri uri;
            if (TryCreateWebLink(m_twitterText, out uri))
            {
                System.Diagnostics.Process.Start(uri.ToString());
            }
        }

        private void EmailIconClick(object sender, MouseButtonEventArgs e)
        {
            System.Diagnostics.Process.Start("mailto:" + m_emailText + "?subject=SubjectExample&body=BodyExample ");
        }

        private void WebLinkClicked(object sender, MouseButtonEventArgs e)
        {
            Uri uri;
            if (TryCreateWebLink(m_emailText, out uri))
            {
                System.Diagnostics.Process.Start(uri.ToString());
            }
        }

        private void OnSearchResultsScrolled(object sender, RoutedEventArgs e)
        {
            if (m_contentContainer.VerticalOffset == m_contentContainer.ScrollableHeight)
            {
                m_footerFade.Visibility = Visibility.Hidden;
            }
            else
            {
                m_footerFade.Visibility = Visibility.Visible;
            }
        }

        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            ExampleApp.SearchResultModelCLI model = modelObject as ExampleApp.SearchResultModelCLI;

            EegeoResultModel eegeoResultModel = EegeoResultModel.FromResultModel(model);
            m_closing = false;

            if(eegeoResultModel.ImageUrl != null)
            {
                m_poiImageContainer.Visibility = Visibility.Visible;
                m_poiImageDivider.Visibility = Visibility.Visible;
                m_poiImage.Visibility = Visibility.Hidden;
                m_previewImageSpinner.Visibility = Visibility.Visible;
            }
            else
            {
                m_poiImageContainer.Visibility = Visibility.Collapsed;
                m_poiImageDivider.Visibility = Visibility.Collapsed;
                m_poiImage.Visibility = Visibility.Collapsed;
                m_previewImageSpinner.Visibility = Visibility.Collapsed;
            }

            if (eegeoResultModel.Phone != null)
            {
                PhoneText = eegeoResultModel.Phone;
                m_phoneDetailsContainer.Visibility = Visibility.Visible;
            }
            else
            {
                m_phoneDetailsContainer.Visibility = Visibility.Collapsed;
            }

            if (eegeoResultModel.Address != null)
            {
                AddressText = eegeoResultModel.Address.Replace(", ", Environment.NewLine);
                m_addressDetailsContainer.Visibility = Visibility.Visible;
            }
            else
            {
                AddressText = null;
                m_addressDetailsContainer.Visibility = Visibility.Collapsed;
            }

            if (eegeoResultModel.WebUrl != null)
            {
                WebAddressText = eegeoResultModel.WebUrl;
                m_webDetailsContainer.Visibility = Visibility.Visible;
            }
            else
            {
                m_webDetailsContainer.Visibility = Visibility.Collapsed;
            }

            if (eegeoResultModel.Facebook != null)
            {
                m_facebookIcon.Visibility = Visibility.Visible;
                m_facebookText = eegeoResultModel.Facebook;
            }
            else
            {
                m_facebookIcon.Visibility = Visibility.Collapsed;
            }

            if (eegeoResultModel.Twitter != null)
            {
                m_twitterIcon.Visibility = Visibility.Visible;
                m_twitterText = eegeoResultModel.Twitter;
            }
            else
            {
                m_twitterIcon.Visibility = Visibility.Collapsed;
            }

            if (eegeoResultModel.Email != null)
            {
                m_emailIcon.Visibility = Visibility.Visible;
                m_emailText = eegeoResultModel.Email;
            }
            else
            {
                m_emailIcon.Visibility = Visibility.Collapsed;
            }

            bool shouldCollapseDivider = eegeoResultModel.Facebook == null &&
                eegeoResultModel.Twitter == null &&
                eegeoResultModel.Email == null &&
                eegeoResultModel.Address == null &&
                eegeoResultModel.Phone == null &&
                eegeoResultModel.WebUrl == null;

            if (shouldCollapseDivider)
            {
                m_detailsDivider.Visibility = Visibility.Collapsed;
            }
            else
            {
                m_detailsDivider.Visibility = Visibility.Visible;
            }

            if(eegeoResultModel.Facebook == null && eegeoResultModel.Twitter == null && eegeoResultModel.Email == null)
            {
                m_socialLinkIconsContainer.Visibility = Visibility.Collapsed;
            }
            else
            {
                m_socialLinkIconsContainer.Visibility = Visibility.Visible;
            }

            m_linkedInIcon.Visibility = Visibility.Collapsed;
            m_slackIcon.Visibility = Visibility.Collapsed;
            TitleText = model.Title;

            if (model.HumanReadableTags != null)
            {
                HumanReadableTagsText = string.Join(", ", model.HumanReadableTags);
                m_tagsDivider.Visibility = Visibility.Visible;
            }
            else
            {
                m_tagsDivider.Visibility = Visibility.Collapsed;
            }

            if(eegeoResultModel.Description != null)
            {
                DescriptionText = eegeoResultModel.Description;
                m_descriptionContainer.Visibility = Visibility.Visible;
            }
            else
            {
                m_descriptionContainer.Visibility = Visibility.Collapsed;
            }

            TagIcon = SearchResultPoiViewIconProvider.GetIconForTag(model.IconKey);

            ShowAll();
        }
        
        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            if (hasImage)
            {
                m_poiImage.Source = LoadImageFromByteArray(imgData);
                m_poiImage.Visibility = Visibility.Visible;
                m_poiImageContainer.Visibility = Visibility.Visible;
                m_poiImageDivider.Visibility = Visibility.Visible;
            }
            m_previewImageSpinner.Visibility = Visibility.Hidden;
        }
        
    }
}
