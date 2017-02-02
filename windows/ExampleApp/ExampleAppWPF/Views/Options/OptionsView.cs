using ExampleApp;
using System;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
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
        private bool m_playTutorialsAgainEnabled;

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

        public bool PlayTutorialsAgainEnabled
        {
            get
            {
                return m_playTutorialsAgainEnabled;
            }
            set
            {
                if(value != m_playTutorialsAgainEnabled)
                {
                    m_playTutorialsAgainEnabled = value;
                    ReplayTutorials(m_playTutorialsAgainEnabled);
                    OnPropertyChanged("PlayTutorialsAgainEnabled");
                }
            }
        }

        protected IntPtr m_nativeCallerPointer;
        
        private string m_adminPassword;
        private bool m_isInKioskMode;

        private Button m_closeButton;
        private ToggleButton m_streamOverWifiButton;
        private ToggleButton m_dataCachingButton;
        private Button m_clearCacheButton = null;
        protected FrameworkElement m_mainContainer;
        private Button m_adminLoginButton;
        private AdminLoginView m_adminLoginView;

        public event PropertyChangedEventHandler PropertyChanged;

        private OptionsCacheClearSubView m_cacheClearSubView;

        public OptionsView(IntPtr nativeCallerPointer, string adminPassword, bool isInKioskMode)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            m_adminPassword = adminPassword;
            m_isInKioskMode = isInKioskMode;
            Visibility = Visibility.Hidden;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            InitialiseAdminLoginView(adminPassword);
        }

        public override void OnApplyTemplate()
        {
            m_closeButton = (Button)GetTemplateChild(m_isInKioskMode ? "OptionsViewCloseButtonKiosk" : "OptionsViewCloseButton");
            m_closeButton.Click += OnCloseButtonClick;

            m_dataCachingButton = (ToggleButton)GetTemplateChild("OptionsViewCacheEnabledTogglebutton");
            var dataCachingLabel = (TextBlock)GetTemplateChild("OptionsViewCacheEnabledLabel");
            dataCachingLabel.PreviewMouseLeftButtonDown += (s, e) => CacheEnabled = !CacheEnabled;
            
            m_clearCacheButton = (Button)GetTemplateChild("OptionsViewClearCacheButton");
            var clearCacheLabel = (TextBlock)GetTemplateChild("OptionsViewClearCacheLabel");
            clearCacheLabel.PreviewMouseLeftButtonDown += (s, e) => OnClearCacheButtonClick(s, e);
            m_clearCacheButton.Click += OnClearCacheButtonClick;
            
            m_adminLoginButton = (Button)GetTemplateChild("OptionsViewAdminButton");
            m_adminLoginButton.Click += OnAdminLoginButtonClick;

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

        private void OnClearCacheButtonClick(object sender, RoutedEventArgs e)
        {
            BeginCacheClearCeremony();
        }

        private void OnDataCachingButtonChecked(object sender, RoutedEventArgs e)
        {
            OptionsViewCLIMethods.CachingEnabledToggled(m_nativeCallerPointer);
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

        public void SetReplayTutorialsSelected(bool replayTutorialsSelected)
        {
            PlayTutorialsAgainEnabled = replayTutorialsSelected;
        }

        public void ConcludeCacheClearCeremony()
        {
            m_cacheClearSubView.ConcludeCeremony();
            m_cacheClearSubView = null;
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
            m_cacheClearSubView.DisplayWarning(() => OptionsViewCLIMethods.ClearCacheSelected(m_nativeCallerPointer));
        }

        private void InitialiseAdminLoginView(string adminPassword)
        {
            m_adminLoginView = new AdminLoginView(adminPassword);
            m_adminLoginView.Visibility = Visibility.Collapsed;
            m_adminLoginView.OnHide += OnAdminLoginHide;
            m_currentWindow.MainGrid.Children.Add(m_adminLoginView);
        }

        private void ReplayTutorials(bool replayTutorials)
        {
            OptionsViewCLIMethods.ReplayTutorials(m_nativeCallerPointer, replayTutorials);
        }
    }
}
