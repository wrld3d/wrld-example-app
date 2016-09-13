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
        public WindowInteractionTouchHandler(FrameworkElement ui, bool enableTouchEnter, bool enableTouchDown, bool enableTouchLeave)
        {
            var window = Application.Current.MainWindow as MainWindow;

            if (enableTouchEnter)
            {
                ui.TouchEnter += (o, e) =>
                {
                    window.PopAllTouchEvents();
                    window.DisableInput();
                };
            }

            if(enableTouchDown)
            {
                ui.TouchDown += (o, e) =>
                {
                    window.PopAllTouchEvents();
                    window.DisableInput();
                };
            }

            if(enableTouchLeave)
            {
                ui.TouchLeave += (o, e) => { window.EnableInput(); };
            }
        }
    }
}
