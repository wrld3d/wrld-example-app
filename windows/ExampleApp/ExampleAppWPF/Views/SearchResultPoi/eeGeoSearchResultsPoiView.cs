using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

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
        private string m_humanReadableCategoriesText;
        private ImageSource m_categoryIcon;
        private ImageSource m_ratingsImage;
        private Visibility m_ratingCountVisibility;
        private string m_url;
        private FrameworkElement m_reviewsIcon;

        private ControlClickHandler m_yelpReviewImageClickHandler;
        
        //public string PhoneText
        //{
        //    get
        //    {
        //        return m_phoneText;
        //    }
        //    set
        //    {
        //        m_phoneText = value;
        //        OnPropertyChanged("PhoneText");
        //    }
        //}
        //public string AddressText
        //{
        //    get
        //    {
        //        return m_addressText;
        //    }
        //    set
        //    {
        //        m_addressText = value;
        //        OnPropertyChanged("AddressText");
        //    }
        //}

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
        public string HumanReadableCategoriesText
        {
            get
            {
                return m_humanReadableCategoriesText;
            }
            set
            {
                m_humanReadableCategoriesText = value;
                OnPropertyChanged("HumanReadableCategoriesText");
            }
        }
        
        public ImageSource CategoryIcon
        {
            get
            {
                return m_categoryIcon;
            }
            set
            {
                m_categoryIcon = value;
                OnPropertyChanged("CategoryIcon");
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
            base.OnApplyTemplate();

            m_titleView = (TextBlock)GetTemplateChild("Title");
            
            m_poiImage = (Image)GetTemplateChild("PoiImage");

            var yelpButton = (Image)GetTemplateChild("WebVendorLinkStyle");

            m_mainContainer = (FrameworkElement)GetTemplateChild("SearchresultsPoiViewContainer");

            m_reviewsIcon = (FrameworkElement)GetTemplateChild("ReviewsIcon");

            var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;
            var screenWidth = mainGrid.ActualWidth;

            m_yelpReviewImageClickHandler = new ControlClickHandler(yelpButton, HandleWebLinkButtonClicked);
        }
        
        public override void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            ExampleApp.SearchResultModelCLI model = modelObject as ExampleApp.SearchResultModelCLI;

            m_closing = false;

            TitleText = model.Title;
            //AddressText = model.Subtitle.Replace(",", Environment.NewLine);
            //PhoneText = ;
            HumanReadableCategoriesText = string.Join(Environment.NewLine, model.HumanReadableCategories) + model.Category;
            ReviewText = model.Subtitle;
            CategoryIcon = SearchResultPoiViewIconProvider.GetIconForCategory(model.Category);

            m_isPinned = isPinned;
            OnPropertyChanged("IsPinned");

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
