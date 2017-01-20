using System.Windows;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public class WatermarkViewDialogViewModel
    {
        public WatermarkViewDialogViewModel(string title, string message, string acceptButton, string cancelButton, ImageSource watermarkLogo)
        {
            TitleText = title;
            MessageText = message;
            AcceptButtonText = acceptButton;
            CancelButtonText = cancelButton;
            WatermarkLogoImageSource = watermarkLogo;
        }

        public string TitleText { get; set; }
        public string MessageText { get; set; }
        public string AcceptButtonText { get; set; }
        public string CancelButtonText { get; set; }
        public ImageSource WatermarkLogoImageSource { get; set; }
    }

    public partial class WatermarkViewDialogBox : Window
    {
        public WatermarkViewDialogBox(string title, string message, string acceptButton, string cancelButton, ImageSource watermarkLogo)
        {
            InitializeComponent();

            DataContext = new WatermarkViewDialogViewModel(title, message, acceptButton, cancelButton, watermarkLogo);
        }

        void OnAcceptButtonClick(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}
