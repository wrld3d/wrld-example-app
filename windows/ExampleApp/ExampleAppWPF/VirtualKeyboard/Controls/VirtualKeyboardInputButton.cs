using System.Windows;

namespace ExampleAppWPF.VirtualKeyboard
{
    class VirtualKeyboardInputButton : VirtualKeyboardButton
    {
        public static readonly DependencyProperty KeyInputValueProperty =
            DependencyProperty.RegisterAttached(
                "KeyInputValue",
                typeof(string),
                typeof(VirtualKeyboardButton),
                new PropertyMetadata(default(string)));

        public static readonly DependencyProperty KeyShiftInputValueProperty =
            DependencyProperty.RegisterAttached(
                "KeyShiftInputValue",
                typeof(string),
                typeof(VirtualKeyboardButton),
                new PropertyMetadata(default(string)));

        public static void SetKeyInputValue(UIElement e, string v)
        {
            e.SetValue(KeyInputValueProperty, v);
        }

        public static string GetKeyInputValue(UIElement e)
        {
            return (string)e.GetValue(KeyInputValueProperty);
        }

        public static void SetKeyShiftInputValue(UIElement e, string v)
        {
            e.SetValue(KeyShiftInputValueProperty, v);
        }

        public static string GetKeyShiftInputValue(UIElement e)
        {
            return (string)e.GetValue(KeyShiftInputValueProperty);
        }

        public string GetKeyInputValue()
        {
            return GetKeyInputValue(this);
        }

        public string GetKeyShiftInputValue()
        {
            return GetKeyShiftInputValue(this);
        }

        static VirtualKeyboardInputButton()
        {
            VirtualKeyboardButton.KeyTypeProperty.OverrideMetadata(
                typeof(VirtualKeyboardInputButton),
                new PropertyMetadata(KeyType.Input));
        }
    }
}
