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
using System.Diagnostics;
using System.Windows.Navigation;

namespace ExampleAppWPF
{
    class MyPinCreationDetailsView : Control
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;
        
        protected Image m_takePhotoButton = null;
        protected Image m_selectFromGalleryButton = null;
        protected Image m_submitButton = null;
        protected Image m_poiImage = null;
        protected TextBox m_title = null;
        protected TextBox m_description = null;
        protected CheckBox m_shouldShareButton = null;
        protected TextBlock m_termsAndConditionsLink = null;
        protected ScrollViewer m_scrollSection = null;

        private ControlClickHandler m_closeButtonClickHandler = null;
        private ControlClickHandler m_uploadButtonClickHandler = null;

        private byte[] m_imageBuffer = null;
        private Uri m_currentImageUri = null;

        private bool m_acceptButtonMouseDown = false;

        private int JPEG_QUALITY = 90;
        private string TERMS_AND_CONDITIONS_LINK = "http://eegeo.com/tos";

        private ImageSource m_prevSource;

        private System.Windows.Documents.Hyperlink m_tosLink;

        static MyPinCreationDetailsView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MyPinCreationDetailsView), new FrameworkPropertyMetadata(typeof(MyPinCreationDetailsView)));
        }

        public MyPinCreationDetailsView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            Visibility = Visibility.Hidden;
        }

        void Destroy()
        {
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
            m_title = CheckAndGetProperty("TitleBox") as TextBox;
            m_description = CheckAndGetProperty("DescBox") as TextBox;
            m_shouldShareButton = CheckAndGetProperty("ToShare") as CheckBox;
            m_submitButton = CheckAndGetProperty("ConfirmButton") as Image;
            m_selectFromGalleryButton = CheckAndGetProperty("OpenGalleryButton") as Image;
            m_poiImage = CheckAndGetProperty("SelectedImage") as Image;
            m_tosLink = CheckAndGetProperty("TermsLink") as System.Windows.Documents.Hyperlink;

            m_prevSource = m_poiImage.Source;
            m_poiImage.Stretch = Stretch.Uniform;
            
            m_submitButton.MouseLeftButtonDown += OnSubmitClick;
            m_submitButton.MouseLeftButtonUp += OnSubmitClick;

            Image closeButton = CheckAndGetProperty("CloseButton") as Image;
            m_closeButtonClickHandler = new ControlClickHandler(closeButton, OnCloseClick);

            m_uploadButtonClickHandler = new ControlClickHandler(m_selectFromGalleryButton, OnSelectFromGalleryClick);

            m_tosLink.Click += OnHyperlinkClick;
        }

        private void OnHyperlinkClick(object sender, RoutedEventArgs e)
        {
            Process.Start(new ProcessStartInfo("http://www.eegeo.com/tos/"));
            e.Handled = true;
        }

        private void OnSelectFromGalleryClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            System.Windows.Forms.OpenFileDialog dlg = new System.Windows.Forms.OpenFileDialog();

            dlg.Filter = "Image Files(*.bmp;*.jpg;*.jpeg;*.png)|*.bmp;*.jpg;*.jpeg;*.png";

            var result = dlg.ShowDialog();

            if(result == System.Windows.Forms.DialogResult.OK)
            {
                string filename = dlg.FileName;

                try
                {
                    m_imageBuffer = System.IO.File.ReadAllBytes(filename);
                    m_poiImage.Source = new BitmapImage(new Uri(filename));
                }
                catch(System.IO.IOException ex)
                {
                    m_imageBuffer = null;
                    return;
                }
            }
        }

        private void OnSubmitClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            if (e.ButtonState == System.Windows.Input.MouseButtonState.Pressed)
            {
                m_acceptButtonMouseDown = true;
                return;
            }
            else if (e.ButtonState == System.Windows.Input.MouseButtonState.Released && m_acceptButtonMouseDown)
            {
                ExampleApp.MyPinCreationDetailsViewCLI.SubmitButtonpressed(m_nativeCallerPointer);
            }

            m_acceptButtonMouseDown = false;
        }

        private void OnCloseClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            ExampleApp.MyPinCreationDetailsViewCLI.CloseButtonPressed(m_nativeCallerPointer);
        }

        public void Show()
        {
            Visibility = Visibility.Visible;
            m_currentWindow.DisableInput();

            m_title.Text = string.Empty;
            m_description.Text = string.Empty;
            m_shouldShareButton.IsChecked = false;
            m_poiImage.Source = m_prevSource;
        }

        public void Dismiss()
        {
            Visibility = Visibility.Hidden;
            m_currentWindow.EnableInput();
        }

        public string GetTitle()
        {
            if (m_title.Text.Length > 0)
            {
                return m_title.Text;
            }

            return "Untitled";
        }

        public string GetDescription()
        {
            if (m_description.Text.Length > 0)
            {
                return m_description.Text;
            }

            return "No description";
        }

        public bool GetShouldShare()
        {
            if (m_shouldShareButton.IsChecked == null)
                return false;
            else
                return (bool)m_shouldShareButton.IsChecked;

        }

        public byte[] GetImageBuffer()
        {
            return m_imageBuffer;
        }

        public int GetImageBufferSize()
        {
            return m_imageBuffer == null ? 0 : m_imageBuffer.Length;
        }
    }
}
