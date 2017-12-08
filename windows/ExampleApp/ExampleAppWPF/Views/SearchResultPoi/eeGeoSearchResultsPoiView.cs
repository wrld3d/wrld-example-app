using System;
using System.Windows;
using System.Windows.Controls;
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
        private string m_subTitleText;
        private string m_descriptionText;
        private ImageSource m_qrCodeImage;
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
        private WrapPanel m_socialLinkIconsContainer;
        private Border m_detailsDivider;
        private Border m_tagsDivider;
        private Border m_poiImageDivider;
        private Grid m_previewImageSpinner;
        private WebBrowser m_webBrowser;
        private bool m_webBrowserSelected;
        private double m_contentContainerLastScrollY;
        private double m_webBrowserOriginalHeight;
        private TextBlock m_subTitle;
        private Grid m_titlesGrid;
        private StackPanel m_qrCodeContainer;
        private ImageSource m_placeholderImage;

        private double m_imageContainerHeight;
        private double m_defaultWebViewHeight;
        private double m_maxWebViewHeight;

        private Visibility m_detailsDividerVisibility;

        private int m_qrCodeMaxSize;
        private bool m_webBrowserLoaded;

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

                QRCodeImage = ViewHelpers.GetQRCodeBitmapSourceFromURL(m_webAddressText, m_qrCodeMaxSize);
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
        public string SubTitleText
        {
            get
            {
                return m_subTitleText;
            }
            set
            {
                m_subTitleText = value;
                OnPropertyChanged("SubTitleText");
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
        public ImageSource QRCodeImage
        {
            get
            {
                return m_qrCodeImage;
            }
            set
            {
                m_qrCodeImage = value;
                OnPropertyChanged("QRCodeImage");
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

        public eeGeoSearchResultsPoiView(IntPtr nativeCallerPointer, bool isInKioskMode)
            : base(nativeCallerPointer, isInKioskMode)
        {
        }

        public override void OnApplyTemplate()
        {
            m_titleView = (TextBlock)GetTemplateChild("Title");
            
            m_poiImage = (Image)GetTemplateChild("PoiImage");
            m_placeholderImage = m_poiImage.Source;

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

            m_previewImageSpinner = (Grid)GetTemplateChild("PreviewImageSpinner");

            m_webBrowser = (WebBrowser)GetTemplateChild("WebBrowser");
            m_webBrowser.LoadCompleted += (OnWebPageLoaded);

            m_subTitle = (TextBlock)GetTemplateChild("SubTitle");

            m_titlesGrid = (Grid)GetTemplateChild("TitlesGrid");

            m_qrCodeContainer = (StackPanel)GetTemplateChild("QRCodeContainer");

            m_imageContainerHeight = (double)Application.Current.Resources["EegeoPOIViewImageContainerHeight"];

            m_defaultWebViewHeight = (double)Application.Current.Resources["EegeoPOIViewDetailsWebViewDefaultHeight"];

            m_maxWebViewHeight = (double)Application.Current.Resources["EegeoPOIViewDetailsWebViewMaxHeight"];

            m_detailsDividerVisibility = (Visibility)Application.Current.Resources["EegeoPOIViewDetailsWebLinksVisibility"];

            var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;
            var screenWidth = mainGrid.ActualWidth;
            m_webBrowserSelected = false;
            m_webBrowserLoaded = false;


            m_contentContainerLastScrollY = m_poiImageContainer.Height;
            m_webBrowserOriginalHeight = m_poiImageContainer.Height;

            m_qrCodeMaxSize = (int)((double)Application.Current.Resources["EegeoPOIViewQRCodeImageSize"]);

            base.OnApplyTemplate();
        }

        private void OnWebPageLoaded(object sender, NavigationEventArgs e)
        {

            m_webBrowserLoaded = true;

            WebBrowser wb = (WebBrowser)sender;
           
            dynamic doc = wb.Document;
             var url = doc.url as string;
             if (url != null && url.StartsWith("res://ieframe.dll"))
             {
                wb.NavigateToString(Properties.Resources.page_not_found);
             }

             else if(m_webBrowserSelected)
             {
                 string script = "document.body.style.overflow ='hidden'";
                 wb.InvokeScript("execScript", new Object[] { script, "JavaScript" });
                 wb.Visibility = Visibility.Visible;
             }
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
            if (TryCreateWebLink(m_webAddressText, out uri))
            {
                System.Diagnostics.Process.Start(uri.ToString());
            }
        }

        protected override void OnSearchResultsScrolled(object sender, RoutedEventArgs e)
        {
            double newBrowserHeight = m_webBrowserOriginalHeight - m_contentContainer.VerticalOffset;

            if (newBrowserHeight < 0)
            {
                newBrowserHeight = 0;
            }

            if (newBrowserHeight > m_maxWebViewHeight)
            {
                newBrowserHeight = m_maxWebViewHeight;
            }

            m_webBrowser.Height = newBrowserHeight;

            var htmlDoc = m_webBrowser.Document as mshtml.HTMLDocument;
            double webBrowserScrollBy = m_contentContainerLastScrollY - newBrowserHeight;
            if (htmlDoc != null)
            {
                htmlDoc.parentWindow.scrollBy(0, (int)webBrowserScrollBy);
            }

            m_contentContainerLastScrollY = newBrowserHeight;

            base.OnSearchResultsScrolled(sender, e);
        }

        private void DisplayPoiImage(bool display)
        {
            m_poiImageContainer.Visibility = display ? Visibility.Visible : Visibility.Collapsed;
            m_poiImage.Visibility = display ? Visibility.Visible : Visibility.Collapsed;
            m_poiImageDivider.Visibility = display ? Visibility.Visible : Visibility.Collapsed;
        }

        private void HandleNoWebView(EegeoResultModel eegeoResultModel)
        {
            m_webBrowser.Visibility = Visibility.Collapsed;
            m_webBrowserSelected = false;
            StopWebBrowser();

            if (eegeoResultModel.ImageUrl != null)
            {
                m_poiImage.Source = m_placeholderImage;
                DisplayPoiImage(true);
            }
            else
            {
                DisplayPoiImage(false);
            }
        }

        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            ExampleApp.SearchResultModelCLI model = modelObject as ExampleApp.SearchResultModelCLI;

            EegeoResultModel eegeoResultModel = EegeoResultModel.FromResultModel(model);
            m_closing = false;
            m_webBrowserSelected = false;
            m_titlesGrid.RowDefinitions[1].Height = new GridLength(1, GridUnitType.Star);
            m_poiImageContainer.Height = m_imageContainerHeight;
            bool webViewUrlIsValid = false;
            m_poiImageContainer.Visibility = Visibility.Visible;
            m_poiImage.Visibility = Visibility.Collapsed;
            m_poiImageDivider.Visibility = Visibility.Visible;

            m_webBrowserLoaded = false;

            m_contentContainer.ScrollToTop();

            if (eegeoResultModel.WebViewUrl != null)
            {
                m_webBrowser.Visibility = Visibility.Hidden;
                m_webBrowserSelected = true;
                Uri hyperlink;
                webViewUrlIsValid = Uri.TryCreate(eegeoResultModel.WebViewUrl, UriKind.Absolute, out hyperlink)
                    && (hyperlink.Scheme == Uri.UriSchemeHttp || hyperlink.Scheme == Uri.UriSchemeHttps);

                if (webViewUrlIsValid)
                {
                    Uri url = new Uri(eegeoResultModel.WebViewUrl);
                   

                    m_webBrowser.Source = url;

                    if (eegeoResultModel.WebViewHeight != 0)
                    {
                        m_webBrowserOriginalHeight = eegeoResultModel.WebViewHeight;
                        m_poiImageContainer.Height = eegeoResultModel.WebViewHeight;

                        if (eegeoResultModel.WebViewHeight > m_maxWebViewHeight)
                        {
                            m_webBrowserOriginalHeight = m_maxWebViewHeight;
                            m_poiImageContainer.Height = m_maxWebViewHeight;
                        }
                    }
                    else
                    {
                        m_webBrowserOriginalHeight = m_defaultWebViewHeight;
                        m_poiImageContainer.Height = m_defaultWebViewHeight;
                    }
                }
                else
                {
                    HandleNoWebView(eegeoResultModel);
                }
            }
            else
            {
                HandleNoWebView(eegeoResultModel);
            }
            

            if (!m_webBrowserSelected)
            {
                Uri uri;
                if ((eegeoResultModel.ImageUrl != null || webViewUrlIsValid) && TryCreateWebLink(eegeoResultModel.ImageUrl, out uri))
                {
                    m_poiImageDivider.Visibility = Visibility.Visible;
                }
                else
                {
                    m_poiImageContainer.Visibility = Visibility.Collapsed;
                    m_poiImageDivider.Visibility = Visibility.Collapsed;
                }
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
                m_qrCodeContainer.Visibility = Visibility.Visible;
            }
            else
            {
                m_webDetailsContainer.Visibility = Visibility.Collapsed;
                m_qrCodeContainer.Visibility = Visibility.Collapsed;
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

            if (shouldCollapseDivider || m_detailsDividerVisibility == Visibility.Collapsed)
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
            if (model.Subtitle != "")
            {
                SubTitleText = model.Subtitle;
            }
            else
            {
                m_titlesGrid.RowDefinitions[1].Height = new GridLength(0);
            }

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

            TagIcon = IconProvider.GetIconForTag(model.IconKey, m_isInKioskMode);
           
            ShowAll();
           
            base.DisplayCustomPoiInfo(modelObject);
        }
        
        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            if (hasImage && !m_webBrowserSelected)
            {
                var imageSource = LoadImageFromByteArray(imgData);

                if (imageSource == null)
                {
                    DisplayPoiImage(false);
                }
                else
                {
                    m_poiImage.Source = imageSource;
                    DisplayPoiImage(true);
                }
            }

            m_previewImageSpinner.Visibility = Visibility.Collapsed;
        }


        
        protected override void OnHideAnimationCompleted(object s, EventArgs e)
        {
             if (m_webBrowserLoaded)
             {
                 StopWebBrowser();
             }
        }
        
        private void StopWebBrowser()
        {
             m_webBrowser.NavigateToString("about:blank");
        }
    }
}
