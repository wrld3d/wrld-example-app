using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF.VirtualKeyboard
{
    class VirtualKeyboardButton : Button
    {
        public enum KeyType
        {
            Input,
            Control,
            Special
        };

        public static readonly DependencyProperty KeyTypeProperty =
            DependencyProperty.RegisterAttached(
                "KeyType",
                typeof(KeyType),
                typeof(VirtualKeyboardButton),
                new PropertyMetadata(KeyType.Input));

        public static void SetKeyType(UIElement e, KeyType t)
        {
            e.SetValue(KeyTypeProperty, t);
        }

        public static KeyType GetKeyType(UIElement e)
        {
            return (KeyType)e.GetValue(KeyTypeProperty);
        }

        public KeyType GetKeyType()
        {
            return GetKeyType(this);
        }
    }
}
