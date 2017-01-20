using ExampleApp;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace ExampleAppWPF
{
    class VirtualKeyboardView : VirtualKeyboard.QuertyKeyboard
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;

        public VirtualKeyboardView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.ContentRendered += (o, e) =>
            {
                OnLoadedAddVirtualKeyboardFocusHandlers();
                m_currentWindow.MainGrid.Children.Add(this);
            };

            Visibility = Visibility.Hidden;
            ControlKeyUp += (key) =>
            {
                if (key == 0xd)
                {
                    HideVirtualKeyboard();
                }
            };
            CustomKeyUp += (key) =>
            {
                if (key == "HideKeyboard")
                {
                    HideVirtualKeyboard();
                }
                else
                {
                    KeyboardLayout = key;
                }
            };
        }

        public void ShowVirtualKeyboard()
        {
            SetVisibility(true);
        }

        public void HideVirtualKeyboard()
        {
            SetVisibility(false);
        }
        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        protected override void OnTouchDown(TouchEventArgs e)
        {
            // Consume touch events to disable double-tap zooming through the keyboard.
            e.Handled = true;
        }

        protected override void OnTouchMove(TouchEventArgs e)
        {
            // Consume touch events to disable panning through the keyboard.
            e.Handled = true;
        }

        private void OnLoadedAddVirtualKeyboardFocusHandlers()
        {
            foreach (var child in ViewHelpers.FindChildrenOfType<TextBox>(m_currentWindow.MainGrid.Children))
            {
                child.PreviewMouseDown += (o, e) => ShowVirtualKeyboard();
                child.GotFocus += (o, e) => ShowVirtualKeyboard();
                child.LostFocus += (o, e) => HideVirtualKeyboard();
                InputMethod.SetIsInputMethodEnabled(child, false);
            }
        }

        private void SetVisibility(bool isVisible)
        {
            if (isVisible != IsVisible)
            {
                Visibility = isVisible ? Visibility.Visible : Visibility.Hidden;
                VirtualKeyboardCLIMethods.OnVisibilityChanged(m_nativeCallerPointer, isVisible);
            }
        }
    }
}
