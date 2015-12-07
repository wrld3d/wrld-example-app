using System.Windows.Controls;
using System.Windows.Input;

namespace ExampleAppWPF
{
    public class ButtonBase : Button
    {
        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonUp(e);

            e.Handled = false;
        }
    }
}
