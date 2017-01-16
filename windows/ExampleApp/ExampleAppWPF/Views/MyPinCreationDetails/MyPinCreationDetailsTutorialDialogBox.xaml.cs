using System.Windows;

namespace ExampleAppWPF
{
    public class MyPinCreationDetailsTutorialDialogViewModel
    {
        public MyPinCreationDetailsTutorialDialogViewModel(string title, string message)
        {
            TitleText = title;
            MessageText = message;
        }

        public string TitleText { get; set; }
        public string MessageText { get; set; }
    }

    public partial class MyPinCreationDetailsTutorialDialogBox : Window
    {
        public MyPinCreationDetailsTutorialDialogBox(string title, string message)
        {
            InitializeComponent();

            DataContext = new MyPinCreationDetailsTutorialDialogViewModel(title, message);
        }

        void OnCancelButtonClick(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}