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
    public class SwallowPersonSearchResultsPoiView : Control, ISearchResultPoiView
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;
        private Image m_portraitImage = null;

        private bool m_closing;
        private bool m_isPinned;

        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowPersonResultModel m_swallowPersonModel;

        public bool IsPinned
        {
            get
            {
                return m_isPinned;
            }
            set
            {
                HandleTogglePinnedClikced(ref m_isPinned, ref value);
            }
        }

        public string TitleText { get; set; }
        public string JobTitle { get; set; }
        public string WorkingGroup { get; set; }
        public string OfficeLocation { get; set; }
        public string DeskCode { get; set; }
        
        static SwallowPersonSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SwallowPersonSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(SwallowPersonSearchResultsPoiView)));
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            Image closeButton = (Image)GetTemplateChild("CloseButton");
            closeButton.MouseLeftButtonDown += HandleCloseButtonClicked;

            m_portraitImage = (Image)GetTemplateChild("PortraitImage");
        }

        public SwallowPersonSearchResultsPoiView(IntPtr nativeCallerPointer)
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
            m_model = modelObject as ExampleApp.SearchResultModelCLI;

            m_swallowPersonModel = SwallowPersonResultModel.FromJson(m_model.GetJsonData());
            
            m_closing = false;

            TitleText = m_swallowPersonModel.Name;
            JobTitle = m_swallowPersonModel.JobTitle;
            WorkingGroup = m_swallowPersonModel.WorkingGroup;
            OfficeLocation = m_swallowPersonModel.OfficeLocation;
            DeskCode = m_swallowPersonModel.DeskCode;

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
            m_portraitImage.Source = LoadImageFromByteArray(imgData);
            m_portraitImage.Visibility = Visibility.Visible;
        }

        public void HandleCloseClicked(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            ExampleApp.SearchResultPoiViewCLI.CloseButtonClicked(m_nativeCallerPointer);
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
