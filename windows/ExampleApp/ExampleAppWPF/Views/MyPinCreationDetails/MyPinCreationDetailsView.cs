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
using System.Windows.Input;

namespace ExampleAppWPF
{
    class MyPinCreationDetailsView : Control
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;
        
        protected Image m_takePhotoButton = null;
        protected Button m_selectFromGalleryButton = null;
        protected Button m_submitButton = null;
        protected Button m_closeButton = null;
        protected Image m_poiImage = null;
        protected TextBox m_title = null;
        protected TextBox m_description = null;
        protected CheckBox m_shouldShareButton = null;
        protected TextBlock m_termsAndConditionsLink = null;
        protected ScrollViewer m_scrollSection = null;

        private byte[] m_imageBuffer = null;
        private Uri m_currentImageUri = null;

        private int JPEG_QUALITY = 90;
        private string TERMS_AND_CONDITIONS_LINK = "http://eegeo.com/tos";

        private ImageSource m_prevSource;

        private System.Windows.Documents.Hyperlink m_tosLink;

        private MyPinCreationDetailsTutorialDialogBox m_tutorialDialogBox;
        private Button m_tutorialCancelButton;
        private int m_tutorialViewCount = 0;
        private double m_tutorialTopMargin = 0;

        private bool m_isInKioskMode;

        static MyPinCreationDetailsView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MyPinCreationDetailsView), new FrameworkPropertyMetadata(typeof(MyPinCreationDetailsView)));
        }

        public MyPinCreationDetailsView(IntPtr nativeCallerPointer, Boolean isInKioskMode)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            m_isInKioskMode = isInKioskMode;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            Visibility = Visibility.Hidden;
        }

        void Destroy()
        {
            m_closeButton.Click -= OnCloseClick;
            m_selectFromGalleryButton.Click -= OnSelectFromGalleryClick;
            m_submitButton.Click -= OnSubmitClick;
            m_tosLink.Click -= OnHyperlinkClick;
            m_description.ManipulationBoundaryFeedback -= OnDescriptionViewBoundaryFeedback;

            m_currentWindow.MainGrid.Children.Remove(this);

            RemoveTutorialDialog();
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
            m_submitButton = CheckAndGetProperty(m_isInKioskMode ? "ConfirmKioskButton" : "ConfirmButton") as Button;
            m_selectFromGalleryButton = CheckAndGetProperty("AddImageButton") as Button;
            m_poiImage = CheckAndGetProperty("SelectedImage") as Image;
            m_tosLink = CheckAndGetProperty("TermsLink") as System.Windows.Documents.Hyperlink;

            m_prevSource = m_poiImage.Source;

            m_closeButton = CheckAndGetProperty(m_isInKioskMode ? "CloseKioskButton" : "CloseButton") as Button;
            m_closeButton.Click += OnCloseClick;
            m_selectFromGalleryButton.Click += OnSelectFromGalleryClick;
            m_submitButton.Click += OnSubmitClick;
            m_tosLink.Click += OnHyperlinkClick;

            m_description.ManipulationBoundaryFeedback += OnDescriptionViewBoundaryFeedback;

            Thickness detailsViewMargin = (Thickness)Application.Current.Resources["PinCreationDetailsMargin"];
            if (detailsViewMargin != null)
            {
                m_tutorialTopMargin = detailsViewMargin.Top;
            }
        }

        private void OnDescriptionViewBoundaryFeedback(object sender, ManipulationBoundaryFeedbackEventArgs e)
        {
            e.Handled = true;
        }

        private void OnHyperlinkClick(object sender, RoutedEventArgs e)
        {
            Process.Start(new ProcessStartInfo("http://www.eegeo.com/tos/"));
            e.Handled = true;
        }

        private void OnSelectFromGalleryClick(object sender, RoutedEventArgs e)
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
                catch(NotSupportedException ex)
                {
                    m_imageBuffer = null;
                    return;
                }
            }
        }

        private void OnSubmitClick(object sender, RoutedEventArgs e)
        {
            if(m_isInKioskMode && m_tutorialViewCount == 0)
            {
                ++m_tutorialViewCount;
                ShowTutorialDialog();
            }
            else
            {
                ExampleApp.MyPinCreationDetailsViewCLI.SubmitButtonpressed(m_nativeCallerPointer);
            }
        }

        private void OnCloseClick(object sender, RoutedEventArgs e)
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
            m_imageBuffer = null;
        }

        public void Dismiss()
        {
            Visibility = Visibility.Hidden;
            m_currentWindow.EnableInput();

            RemoveTutorialDialog();
        }

        private void ShowTutorialDialog()
        {
            Dismiss();

            m_tutorialDialogBox = new MyPinCreationDetailsTutorialDialogBox("Pin Created", "Your pin has been created.");
            m_tutorialDialogBox.Owner = m_currentWindow;
            Point pos = m_currentWindow.PointToScreen(new Point((m_currentWindow.ActualWidth - m_tutorialDialogBox.Width) / 2, m_tutorialTopMargin));
            m_tutorialDialogBox.Left = pos.X;
            m_tutorialDialogBox.Top = pos.Y;
            m_tutorialDialogBox.Show();

            m_tutorialCancelButton = (Button)m_tutorialDialogBox.FindName("CancelButton");
            m_tutorialCancelButton.Click += CancelTutorialDialog;
        }

        private void CancelTutorialDialog(object sender, EventArgs e)
        {
            ExampleApp.MyPinCreationDetailsViewCLI.SubmitButtonpressed(m_nativeCallerPointer);

            RemoveTutorialDialog();
        }

        private void RemoveTutorialDialog()
        {
            if (m_tutorialCancelButton != null)
            {
                m_tutorialCancelButton.Click -= CancelTutorialDialog;
                m_tutorialCancelButton = null;
            }

            if (m_tutorialDialogBox != null)
            {
                m_tutorialDialogBox.Close();
                m_tutorialDialogBox = null;
            }
        }

        public void ResetTutorialViewCount()
        {
            m_tutorialViewCount = 0;
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
            return m_description.Text;
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
