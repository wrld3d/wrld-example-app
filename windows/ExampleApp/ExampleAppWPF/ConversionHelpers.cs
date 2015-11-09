using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExampleAppWPF
{
    class ConversionHelpers
    {
        public static double AndroidToWindowsDip(double input)
        {
            // this is backwards, but actually works out as our android builds don't work at lowest DPI
            return input * (240.0 / 160.0);//(160.0 / 96.0);
        }
    }
}
