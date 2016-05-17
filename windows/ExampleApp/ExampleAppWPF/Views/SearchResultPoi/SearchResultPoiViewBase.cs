using System;
using System.ComponentModel;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Diagnostics;

namespace ExampleAppWPF
{
    public abstract class SearchResultPoiViewBase : Control, INotifyPropertyChanged
    {
        protected IntPtr m_nativeCallerPointer;
        protected MainWindow m_currentWindow;
        protected FrameworkElement m_mainContainer;
        protected Button m_closeButton;

        protected bool m_closing;

        protected bool m_isOpen;

        private ControlClickHandler m_closeButtonClickHandler = null;

        private const double m_animationTimeMilliseconds = 250;

        public event PropertyChangedEventHandler PropertyChanged;

        public SearchResultPoiViewBase(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            m_currentWindow.SizeChanged += OnWindowResized;

            Visibility = Visibility.Hidden;

            m_isOpen = false;

            Panel.SetZIndex(this, 100);
        }

        private void OnWindowResized(object sender, SizeChangedEventArgs e)
        {
            var mainGrid = m_currentWindow.MainGrid;
            var screenWidth = mainGrid.ActualWidth;

            if (m_isOpen)
            {
                m_mainContainer.RenderTransform = new TranslateTransform((screenWidth / 2) - (m_mainContainer.ActualWidth / 2), 0);
            }
            else
            {
                m_mainContainer.RenderTransform = new TranslateTransform((screenWidth / 2) + (m_mainContainer.ActualWidth / 2), 0);
            }
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public override void OnApplyTemplate()
        {
            m_closeButton = GetTemplateChild("CloseButton") as Button;
            Debug.Assert(m_closeButton != null);

            m_mainContainer.MouseDown += OnContainerMouseDown;

            m_closeButton.Click += HandleCloseButtonClicked;
        }

        private void OnContainerMouseDown(object sender, MouseButtonEventArgs e)
        {
            e.Handled = true;
        }

        protected void HideAll()
        {
            var mainGrid = m_currentWindow.MainGrid;
            var screenWidth = mainGrid.ActualWidth;

            var db = new DoubleAnimation((screenWidth / 2) + (m_mainContainer.ActualWidth / 2), TimeSpan.FromMilliseconds(m_animationTimeMilliseconds));
            db.From = (screenWidth / 2) - (m_mainContainer.ActualWidth / 2);

            var easingFunction = new CubicEase();
            easingFunction.EasingMode = EasingMode.EaseInOut;
            db.EasingFunction = easingFunction;

            m_mainContainer.RenderTransform = new TranslateTransform();
            m_mainContainer.RenderTransform.BeginAnimation(TranslateTransform.XProperty, db);

            m_isOpen = false;
        }

        protected void ShowAll()
        {
            if(m_isOpen)
            {
                return;
            }

            Visibility = Visibility.Visible;

            var mainGrid = m_currentWindow.MainGrid;
            var screenWidth = mainGrid.ActualWidth;

            var db = new DoubleAnimation((screenWidth / 2) - (m_mainContainer.ActualWidth / 2), TimeSpan.FromMilliseconds(m_animationTimeMilliseconds));
            db.From = (screenWidth / 2) + (m_mainContainer.ActualWidth / 2);

            var easingFunction = new CubicEase();
            easingFunction.EasingMode = EasingMode.EaseInOut;
            db.EasingFunction = easingFunction;

            m_mainContainer.RenderTransform = new TranslateTransform();
            m_mainContainer.RenderTransform.BeginAnimation(TranslateTransform.XProperty, db);

            m_isOpen = true;
        }

        private void HandleCloseButtonClicked(object sender, RoutedEventArgs e)
        {
            if (!m_closing)
            {
                m_closing = true;
                ExampleApp.SearchResultPoiViewCLI.CloseButtonClicked(m_nativeCallerPointer);
            }
        }

        public abstract void DisplayPoiInfo(Object modelObject, bool isPinned);

        public virtual void DismissPoiInfo()
        {
            HideAll();
        }

        public abstract void UpdateImageData(string url, bool hasImage, byte[] imgData);
        
        protected static BitmapImage LoadImageFromByteArray(byte[] imageData)
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
    }
}
