using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Shapes;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.IO;

namespace ExampleAppWPF
{
    class MyPinDetailsView : Control
    {
        private MainWindow m_currentWindow;
        private IntPtr m_nativeCallerPointer;
        
        private TextBlock m_titleView = null;
        private TextBlock m_descriptionView = null;
        private TextBlock m_descriptHeader = null;
        private TextBlock m_imageHeader = null;
        private Image m_imageView = null;
        private Button m_closeButton = null;
        private Button m_removeButton = null;

        private float m_imageWidth;

        static MyPinDetailsView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MyPinDetailsView), new FrameworkPropertyMetadata(typeof(MyPinDetailsView)));
        }

        public MyPinDetailsView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            Visibility = Visibility.Hidden;
        }

        void Destroy()
        {
            m_removeButton.Click -= OnDeleteClicked;
            m_closeButton.Click -= OnCloseClicked;

            m_currentWindow.MainGrid.Children.Remove(this);
        }

        private DependencyObject CheckAndGetProperty(string name)
        {
            var prop = GetTemplateChild(name);
            System.Diagnostics.Debug.Assert(prop != null, "Property cannot be found!!");
            return prop;
        }

        public override void OnApplyTemplate()
        {
            m_titleView = (TextBlock)CheckAndGetProperty("Title");
            m_descriptionView = (TextBlock)CheckAndGetProperty("Description");
            m_imageView = (Image)CheckAndGetProperty("Image");
            m_imageHeader = (TextBlock)CheckAndGetProperty("ImageHeader");
            
            m_removeButton = (Button)CheckAndGetProperty("RemovePIN");
            m_closeButton = (Button)CheckAndGetProperty("Close");

            m_removeButton.Click += OnDeleteClicked;
            m_closeButton.Click += OnCloseClicked;
        }

        private void OnDeleteClicked(object sender, RoutedEventArgs e)
        {
            if (ShowRemovePinDialog() == true)
            {
                ExampleApp.MyPinDetailsViewCLI.RemovePinButtonClicked(m_nativeCallerPointer);
            }
        }

        private void OnCloseClicked(object sender, RoutedEventArgs e)
        {
            ExampleApp.MyPinDetailsViewCLI.CloseButtonClicked(m_nativeCallerPointer);
        }

        public void Display(string title, string description, string imagePath)
        {
            Visibility = Visibility.Visible;

            m_titleView.Text = title;
            m_descriptionView.Text = description;

            if (imagePath.Length > 0)
            {
                StartupResourceLoader.LoadImage(imagePath);
                var src = StartupResourceLoader.GetBitmap(imagePath);

                if(src != null)
                {
                    m_imageHeader.Visibility = Visibility.Visible;
                    m_imageView.Visibility = Visibility.Visible;
                    m_imageView.Source = src;
                    m_imageHeader.Visibility = Visibility.Visible;
                    m_imageView.Visibility = Visibility.Visible;
                }
                else
                {
                    m_imageHeader.Visibility = Visibility.Hidden;
                    m_imageView.Visibility = Visibility.Hidden;
                }
            }
            else
            {
                m_imageHeader.Visibility = Visibility.Hidden;
                m_imageView.Visibility = Visibility.Hidden;
            }

            m_currentWindow.DisableInput();
        }

        public void Dismiss()
        {
            Visibility = Visibility.Hidden;
            m_currentWindow.EnableInput();
        }

        private bool ShowRemovePinDialog()
        {
            DialogBox dialogBox = new DialogBox("Remove Report", "Are you sure you want to remove this report?", "Yes", "No");
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
    }
}
