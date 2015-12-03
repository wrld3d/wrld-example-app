using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class DialogViewModel
    {
        public DialogViewModel(string title, string message, string acceptButton, string cancelButton)
        {
            TitleText = title;
            MessageText = message;
            AcceptButtonText = acceptButton;
            CancelButtonText = cancelButton;
        }

        public string TitleText { get; set; }
        public string MessageText { get; set; }
        public string AcceptButtonText { get; set; }
        public string CancelButtonText { get; set; }
    }

    public partial class DialogBox : Window
    {
        public DialogBox(string title, string message, string acceptButton, string cancelButton)
        {
            InitializeComponent();

            DataContext = new DialogViewModel(title, message, acceptButton, cancelButton);
        }

        void OnAcceptButtonClick(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}
