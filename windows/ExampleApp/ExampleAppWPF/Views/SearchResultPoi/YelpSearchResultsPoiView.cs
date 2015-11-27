using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class YelpSearchResultsPoiView : Control, ISearchResultPoiView
    {
        private IntPtr m_nativeCallerPointer;
        private TextBlock m_titleView = null;
        private Image m_poiImage = null;
        private Image m_closeButton = null;
        private bool m_isPinned;
        private MainWindow m_currentWindow;
        private ToggleButton m_togglePinned;
        
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

        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

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

        public bool IsPinned
        {
            get
            {
                return m_isPinned;
            }
            set
            {
                HandleTogglePinnedClikced(ref m_isPinned, ref value);
                OnPropertyChanged("IsPinned");
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

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_titleView = (TextBlock)GetTemplateChild("SearchResultPoiViewTitle");
            m_closeButton = (Image)GetTemplateChild("SearchResultPoiViewCloseButton");
            m_closeButton.MouseLeftButtonDown += HandleCloseButtonClicked;

            m_poiImage = (Image)GetTemplateChild("SearchResultPoiViewImage");

            m_togglePinned = (ToggleButton)GetTemplateChild("SearchResultPoiViewTogglePinnedButton");

            var yelpButton = (Image)GetTemplateChild("SearchResultPoiViewWebVendorLinkStyle");
            yelpButton.PreviewMouseLeftButtonDown += (s, e) => HandleWebLinkButtonClicked();
            
        }

        public YelpSearchResultsPoiView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            HideAll();
        }
        
        private void HideAll()
        {
            Visibility = Visibility.Hidden;
            m_currentWindow.EnableInput();
        }

        private void ShowAll()
        {
            Visibility = Visibility.Visible;
            m_currentWindow.DisableInput();
        }

        private bool m_closing;

        private void HandleCloseButtonClicked(object sender, MouseButtonEventArgs e)
        {
            if (!m_closing)
            {
                m_closing = true;
                ExampleApp.SearchResultPoiViewCLI.CloseButtonClicked(m_nativeCallerPointer);
            }            
        }
        
        public void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            ExampleApp.SearchResultModelCLI model = modelObject as ExampleApp.SearchResultModelCLI;

            YelpResultModel yelpResultModel = YelpResultModel.FromResultModel(model);

            m_closing = false;

            TitleText = model.GetTitle();
            AddressText = model.GetSubtitle().Replace(",", Environment.NewLine);
            PhoneText = yelpResultModel.Phone;
            HumanReadableCategoriesText = string.Join(Environment.NewLine, model.GetHumanReadableCategories());
            ReviewText = string.Join(Environment.NewLine, yelpResultModel.Reviews);
            CategoryIcon = StartupResourceLoader.GetBitmap(SearchResultCategoryMapper.GetIconImageName(model.GetCategory()));
            PoiViewRatingCountText = yelpResultModel.ReviewCount.ToString();
            RatingsImage = null;

            if (yelpResultModel.ReviewCount > 0 && !string.IsNullOrEmpty(yelpResultModel.RatingsImageUrl))
            {
                RatingsImage = new BitmapImage(new Uri(string.Format("pack://application:,,,/ExampleAppWPF;component/Assets/{0}.png", yelpResultModel.RatingsImageUrl)));
            }

            RatingCountVisibility = string.IsNullOrEmpty(yelpResultModel.ImageUrl) && !string.IsNullOrEmpty(yelpResultModel.RatingsImageUrl) && yelpResultModel.ReviewCount > 0 ? Visibility.Visible : Visibility.Collapsed;
            Url = yelpResultModel.WebUrl;

            IsPinned = isPinned;

            ShowAll();
        }

        public void DismissPoiInfo()
        {
            HideAll();
        }

        private static BitmapImage LoadImageFromByteArray(byte[] imageData)
        {
            if (imageData == null || imageData.Length == 0)
            {
                return null;
            }

            var image = new BitmapImage();

            using (var mem = new MemoryStream(imageData))
            {
                mem.Position = 0;
                image.BeginInit();
                image.CreateOptions = BitmapCreateOptions.PreservePixelFormat;
                image.CacheOption = BitmapCacheOption.OnLoad;
                image.UriSource = null;
                image.StreamSource = mem;
                image.EndInit();
            }

            image.Freeze();

            return image;
        }

        public void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            m_poiImage.Source = LoadImageFromByteArray(imgData);
            m_poiImage.Visibility = Visibility.Visible;
        }

        public void HandleCloseClicked(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            ExampleApp.SearchResultPoiViewCLI.CloseButtonClicked(m_nativeCallerPointer);
        }

        public void HandleWebLinkButtonClicked()
        {
            if (!string.IsNullOrEmpty(m_url))
            {
                Process.Start(m_url);
            }
        }
        public void HandleTogglePinnedClikced(ref bool oldValue, ref bool newValue)
        {
            if (oldValue != newValue)
            {
                if (!newValue)
                {
                    if (ShowRemovePinDialog() == MessageBoxResult.Yes)
                    {
                        ExampleApp.SearchResultPoiViewCLI.TogglePinnedButtonClicked(m_nativeCallerPointer);
                        oldValue = newValue;
                    }
                }
                else
                {
                    ExampleApp.SearchResultPoiViewCLI.TogglePinnedButtonClicked(m_nativeCallerPointer);
                    oldValue = newValue;
                }                
            }
        }

        public MessageBoxResult ShowRemovePinDialog()
        {
            return MessageBox.Show("Are you sure you want to remove this pin?", "Remove Pin", MessageBoxButton.YesNo, MessageBoxImage.Question);
        }
    }
}
