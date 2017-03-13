using System.Windows;

namespace ExampleAppWPF.VirtualKeyboard
{
    class VirtualKeyboardInputButton : VirtualKeyboardButton
    {
        public static readonly DependencyProperty AutoLabelProperty =
            DependencyProperty.RegisterAttached(
                "AutoLabel",
                typeof(bool),
                typeof(VirtualKeyboardButton),
                new PropertyMetadata(true));

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

        public static void SetAutoLabel(UIElement e, bool v)
        {
            e.SetValue(AutoLabelProperty, v);
        }

        public static bool GetAutoLabel(UIElement e)
        {
            return (bool)e.GetValue(AutoLabelProperty);
        }

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

        public bool GetAutoLabel()
        {
            return GetAutoLabel(this);
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
