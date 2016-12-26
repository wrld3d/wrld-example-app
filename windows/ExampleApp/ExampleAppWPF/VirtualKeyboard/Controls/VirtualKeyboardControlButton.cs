using System.Windows;

namespace ExampleAppWPF.VirtualKeyboard
{
    class VirtualKeyboardControlButton : VirtualKeyboardButton
    {
        public static readonly DependencyProperty KeyControlInputValueProperty =
            DependencyProperty.RegisterAttached(
                "KeyControlInputValue",
                typeof(int),
                typeof(VirtualKeyboardControlButton));

        static VirtualKeyboardControlButton()
        {
            VirtualKeyboardButton.KeyTypeProperty.OverrideMetadata(
                typeof(VirtualKeyboardControlButton),
                new PropertyMetadata(KeyType.Control));
        }

        public static void SetKeyControlInputValue(UIElement e, int v)
        {
            e.SetValue(KeyControlInputValueProperty, v);
        }

        public static int GetKeyControlInputValue(UIElement e)
        {
            return (int)e.GetValue(KeyControlInputValueProperty);
        }

        public int GetKeyControlInputValue()
        {
            return GetKeyControlInputValue(this);
        }
    }
}
