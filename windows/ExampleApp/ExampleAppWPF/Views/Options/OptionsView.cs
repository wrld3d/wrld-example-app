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
        private bool m_clearCacheSelected;
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

        public bool ClearCacheSelected
        {
            get
            {
                return m_clearCacheSelected;
            }
            set
            {
                if (value != m_clearCacheSelected)
                {
                    m_clearCacheSelected = value;
                    OnPropertyChanged("ClearCacheSelected");

                    if (!m_explicitlySettingValue)
                    {
                        OptionsViewCLIMethods.ClearCacheToggled(m_nativeCallerPointer);
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
                    OnPropertyChanged("PlayTutorialsAgainEnabled");

                    if (!m_explicitlySettingValue)
                    {
                        OptionsViewCLIMethods.ReplayTutorials(m_nativeCallerPointer, m_playTutorialsAgainEnabled);
                    }
                }
            }
        }

        protected IntPtr m_nativeCallerPointer;
        
        private string m_adminPassword;
        private bool m_isInKioskMode;

        private Button m_closeButton;
        protected FrameworkElement m_mainContainer;
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

            DataContext = this;

            InitialiseAdminLoginView(adminPassword);
        }

        public override void OnApplyTemplate()
        {
            m_closeButton = (Button)GetTemplateChild("OptionsViewCloseButton");
            m_closeButton.Click += OnCloseButtonClick;

            var okButton = (Button)GetTemplateChild("OptionsViewOkButton");
            okButton.Click += OnOkButtonClick;

            var dataCachingLabel = (TextBlock)GetTemplateChild("OptionsViewCacheEnabledLabel");
            dataCachingLabel.PreviewMouseLeftButtonDown += (s, e) => CacheEnabled = !CacheEnabled;
            
            var clearCacheLabel = (TextBlock)GetTemplateChild("OptionsViewClearCacheLabel");
            clearCacheLabel.PreviewMouseLeftButtonDown += (s, e) => ClearCacheSelected = !ClearCacheSelected;

            var playTutorialLabel = (TextBlock)GetTemplateChild("OptionsViewPlayTutorialLabel");
            playTutorialLabel.PreviewMouseLeftButtonDown += (s, e) => PlayTutorialsAgainEnabled = !PlayTutorialsAgainEnabled;

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

        private void OnOkButtonClick(object sender, RoutedEventArgs e)
        {
            OptionsViewCLIMethods.OkButtonSelected(m_nativeCallerPointer);
        }

        public void OpenClearCacheWarning()
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
            m_explicitlySettingValue = true;
            PlayTutorialsAgainEnabled = replayTutorialsSelected;
            m_explicitlySettingValue = false;
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

        public bool IsClearCacheSelected()
        {
            return ClearCacheSelected;
        }

        public void SetClearCacheSelected(bool clearCacheSelected)
        {
            m_explicitlySettingValue = true;
            ClearCacheSelected = clearCacheSelected;
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
