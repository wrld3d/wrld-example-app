using System;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;

namespace ExampleAppWPF
{
    [System.Windows.Markup.ContentProperty("LabelContent")]
    public class TickBarVerticalWithLabels : TickBar
    {
        public static readonly DependencyProperty LabelContentProperty = DependencyProperty.Register("LabelContent", typeof(object), typeof(TickBarVerticalWithLabels), null);
        public static readonly DependencyProperty TickLabelsProperty = DependencyProperty.Register("TickLabels", typeof(string), typeof(TickBarVerticalWithLabels), new FrameworkPropertyMetadata(string.Empty, FrameworkPropertyMetadataOptions.AffectsRender));
        public static readonly DependencyProperty TickLabelsOffsetProperty = DependencyProperty.Register("TickLabelsOffset", typeof(double), typeof(TickBarVerticalWithLabels), new FrameworkPropertyMetadata(0.0, FrameworkPropertyMetadataOptions.AffectsRender));
        public static readonly DependencyProperty FontSizeProperty = DependencyProperty.Register("FontSize", typeof(int), typeof(TickBarVerticalWithLabels), new FrameworkPropertyMetadata(16, FrameworkPropertyMetadataOptions.AffectsRender));
        public static readonly DependencyProperty TickLabelsOpacityProperty = DependencyProperty.Register("TickLabelsOpacity", typeof(double), typeof(TickBarVerticalWithLabels), new FrameworkPropertyMetadata(0.0, FrameworkPropertyMetadataOptions.AffectsRender));


        public TickBarVerticalWithLabels()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(TickBarVerticalWithLabels), new FrameworkPropertyMetadata(typeof(TickBarVerticalWithLabels)));
        }

        public object LabelContent
        {
            get { return GetValue(LabelContentProperty); }
            set { SetValue(LabelContentProperty, value); }
        }
        
        [Bindable(true)]
        [Category("Appearance")]
        public int FontSize
        {
            get { return (int)GetValue(FontSizeProperty); }
            set { SetValue(FontSizeProperty, value); }
        }

        [Bindable(true)]
        [Category("Appearance")]
        public string TickLabels
        {
            get { return (string)GetValue(TickLabelsProperty); }
            set { SetValue(TickLabelsProperty, value); }
        }

        [Bindable(true)]
        [Category("Appearance")]
        public double TickLabelsOffset
        {
            get { return (double)GetValue(TickLabelsOffsetProperty); }
            set { SetValue(TickLabelsOffsetProperty, value); }
        }

        [Bindable(true)]
        [Category("Appearance")]
        public double TickLabelsOpacity
        {
            get { return (double)GetValue(TickLabelsOpacityProperty); }
            set { SetValue(TickLabelsOpacityProperty, value); }
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
            var fontPointSize = FontSize;
            var fontHeight = Math.Ceiling(fontPointSize * fontFamily.LineSpacing);
            var typeface = new Typeface("Segoe");

            var cultureInfo = CultureInfo.GetCultureInfo(Language.IetfLanguageTag);

            var verticalOffset = ReservedSpace / 2 - fontHeight / 2;
            var tickSpacing = height * this.TickFrequency / tickRange;

            dc.PushOpacity(TickLabelsOpacity);

            for (var i = 0; i < tickCount; ++i)
            {
                var formattedText = new FormattedText(labels[i], cultureInfo, FlowDirection.LeftToRight, typeface, fontPointSize, Fill);
                formattedText.TextAlignment = TextAlignment.Right;
                var y = verticalOffset + height - (i * tickSpacing);
                dc.DrawText(formattedText, new Point(TickLabelsOffset, y));
            }

            dc.Pop();
        }
    }

}
