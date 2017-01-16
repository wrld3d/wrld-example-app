using System.Windows;

namespace ExampleAppWPF
{
    public class MyPinCreationConfirmationTutorialDialogViewModel
    {
        public MyPinCreationConfirmationTutorialDialogViewModel(string title, string message, string acceptButton)
        {
            TitleText = title;
            MessageText = message;
            AcceptButtonText = acceptButton;
        }

        public string TitleText { get; set; }
        public string MessageText { get; set; }
        public string AcceptButtonText { get; set; }
    }

    public partial class MyPinCreationConfirmationTutorialDialogBox : Window
    {
        public MyPinCreationConfirmationTutorialDialogBox(string title, string message, string acceptButton)
        {
            InitializeComponent();

            DataContext = new MyPinCreationConfirmationTutorialDialogViewModel(title, message, acceptButton);
        }

        void OnAcceptButtonClick(object sender, RoutedEventArgs e)
        {
            Close();
        }

        void OnCancelButtonClick(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}