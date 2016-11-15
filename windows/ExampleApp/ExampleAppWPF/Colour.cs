using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public static class Colour
    {
        public static SolidColorBrush gold = (SolidColorBrush)(new BrushConverter().ConvertFrom("#1E7BC3"));
        public static SolidColorBrush olive = (SolidColorBrush)(new BrushConverter().ConvertFrom("#94A847"));
        public static SolidColorBrush white = (SolidColorBrush)(new BrushConverter().ConvertFrom("#FFFFFF"));
        public static SolidColorBrush black = (SolidColorBrush)(new BrushConverter().ConvertFrom("#000000"));
        public static SolidColorBrush darkgrey = (SolidColorBrush)(new BrushConverter().ConvertFrom("#606060"));
        public static SolidColorBrush grey = (SolidColorBrush)(new BrushConverter().ConvertFrom("#AAAAAA"));
        public static SolidColorBrush lightgrey = (SolidColorBrush)(new BrushConverter().ConvertFrom("#CCCCCC"));
        public static SolidColorBrush blue = (SolidColorBrush)(new BrushConverter().ConvertFrom("#291E9A"));
        public static SolidColorBrush menu_separator = (SolidColorBrush)(new BrushConverter().ConvertFrom("#B1CCE1"));
        public static SolidColorBrush submenu_separator = (SolidColorBrush)(new BrushConverter().ConvertFrom("#C6CECF"));
        public static SolidColorBrush transparent = (SolidColorBrush)(new BrushConverter().ConvertFrom("#00000000"));
    }
}
