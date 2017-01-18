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
        public delegate void ButtonClickHandler(object sender, RoutedEventArgs e, bool result);
        public event ButtonClickHandler ButtonClicked;
        public bool m_modal;

        public DialogBox(string title, string message, string acceptButton, string cancelButton, bool modal=true)
        {
            m_modal = modal;

            InitializeComponent();

            DataContext = new DialogViewModel(title, message, acceptButton, cancelButton);
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
            if (m_modal)
            {
                ButtonClicked?.Invoke(sender, e, false);
                Close();
            }
        }
    }
}
