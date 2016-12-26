using System.Windows;

namespace ExampleAppWPF.VirtualKeyboard
{
    class VirtualKeyboardSpecialButton : VirtualKeyboardButton
    {
        public static readonly DependencyProperty KeySpecialInputValueProperty =
            DependencyProperty.RegisterAttached(
                "KeySpecialInputValue",
                typeof(string),
                typeof(VirtualKeyboardButton),
                new PropertyMetadata(default(string)));

        static VirtualKeyboardSpecialButton()
        {
            VirtualKeyboardButton.KeyTypeProperty.OverrideMetadata(
                typeof(VirtualKeyboardSpecialButton),
                new PropertyMetadata(KeyType.Special));
        }

        public static void SetKeySpecialInputValue(UIElement e, string v)
        {
            e.SetValue(KeySpecialInputValueProperty, v);
        }

        public static string GetKeySpecialInputValue(UIElement e)
        {
            return (string)e.GetValue(KeySpecialInputValueProperty);
        }

        public string GetKeySpecialInputValue()
        {
            return GetKeySpecialInputValue(this);
        }
    }
}
