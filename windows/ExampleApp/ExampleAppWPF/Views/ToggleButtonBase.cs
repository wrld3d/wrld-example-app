using System.Windows.Controls.Primitives;
using System.Windows.Input;

namespace ExampleAppWPF
{
    public class ToggleButtonBase : ToggleButton
    {
        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonUp(e);

            e.Handled = false;
        }
    }
}
