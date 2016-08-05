using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ExampleAppWPF
{
    class WindowInteractionTouchHandler
    {
        public WindowInteractionTouchHandler(FrameworkElement ui)
        {
            var window = Application.Current.MainWindow as MainWindow;

            ui.TouchEnter += (o, e) => { window.DisableInput(); window.PopAllTouchEvents(); };
            ui.TouchLeave += (o, e) => { window.EnableInput(); };
        }
    }
}
