using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Threading;

namespace ExampleAppWPF
{   public class OptionsCacheClearSubView : Control, INotifyPropertyChanged
    {
        private Action m_confirmationCallback = null;
        private bool m_isDisplayed = false;
        private Button m_confirmButton;
        private Button m_closeButton;
        private ProgressBar m_spinner;
        private string m_title;
        private string m_content;
        private long m_cacheClearDialogMinimumEndTimeMilliseconds;
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public string Title { get { return m_title; } set { m_title = value; OnPropertyChanged("Title"); } }

        public string Content { get { return m_content; } set { m_content = value; OnPropertyChanged("Content"); } }

        static OptionsCacheClearSubView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(OptionsCacheClearSubView), new FrameworkPropertyMetadata(typeof(OptionsCacheClearSubView)));
        }

        public OptionsCacheClearSubView()
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);

            ResetState();
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_confirmButton = (Button)GetTemplateChild("CacheClearCeremonyConfirmButton");
            m_closeButton = (Button)GetTemplateChild("CacheClearCeremonyCloseButton");
            m_spinner = (ProgressBar)GetTemplateChild("CacheClearCeremonyViewSpinner");
            
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            m_confirmButton.Click += (s, e) => HandleConfirmClicked();
            m_closeButton.Click += (s, e) =>
            {
                ResetState();
                mainWindow.MainGrid.Children.Remove(this);
            };
        }


        public void DisplayWarning(Action confirmationCallback)
        {
            Debug.Assert(confirmationCallback != null);
            Debug.Assert(m_confirmationCallback == null);
            Debug.Assert(!m_isDisplayed);

            m_isDisplayed = true;
            m_confirmationCallback = confirmationCallback;

            Visibility = Visibility.Visible;

            Title = "Warning";
            Content = "Are you sure you want to remove all stored data?";
        }

        public void ConcludeCeremony()
        {
            Debug.Assert(m_isDisplayed);

            long nowMilliseconds = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
            long remainingIntervalUntilEndTimeMilliseconds = m_cacheClearDialogMinimumEndTimeMilliseconds - nowMilliseconds;

            if (remainingIntervalUntilEndTimeMilliseconds <= 0)
            {
                CloseAsyncCacheClearDialog();
            }
            else
            {
                var timer = new DispatcherTimer();
                timer.Interval = TimeSpan.FromMilliseconds(remainingIntervalUntilEndTimeMilliseconds);
                timer.Tick += (s,e) => { CloseAsyncCacheClearDialog(); timer.Stop(); };
                timer.Start();
            }
        }
    
        private void CloseAsyncCacheClearDialog()
        {
            Content = "Map data deleted from device";
            m_closeButton.Visibility = Visibility.Visible;
            m_spinner.Visibility = Visibility.Hidden;
        }

        private void ResetState()
        {
            m_isDisplayed = false;
            m_confirmationCallback = null;
            Visibility = Visibility.Collapsed;
        }

        private void HandleConfirmClicked()
        {
            Debug.Assert(m_isDisplayed);

            m_confirmButton.Visibility = Visibility.Collapsed;
            m_closeButton.Visibility = Visibility.Collapsed;
            m_spinner.Visibility = Visibility.Visible;
            Title = "Remove Stored Data";
            Content = "Please wait, this may take a while...";
            m_cacheClearDialogMinimumEndTimeMilliseconds = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond + 3000;

            m_confirmationCallback();
        }
    }
}
