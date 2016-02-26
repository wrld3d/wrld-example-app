using System;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Windows;
using System.Windows.Controls.Primitives;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public class TickBarVerticalWithLabels : TickBar
    {

        public static readonly DependencyProperty TickLabelsProperty = DependencyProperty.Register("TickLabels", typeof(string), typeof(TickBarVerticalWithLabels), new PropertyMetadata(string.Empty));
        public static readonly DependencyProperty TickLabelsOffsetProperty = DependencyProperty.Register("TickLabelsOffset", typeof(double), typeof(TickBarVerticalWithLabels), new PropertyMetadata(0.0));

        [Bindable(true)]
        [Category("Appearance")]
        public string TickLabels
        {
            get { return (string)GetValue(TickLabelsProperty); }
            set {
                SetValue(TickLabelsProperty, value);
                InvalidateVisual();
            }
        }

        [Bindable(true)]
        [Category("Appearance")]
        public double TickLabelsOffset
        {
            get { return (double)GetValue(TickLabelsOffsetProperty); }
            set {
                SetValue(TickLabelsOffsetProperty, value);
                InvalidateVisual();
            }
        }

        protected override void OnRender(DrawingContext dc)
        {
            base.OnRender(dc);

            var height = base.ActualHeight - ReservedSpace;
            var tickRange = Maximum - Minimum;
            var tickCount = (int)(tickRange / TickFrequency) + 1;

            var labels = TickLabels.Split(',');
            if (labels.Length != tickCount)
                return;

            FontFamily fontFamily = new FontFamily("Segoe UI");
            var fontPointSize = 16;
            var fontHeight = Math.Ceiling(fontPointSize * fontFamily.LineSpacing);
            var typeface = new Typeface("Segoe");

            var cultureInfo = CultureInfo.GetCultureInfo(Language.IetfLanguageTag);

            var verticalOffset = ReservedSpace / 2 - fontHeight / 2;
            var tickSpacing = height * this.TickFrequency / tickRange;

            for (var i = 0; i < tickCount; ++i)
            {
                var formattedText = new FormattedText(labels[i], cultureInfo, FlowDirection.RightToLeft, typeface, fontPointSize, Fill);
                var y = verticalOffset + height - (i * tickSpacing);
                dc.DrawText(formattedText, new Point(TickLabelsOffset, y));
            }
        }
    }

}
