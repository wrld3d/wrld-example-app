using System;
using System.Windows;
using System.Windows.Input;

namespace ExampleAppWPF
{
    public class ControlClickHandler
    {
        private Action<object, MouseButtonEventArgs> m_onClickAction;

        private bool m_mouseDown = false;

        public ControlClickHandler(FrameworkElement control, Action<object, MouseButtonEventArgs> onClickAction)
        {
            m_onClickAction = onClickAction;

            control.MouseLeftButtonDown += OnLeftButtonDown;
            control.MouseLeave += OnMouseLeave;
            control.MouseLeftButtonUp += OnLeftButtonUp;
        }

        public ControlClickHandler(Action<object, MouseButtonEventArgs> onClickAction, FrameworkElement control)
        {
            m_onClickAction = onClickAction;

            control.PreviewMouseLeftButtonDown += OnLeftButtonDown;
            control.MouseLeave += OnMouseLeave;
            control.PreviewMouseLeftButtonUp += OnLeftButtonUp;
        }

        private void OnLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            m_mouseDown = true;
        }

        private void OnMouseLeave(object sender, MouseEventArgs e)
        {
            m_mouseDown = false;
        }

        private void OnLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if(m_mouseDown)
            {
                m_mouseDown = false;

                m_onClickAction(sender, e);
            }
        }
    }
}
