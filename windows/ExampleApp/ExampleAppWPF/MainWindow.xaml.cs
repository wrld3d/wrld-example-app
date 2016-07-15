using System;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using ExampleApp.CLI;
using System.Diagnostics;
using System.Windows.Navigation;
using System.Windows.Threading;
using System.Collections.Generic;

namespace ExampleAppWPF
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
        public const float OpacityOnPopup = 0.46f;

		private MapImage m_mapImage;
        private TimeSpan m_currentRenderArgsRenderingTime = TimeSpan.Zero;
        
        private Stopwatch m_frameTimer;
        private bool m_isMouseInputActive;
        private bool m_isTouchInputActive;
        private int m_frameCount = 0;
        private bool m_hasEmptiedEventQueueSinceLastRender = true;
        private bool m_hasHadRenderEventSinceRender = false;
        private double m_maxDelta = 0.0;
        private bool m_logging = false;
        private bool m_firstFrame = true;

        private const float m_maxWaitPercentage = 1.1f;

        private const float m_oversampleScale = 1.0f;

        List<int> m_zeroIndexedTouchIds;
        private bool m_isFullscreen;

        public MainWindow()
        {
            InitializeComponent();

            StartupResourceLoader.Init();


            m_mapImage = new MapImage();
            Loaded += MainWindow_Loaded;
            Closed += MainWindow_Closed;


            m_frameTimer = Stopwatch.StartNew();

            m_isMouseInputActive = true;
            m_isTouchInputActive = true;

            m_zeroIndexedTouchIds = new List<int>();
            m_isMouseInputActive = true;
            m_isFullscreen = false;
        }

        private void MainWindow_Closed(object sender, EventArgs e)
        {
            m_mapImage.Dispose();
        }

        private void OnIsFrontBufferAvailableChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if (m_mapImage.IsFrontBufferAvailable)
            {
                m_mapImage.InitBackBuffer();
            }
        }

        public bool HasTouchInput()
        {
            foreach (TabletDevice tabletDevice in Tablet.TabletDevices)
            {
                //Only detect if it is a touch Screen not how many touches (i.e. Single touch or Multi-touch)
                if (tabletDevice.Type == TabletDeviceType.Touch)
                    return true;
            }
            return false;
        }

        public int GetMaxDeviceTouchCount()
        {
            foreach (TabletDevice tabletDevice in Tablet.TabletDevices)
            {
                return tabletDevice.StylusDevices.Count;
            }
            return 0;
        }

        private void MainWindow_Loaded(object sender, EventArgs loadedEvent)
        {
            MainGrid.SizeChanged += MapHost_SizeChanged;

            int pixelWidth = (int)MainGrid.ActualWidth;
            int pixelHeight = (int)MainGrid.ActualHeight;

            bool hasNativeTouchInput = HasTouchInput();
            int maxDeviceTouchCount = GetMaxDeviceTouchCount();

            m_mapImage.Init(pixelWidth, pixelHeight, m_oversampleScale, hasNativeTouchInput, maxDeviceTouchCount);
            MapHost.Source = m_mapImage;
            MapHost.Width = pixelWidth;
            MapHost.Height = pixelHeight;
            m_mapImage.RespondToResize(pixelWidth, pixelHeight);

            m_mapImage.IsFrontBufferAvailableChanged += OnIsFrontBufferAvailableChanged;
            CompositionTarget.Rendering += CompositionTarget_Rendering;

            if(m_mapImage.ShouldStartFullscreen())
            {
                SetFullScreen(true);
            }

            MouseLeftButtonDown += (o, e) => { if (m_isMouseInputActive) m_mapImage.HandlePanStartEvent((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y), Keyboard.Modifiers); };
            PreviewMouseLeftButtonUp += (o, e) => { if (m_isMouseInputActive) m_mapImage.HandlePanEndEvent((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y), Keyboard.Modifiers); };
            MouseRightButtonDown += (o, e) => { if (m_isMouseInputActive) m_mapImage.HandleRotateStartEvent((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y), Keyboard.Modifiers); };
            PreviewMouseRightButtonUp += (o, e) => { if (m_isMouseInputActive) m_mapImage.HandleRotateEndEvent((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y), Keyboard.Modifiers); };
            MouseWheel += (o, e) => { if (m_isMouseInputActive) m_mapImage.HandleZoomEvent((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y), e.Delta, Keyboard.Modifiers); };
            MouseLeave += (o, e) => { if (m_isMouseInputActive) m_mapImage.SetAllInputEventsToPointerUp((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y)); };
            MouseMove += (o, e) => { if (m_isMouseInputActive) m_mapImage.HandleMouseMoveEvent((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y), Keyboard.Modifiers); };

            KeyDown += OnKeyDown;

            MouseDown += MainWindow_MouseDown;
            MouseUp += MainWindow_MouseUp;

            TouchDown += OnTouchDown;
            TouchUp += OnTouchUp;
            TouchMove += OnTouchMove;

            Dispatcher.Hooks.DispatcherInactive += new EventHandler(DispatcherInactive);

        }

        private void SetFullScreen(bool isFullScreen)
        {
            m_mapImage.SetFullscreen(isFullScreen);
            m_isFullscreen = isFullScreen;
        }

        private int CheckAndGetZeroIndexedId(int systemId)
        {
            int result =  m_zeroIndexedTouchIds.IndexOf(systemId);

            if(result != -1)
            {
                return result;
            }

            m_zeroIndexedTouchIds.Add(systemId);

            return m_zeroIndexedTouchIds.Count - 1;
        }

        private void OnTouchMove(object sender, TouchEventArgs e)
        {
            if (m_isTouchInputActive)
            {
                m_mapImage.HandleTouchMoveEvent((float)e.TouchDevice.GetTouchPoint(this).Position.X, (float)e.TouchDevice.GetTouchPoint(this).Position.Y, 0.0f, CheckAndGetZeroIndexedId(e.TouchDevice.Id));
            }
        }

        private void OnTouchUp(object sender, TouchEventArgs e)
        {
            if (m_isTouchInputActive)
            {
                m_mapImage.HandleTouchUpEvent((float)e.TouchDevice.GetTouchPoint(this).Position.X, (float)e.TouchDevice.GetTouchPoint(this).Position.Y, 0.0f, CheckAndGetZeroIndexedId(e.TouchDevice.Id));
            }
        }

        private void OnTouchDown(object sender, TouchEventArgs e)
        {


            if (m_isTouchInputActive)
            {
                m_mapImage.HandleTouchDownEvent((float)e.TouchDevice.GetTouchPoint(this).Position.X, (float)e.TouchDevice.GetTouchPoint(this).Position.Y, 0.0f, CheckAndGetZeroIndexedId(e.TouchDevice.Id));
            }
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            m_mapImage.HandleKeyboardDownEvent((int)KeyInterop.VirtualKeyFromKey(e.Key));

            if (Keyboard.IsKeyDown(Key.LeftCtrl) && Keyboard.IsKeyDown(Key.LeftShift) && Keyboard.IsKeyDown(Key.F))
            {
                SetFullScreen(!m_isFullscreen);
            }
        }

        private void DispatcherInactive(object sender, EventArgs e)
        {
            m_hasEmptiedEventQueueSinceLastRender = true;

            TryDoUpdateAndRender();
        }

        public void EnableInput()
        {
            SetInputActive(true);
        }

        public void DisableInput()
        {
            SetInputActive(false);
        }

        public void SetInputActive(bool input)
        {
            m_isMouseInputActive = input;
            m_isTouchInputActive = input;
        }

        public void SetOpacity(double opacity)
        {
            Opacity = opacity;
        }

        private void MainWindow_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Middle && m_isMouseInputActive)
            {
                m_mapImage.HandleTiltEnd((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y), Keyboard.Modifiers);
            }
        }

        private void MainWindow_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Middle && m_isMouseInputActive)
            {
                m_mapImage.HandleTiltStart((int)(e.GetPosition(null).X), (int)(e.GetPosition(null).Y), Keyboard.Modifiers);
            }
        }

        private void MapHost_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            int pixelWidth = (int)e.NewSize.Width;
            int pixelHeight = (int)e.NewSize.Height;

            if (pixelWidth != m_mapImage.PixelWidth || pixelHeight != m_mapImage.PixelHeight)
            {
                MapHost.Width = pixelWidth;
                MapHost.Height = pixelHeight;

                if (pixelWidth > 0 && pixelHeight > 0)
                {
                    m_mapImage.RespondToResize(pixelWidth, pixelHeight);
                }
            }
        }

        private void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            RenderingEventArgs renderArgs = (RenderingEventArgs)e;
            if (!m_hasHadRenderEventSinceRender)
            {                
                m_maxDelta = m_frameTimer.Elapsed.TotalSeconds * m_maxWaitPercentage;
                m_hasHadRenderEventSinceRender = true;
            }

            if (m_currentRenderArgsRenderingTime == renderArgs.RenderingTime)
            {
                return;
            }
            m_currentRenderArgsRenderingTime = renderArgs.RenderingTime;

            TryDoUpdateAndRender();
        }

        private void TryDoUpdateAndRender()
        {
            if (m_firstFrame)
            {
                m_firstFrame = false;
                return;
            }

            if (MapHost.Source == null)
                return;

            if (!m_mapImage.IsFrontBufferAvailable)
                return;

            var dt = m_frameTimer.Elapsed.TotalSeconds;

            if (!m_hasEmptiedEventQueueSinceLastRender && (dt < m_maxDelta))
            {
                if (m_logging)
                {
                    Debug.WriteLine(string.Format("[{0}] BAIL dt {1}, frameTimer {2}", m_frameCount, dt, m_frameTimer.Elapsed));
                }
                return;
            }

            if (m_logging)
            {
                Debug.WriteLine(string.Format("[{0}] BAIL dt {1}, frameTimer {2}", m_frameCount, dt, m_frameTimer.Elapsed));
            }

            m_hasEmptiedEventQueueSinceLastRender = false;
            m_hasHadRenderEventSinceRender = false;
            ++m_frameCount;
            m_frameTimer.Restart();

            m_mapImage.Render((float)dt);
        }

        private void Hyperlink_RequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
            e.Handled = true;
        }
    }
}
