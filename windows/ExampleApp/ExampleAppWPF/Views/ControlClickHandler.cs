using System;
using System.Windows;
using System.Windows.Input;

namespace ExampleAppWPF
{
    class ControlClickHandler
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
