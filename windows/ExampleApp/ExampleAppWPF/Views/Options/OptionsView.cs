using ExampleApp;
using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace ExampleAppWPF
{
    public class OptionsView : Control, INotifyPropertyChanged
    {
        private MainWindow m_currentWindow;

        static OptionsView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(OptionsView), new FrameworkPropertyMetadata(typeof(OptionsView)));
        }

        private bool m_cacheEnabled;
        private bool m_explicitlySettingValue;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
        
        public bool CacheEnabled
        {
            get
            {
                return m_cacheEnabled;
            }

            set
            {
                if (value != m_cacheEnabled)
                {
                    m_cacheEnabled = value;
                    OnPropertyChanged("CacheEnabled");

                    if (!m_explicitlySettingValue)
                    {
                        OptionsViewCLIMethods.CachingEnabledToggled(m_nativeCallerPointer);
                    }
                }
            }
        }

        private static string StringResource(string name)
        {
            return (string)Application.Current.Resources[name];
        }

        protected IntPtr m_nativeCallerPointer;
        
        private string m_adminPassword;
        private bool m_isInKioskMode;

        private Button m_closeButton;
        protected FrameworkElement m_mainContainer;
        private AdminLoginView m_adminLoginView;

        public event PropertyChangedEventHandler PropertyChanged;

        private OptionsCacheClearSubView m_cacheClearSubView;
        private OptionsMessage m_messageSubView;

        public OptionsView(IntPtr nativeCallerPointer, string adminPassword, bool isInKioskMode)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            m_adminPassword = adminPassword;
            m_isInKioskMode = isInKioskMode;
            Visibility = Visibility.Hidden;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            DataContext = this;

            InitialiseAdminLoginView(adminPassword);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_closeButton = (Button)GetTemplateChild("OptionsViewCloseButton");
            m_closeButton.Click += OnCloseButtonClick;

            var dataCachingLabel = (TextBlock)GetTemplateChild("OptionsViewCacheEnabledLabel");
            dataCachingLabel.PreviewMouseLeftButtonDown += (s, e) => CacheEnabled = !CacheEnabled;

            var clearCacheButton = (Button)   GetTemplateChild("OptionsViewClearCacheButton");
            var clearCacheLabel  = (TextBlock)GetTemplateChild("OptionsViewClearCacheLabel");
            clearCacheButton.Click    += OnClearCacheButtonClick;
            clearCacheLabel.MouseDown += OnClearCacheButtonClick;

            var playTutorialsButton = (Button)   GetTemplateChild("OptionsViewPlayTutorialsButton");
            var playTutorialsLabel  = (TextBlock)GetTemplateChild("OptionsViewPlayTutorialsLabel");
            playTutorialsButton.Click    += OnPlayTutorialsButtonClick;
            playTutorialsLabel.MouseDown += OnPlayTutorialsButtonClick;

            var adminLoginButton = (Button)GetTemplateChild("OptionsViewAdminButton");
            adminLoginButton.Click += OnAdminLoginButtonClick;

            var adminLoginLabel = (TextBlock)GetTemplateChild("OptionsViewAdminLabel");
            adminLoginLabel.MouseDown += OnAdminLoginButtonClick;

            m_mainContainer = (FrameworkElement)GetTemplateChild("MainContainer");

            m_mainContainer.MouseDown += OnContainerMouseDown;
        }

        private void OnContainerMouseDown(object sender, MouseButtonEventArgs e)
        {
            e.Handled = true;
        }

        private void OnCloseButtonClick(object sender, RoutedEventArgs e)
        {
            OptionsViewCLIMethods.CloseButtonSelected(m_nativeCallerPointer);
        }

        public void OpenClearCacheWarning()
        {
            BeginCacheClearCeremony();
        }

        private void OnDataCachingButtonChecked(object sender, RoutedEventArgs e)
        {
            OptionsViewCLIMethods.CachingEnabledToggled(m_nativeCallerPointer);
        }

        private void OnClearCacheButtonClick(object sender, RoutedEventArgs e)
        {
            OptionsViewCLIMethods.ClearCacheSelected(m_nativeCallerPointer);
        }

        private void OnPlayTutorialsButtonClick(object sender, RoutedEventArgs e)
        {
            OptionsViewCLIMethods.ReplayTutorialsSelected(m_nativeCallerPointer);

            m_messageSubView = new OptionsMessage(m_nativeCallerPointer,
                                                  StringResource("OptionsViewReplayTitle"),
                                                  StringResource("OptionsViewReplayMessage"));

            m_messageSubView.ShowMessage(() => {
                m_messageSubView = null;

                OptionsViewCLIMethods.CloseButtonSelected(m_nativeCallerPointer);
            });
        }

        private void OnAdminLoginButtonClick(object sender, RoutedEventArgs e)
        {
            Visibility = Visibility.Collapsed;
            m_adminLoginView.Show();
        }

        private void OnAdminLoginHide()
        {
            Visibility = Visibility.Visible;
        }

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(m_adminLoginView);
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void OpenOptions()
        {
            m_closeButton.IsEnabled = true;
            Visibility = Visibility.Visible;
            Focus();

            m_currentWindow.DisableInput();
        }

        public void CloseOptions()
        {
            m_adminLoginView.Dismiss();
            Visibility = Visibility.Hidden;
            m_currentWindow.EnableInput();
        }

        public void ConcludeCacheClearCeremony()
        {
            m_cacheClearSubView.ConcludeCeremony();
            m_cacheClearSubView = null;

            OptionsViewCLIMethods.CloseButtonSelected(m_nativeCallerPointer);
        }

        public bool IsCacheEnabledSelected()
        {
            return CacheEnabled;
        }
        
        public void SetCacheEnabledSelected(bool cacheEnabledSelected)
        {
            m_explicitlySettingValue = true;
            CacheEnabled = cacheEnabledSelected;
            m_explicitlySettingValue = false;
        }

        private void BeginCacheClearCeremony()
        {
            m_cacheClearSubView = new OptionsCacheClearSubView();
            m_cacheClearSubView.DisplayWarning(() => OptionsViewCLIMethods.ClearCacheTriggered(m_nativeCallerPointer));
        }

        private void InitialiseAdminLoginView(string adminPassword)
        {
            m_adminLoginView = new AdminLoginView(adminPassword);
            m_adminLoginView.Visibility = Visibility.Collapsed;
            m_adminLoginView.OnHide += OnAdminLoginHide;
            m_currentWindow.MainGrid.Children.Add(m_adminLoginView);
        }
    }
}
