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
        private List<List<string>> customKeyboardLayout;

        public VirtualKeyboardView(IntPtr nativeCallerPointer)
        {
            customKeyboardLayout = new List<List<string>>();

            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.ContentRendered += (o, e) =>
            {
                OnLoadedAddVirtualKeyboardFocusHandlers();
                m_currentWindow.MainGrid.Children.Add(this);
                Panel.SetZIndex(this, 1000);
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

        public void AddCustomKeyboardKey(string row, string index, string uppercase, string lowercase)
        {
            customKeyboardLayout.Add(new List<string>() { row, index, uppercase, lowercase });
        }

        public void ClearCustomKeyboardKeys()
        {
            customKeyboardLayout.Clear();
        }

        public void ProcessCustomKeyboardKeys()
        {
            foreach (var customKeyLayout in this.customKeyboardLayout)
            {
                string row = customKeyLayout[0];
                int index = int.Parse(customKeyLayout[1]);
                string lowercase = customKeyLayout[2];
                string uppercase = customKeyLayout[3];

                StackPanel keyboardRow = ViewHelpers.FindChildByName<StackPanel>(this, row);

                VirtualKeyboard.VirtualKeyboardInputButton keyToChange = keyboardRow.Children[index] as VirtualKeyboard.VirtualKeyboardInputButton;

                VirtualKeyboard.VirtualKeyboardInputButton.SetKeyInputValue(keyToChange, lowercase);

                if (lowercase != "")
                {
                    VirtualKeyboard.VirtualKeyboardInputButton.SetKeyShiftInputValue(keyToChange, uppercase);
                }
                else if (VirtualKeyboard.VirtualKeyboardInputButton.GetKeyShiftInputValue(keyToChange) != null)
                {
                    uppercase = lowercase;
                    VirtualKeyboard.VirtualKeyboardInputButton.SetKeyShiftInputValue(keyToChange, uppercase);
                }

                if (keyToChange.GetAutoLabel())
                {
                    keyToChange.Content = keyToChange.GetKeyInputValue();
                }
                else
                {
                    StackPanel customKeyLabel = ViewHelpers.FindChildByName<StackPanel>(this, "Label" + customKeyLayout[1]);

                    TextBlock upperCaseLabel = customKeyLabel.Children[0] as TextBlock;
                    upperCaseLabel.Text = uppercase;

                    TextBlock lowerCaseLabel = customKeyLabel.Children[1] as TextBlock;
                    lowerCaseLabel.Text = lowercase;
                }
            }
        }

        public void ShowVirtualKeyboard()
        {
            SetVisibility(true);
            ProcessCustomKeyboardKeys();
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
