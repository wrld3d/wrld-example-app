using System.Windows;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public class WatermarkViewDialogViewModel
    {
        

        public WatermarkViewDialogViewModel(string title, string message, string acceptButton, string cancelButton, ImageSource watermarkLogo, string watermarkUrl, int maxQRCodeSize)
        {
            TitleText = title;
            MessageText = message;
            AcceptButtonText = acceptButton;
            CancelButtonText = cancelButton;
            WatermarkLogoImageSource = watermarkLogo;
            WatermarkQRCodeImageSource = ViewHelpers.GetQRCodeBitmapSourceFromURL(watermarkUrl, maxQRCodeSize);
        }

        public string TitleText { get; set; }
        public string MessageText { get; set; }
        public string AcceptButtonText { get; set; }
        public string CancelButtonText { get; set; }
        public ImageSource WatermarkLogoImageSource { get; set; }
        public ImageSource WatermarkQRCodeImageSource { get; set; }
    }

    public partial class WatermarkViewDialogBox : Window
    {
        public delegate void ButtonClickHandler(object sender, RoutedEventArgs e, bool result);
        public event ButtonClickHandler ButtonClicked;
        public bool m_modal;

        public WatermarkViewDialogBox(string title, string message, string acceptButton, string cancelButton, ImageSource watermarkLogo, string watermarkUrl, int maxQRCodeSize, bool modal = true)
        {
            m_modal = modal;

            InitializeComponent();

            DataContext = new WatermarkViewDialogViewModel(title, message, acceptButton, cancelButton, watermarkLogo, watermarkUrl, maxQRCodeSize);
        }

        void OnAcceptButtonClick(object sender, RoutedEventArgs e)
        {
            if (m_modal)
            {
                DialogResult = true;
            }
            else
            {
                ButtonClicked?.Invoke(sender, e, true);
                Close();
            }
        }

        void OnCancelButtonClick(object sender, RoutedEventArgs e)
        {
            if (!m_modal)
            {
                ButtonClicked?.Invoke(sender, e, false);
                Close();
            }
        }
    }
}
