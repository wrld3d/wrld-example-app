using System;
using System.ComponentModel;
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
        public delegate void ButtonClickHandler(object sender, EventArgs e, bool result);
        public event ButtonClickHandler ButtonClicked;
        public bool m_modal;

        public DialogBox(string title, string message, string acceptButton, string cancelButton, bool modal=true)
        {
            m_modal = modal;

            InitializeComponent();

            DataContext = new DialogViewModel(title, message, acceptButton, cancelButton);
        }

        public void ShowWithParentControl(Control parent, ButtonClickHandler cont)
        {
            DependencyPropertyChangedEventHandler close = (o, e) => Close();
            parent.IsVisibleChanged += (o,e) =>
            {
                if (!parent.IsVisible)
                {
                    close(o, e);
                }
            };
            ButtonClicked += (sender, ev, okClicked) =>
            {
                IsVisibleChanged -= close;
                cont(sender, ev, okClicked);
            };
            Show();
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            ButtonClicked?.Invoke(this, e, false);
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
