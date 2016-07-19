using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public abstract class SearchResultPoiViewBase : Control, INotifyPropertyChanged
    {
        protected IntPtr m_nativeCallerPointer;
        protected MainWindow m_currentWindow;
        protected FrameworkElement m_mainContainer;
        protected Button m_closeButton;

        protected bool m_closing;
        protected bool m_isPinned;

        protected bool m_isOpen;

        private ControlClickHandler m_closeButtonClickHandler = null;

        private const double m_animationTimeMilliseconds = 250;

        public event PropertyChangedEventHandler PropertyChanged;

        private static bool m_isAnyPOIOpen = false;

        public bool IsPinned
        {
            get
            {
                return m_isPinned;
            }

            set
            {
                if (HandleTogglePinnedClicked(ref m_isPinned, !m_isPinned))
                {
                    OnPropertyChanged("IsPinned");
                }
            }
        }

        public static bool IsAnyPOIOpen()
        {
            return m_isAnyPOIOpen;
        }

        public SearchResultPoiViewBase(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            Application.Current.MainWindow.SizeChanged += OnWindowResized;

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

            TouchMove += OnTouchMove;
        }

        private void OnTouchMove(object sender, TouchEventArgs e)
        {
            e.Handled = true;
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
            m_isAnyPOIOpen = false;
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
            m_isAnyPOIOpen = true;
        }

        private void HandleCloseButtonClicked(object sender, RoutedEventArgs e)
        {
            if (!m_closing)
            {
                m_closing = true;
                ExampleApp.SearchResultPoiViewCLI.CloseButtonClicked(m_nativeCallerPointer);
            }
        }
        protected abstract void DisplayCustomPoiInfo(Object modelObject);

        public void DisplayPoiInfo(Object modelObject, bool isPinned)
        {
            // set the pinned state from the native model without feeding back into the native model
            if (m_isPinned != isPinned)
            {
                m_isPinned = isPinned;
                OnPropertyChanged("IsPinned");
            }

            DisplayCustomPoiInfo(modelObject);
        }

        public virtual void DismissPoiInfo()
        {
            HideAll();
        }

        public abstract void UpdateImageData(string url, bool hasImage, byte[] imgData);

        private void HandleCloseClicked(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            ExampleApp.SearchResultPoiViewCLI.CloseButtonClicked(m_nativeCallerPointer);
        }

        private bool HandleTogglePinnedClicked(ref bool oldValue, bool newValue)
        {
            if (oldValue != newValue)
            {
                if (!newValue)
                {
                    if (ShowRemovePinDialog() == true)
                    {
                        ExampleApp.SearchResultPoiViewCLI.TogglePinnedButtonClicked(m_nativeCallerPointer);
                        oldValue = newValue;

                        return true;
                    }
                }
                else
                {
                    ExampleApp.SearchResultPoiViewCLI.TogglePinnedButtonClicked(m_nativeCallerPointer);
                    oldValue = newValue;

                    return true;
                }
            }

            return false;
        }

        private bool ShowRemovePinDialog()
        {
            DialogBox dialogBox = new DialogBox("Remove Pin", "Are you sure you want to remove this pin?", "Yes", "No");
            dialogBox.Owner = m_currentWindow;

            m_currentWindow.SetOpacity(MainWindow.OpacityOnPopup);

            bool? result = dialogBox.ShowDialog();

            m_currentWindow.SetOpacity(1.0f);

            if (result == null)
            {
                return false;
            }

            return (bool)result;
        }

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
