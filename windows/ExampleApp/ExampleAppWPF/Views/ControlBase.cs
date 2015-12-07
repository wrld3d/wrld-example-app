using System.Windows.Controls;
using System.Windows.Input;

namespace ExampleAppWPF
{
    public class ControlBase : Control
    {
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            e.Handled = true;
        }

        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonUp(e);

            e.Handled = false;
        }
    }
}
