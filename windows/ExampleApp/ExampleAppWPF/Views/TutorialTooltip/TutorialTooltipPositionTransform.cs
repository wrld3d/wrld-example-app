using System;
using System.Windows;

namespace ExampleAppWPF
{
    class TutorialTooltipPositionTracker
    {
        public delegate void OnUpdateTransformEvent(double x, double y, double width, double height);
        public OnUpdateTransformEvent OnUpdateTransform;

        private static Point Origin = new Point(0.0, 0.0);

        private Window m_rootWindow;
        private FrameworkElement m_element;
        private Point m_lastPosition;

        public TutorialTooltipPositionTracker(Window rootWindow, FrameworkElement element)
        {
            m_rootWindow = rootWindow;
            m_element = element;

            m_element.IsVisibleChanged += OnControlVisibileChanged;
            EnableChangeHooks(true);
            UpdateTransform();
        }

        public void EnableChangeHooks(bool enableHooks)
        {
            if (enableHooks)
            {
                m_rootWindow.SizeChanged += OnControlLayoutUpdated;
                m_element.SizeChanged += OnControlSizeChanged;
                m_element.LayoutUpdated += OnControlLayoutUpdated;
            }
            else
            {
                m_rootWindow.SizeChanged -= OnControlLayoutUpdated;
                m_element.SizeChanged -= OnControlSizeChanged;
                m_element.LayoutUpdated -= OnControlLayoutUpdated;
            }
        }

        public void UpdateTransform()
        {
            Point absolutePosition = m_element.TransformToAncestor(m_rootWindow).Transform(Origin);
            if (m_lastPosition != absolutePosition)
            {
                m_lastPosition = absolutePosition;
                OnUpdateTransform?.Invoke(absolutePosition.X, absolutePosition.Y, m_element.ActualWidth, m_element.ActualHeight);
            }
        }

        private void OnControlVisibileChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            EnableChangeHooks(m_element.IsVisible);
        }

        private void OnControlLayoutUpdated(object sender, EventArgs e)
        {
            UpdateTransform();
        }

        private void OnControlSizeChanged(object sender, SizeChangedEventArgs e)
        {
            UpdateTransform();
        }
    }
}