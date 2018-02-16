using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class OptionsMessage : Control, INotifyPropertyChanged
    {
        protected IntPtr m_nativeCallerPointer;

        private Action m_onClose;

        public event PropertyChangedEventHandler PropertyChanged;

        static OptionsMessage()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(OptionsMessage), new FrameworkPropertyMetadata(typeof(OptionsMessage)));
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public string Title     { get; set; }
        public string Message   { get; set; }

        public OptionsMessage(IntPtr nativeCallerPointer, string title, string message)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);

            DataContext = this;

            m_nativeCallerPointer = nativeCallerPointer;

            Title = title;
            Message = message;

            Visibility = Visibility.Collapsed;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            Button closeButton = (Button)GetTemplateChild("CloseButton");
            closeButton.Click += CloseButton_Click;
        }

        public void ShowMessage(Action onClose)
        {
            m_onClose = onClose;

            Visibility = Visibility.Visible;
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            m_onClose();

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Remove(this);
        }
    }
}