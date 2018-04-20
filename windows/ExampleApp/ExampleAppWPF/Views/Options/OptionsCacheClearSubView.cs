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
        private Button m_cancelButton;
        private Button m_closeButton;
        private Image m_spinner;
        private string m_contentBig;
        private string m_contentSmall;
        private long m_cacheClearDialogMinimumEndTimeMilliseconds;
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public string ContentBig { get { return m_contentBig; } set { m_contentBig = value; OnPropertyChanged("ContentBig"); } }

        public string ContentSmall { get { return m_contentSmall; } set { m_contentSmall = value; OnPropertyChanged("ContentSmall"); } }

        private static string StringResource(string name)
        {
            return (string)Application.Current.Resources[name];
        }

        static OptionsCacheClearSubView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(OptionsCacheClearSubView), new FrameworkPropertyMetadata(typeof(OptionsCacheClearSubView)));
        }

        public OptionsCacheClearSubView()
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);

            DataContext = this;

            ResetState();
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_confirmButton = (Button)GetTemplateChild("CacheClearCeremonyConfirmButton");
            m_cancelButton = (Button)GetTemplateChild("CacheClearCeremonyCancelButton");
            m_closeButton = (Button)GetTemplateChild("CacheClearCeremonyCloseButton");
            m_spinner = (Image)GetTemplateChild("CacheClearCeremonyViewSpinner");
            
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;

            RoutedEventHandler closeHandler = (s, e) =>
            {
                ResetState();
                mainWindow.MainGrid.Children.Remove(this);
            };

            m_closeButton.Click += closeHandler;
            m_cancelButton.Click += closeHandler;
            m_confirmButton.Click += (s, e) => HandleConfirmClicked();
        }


        public void DisplayWarning(Action confirmationCallback)
        {
            Debug.Assert(confirmationCallback != null);
            Debug.Assert(m_confirmationCallback == null);
            Debug.Assert(!m_isDisplayed);

            m_isDisplayed = true;
            m_confirmationCallback = confirmationCallback;

            Visibility = Visibility.Visible;

            ContentBig   = StringResource("ClearCacheSubViewConfirmMessageBig");
            ContentSmall = StringResource("ClearCacheSubViewConfirmMessageSmall");
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
            ContentBig   = "";
            ContentSmall = StringResource("ClearCacheSubViewDoneMessageSmall");

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
            m_cancelButton.Visibility = Visibility.Collapsed;
            m_closeButton.Visibility = Visibility.Collapsed;
            m_spinner.Visibility = Visibility.Visible;

            ContentBig   = "";
            ContentSmall = StringResource("ClearCacheSubViewWorkingMessageSmall");

            m_cacheClearDialogMinimumEndTimeMilliseconds = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond + 3000;

            m_confirmationCallback();
        }
    }
}
