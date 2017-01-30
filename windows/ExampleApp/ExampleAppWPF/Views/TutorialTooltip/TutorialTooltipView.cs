using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace ExampleAppWPF
{
    class TutorialTooltipView : ControlBase
    {
        private enum Edge
        {
            Top,
            Left,
            Right,
            Bottom
        };

        private const double DefaultArrowAngle = 0.0;
        private const double DefaultPointHeight = 20.0;
        private const double DefaultArrowSize = 26.0;

        private Edge m_arrowEdge;
        private Path m_arrow;
        private Border m_boxBorder;
        private double m_arrowAngle = DefaultArrowAngle;
        private double m_arrowPointHeight = DefaultPointHeight;
        private double m_arrowSize = DefaultArrowSize;

        public static readonly DependencyProperty FixedWidthProperty =
            DependencyProperty.Register(
                "FixedWidth",
                typeof(double?),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(null));

        public static readonly DependencyProperty FixedHeightProperty =
            DependencyProperty.Register(
                "FixedHeight",
                typeof(double?),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(null));

        public static readonly DependencyProperty ShowSeparatingLineProperty =
            DependencyProperty.Register(
                "ShowSeparatingLine",
                typeof(bool),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(false));

        public static readonly DependencyProperty ArrowPointHeightProperty =
            DependencyProperty.Register(
                "ArrowPointHeight",
                typeof(double),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(DefaultPointHeight));

        public static readonly DependencyProperty ArrowSizeProperty =
            DependencyProperty.Register(
                "ArrowSize",
                typeof(double),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(DefaultArrowSize));

        public static readonly DependencyProperty ArrowAngleDegreesProperty =
            DependencyProperty.Register(
                "ArrowAngleDegrees",
                typeof(double),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(DefaultArrowAngle));

        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register(
                "Title",
                typeof(string),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(string.Empty));

        public static readonly DependencyProperty DescriptionProperty =
            DependencyProperty.Register(
                "Description",
                typeof(string),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(string.Empty));

        public static readonly DependencyProperty LeftColumnValueProperty =
            DependencyProperty.Register(
                "LeftColumnValue",
                typeof(string),
                typeof(TutorialTooltipView),
                new UIPropertyMetadata(string.Empty));

        public double? FixedWidth
        {
            get { return (double?)GetValue(FixedWidthProperty); }
            set
            {
                m_boxBorder.Width = value.HasValue ? value.Value : double.NaN;
                SetValue(FixedWidthProperty, value);
            }
        }

        public double? FixedHeight
        {
            get { return (double?)GetValue(FixedHeightProperty); }
            set
            {
                m_boxBorder.Height = value.HasValue ? value.Value : double.NaN;
                SetValue(FixedHeightProperty, value);
            }
        }

        public double ArrowSize
        {
            get { return m_arrowSize;  }
            set
            {
                m_arrowSize = value;
                UpdateArrowGeometry(m_arrowAngle);
                SetValue(ArrowSizeProperty, m_arrowSize);
            }
        }

        public double ArrowPointHeight
        {
            get { return m_arrowPointHeight; }
            set
            {
                m_arrowPointHeight = value;
                UpdateArrowGeometry(m_arrowAngle);
                SetValue(ArrowPointHeightProperty, m_arrowPointHeight);
            }
        }

        public bool ShowSeparatingLine
        {
            get { return (bool)GetValue(ShowSeparatingLineProperty); }
            set { SetValue(ShowSeparatingLineProperty, value); }
        }

        public double ArrowAngleDegrees
        {
            get { return Rad2Deg(m_arrowAngle); }
            set
            {
                m_arrowAngle = Deg2Rad(value);
                UpdateArrowGeometry(m_arrowAngle);
                SetValue(ArrowAngleDegreesProperty, m_arrowAngle);
            }
        }

        public string Title
        {
            get { return (string)GetValue(TitleProperty); }
            set { SetValue(TitleProperty, value); }
        }

        public string Description
        {
            get { return (string)GetValue(DescriptionProperty); }
            set { SetValue(DescriptionProperty, value); }
        }

        public string LeftColumnValue
        {
            get { return (string)GetValue(LeftColumnValueProperty); }
            set { SetValue(LeftColumnValueProperty, value); }
        }

        static TutorialTooltipView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(
                typeof(TutorialTooltipView),
                new FrameworkPropertyMetadata(typeof(TutorialTooltipView)));
        }

        public TutorialTooltipView()
        {
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_boxBorder = (Border)GetTemplateChild("BoxBorder");

            m_arrow = (Path)GetTemplateChild("Arrow");
            m_arrowPointHeight = (double)GetValue(ArrowPointHeightProperty);
            m_arrowSize = (double)GetValue(ArrowSizeProperty);
            m_arrowAngle = Deg2Rad((double)GetValue(ArrowAngleDegreesProperty));
            m_boxBorder.SizeChanged += (o, e) =>
            {
                UpdateArrowGeometry(m_arrowAngle);
            };

            double? fixedWidth = (double?)GetValue(FixedWidthProperty);
            double? fixedHeight = (double?)GetValue(FixedHeightProperty);
            m_boxBorder.Width = fixedWidth.HasValue ? fixedWidth.Value : double.NaN;
            m_boxBorder.Height = fixedHeight.HasValue ? fixedHeight.Value : double.NaN;
        }

        public double GetTooltipWidth()
        {
            double pointHeight = m_arrowEdge == Edge.Right || m_arrowEdge == Edge.Left ? ArrowPointHeight : 0.0;
            return m_boxBorder.ActualWidth + pointHeight;
        }

        public double GetTooltipHeight()
        {
            double pointHeight = m_arrowEdge == Edge.Top || m_arrowEdge == Edge.Bottom ? ArrowPointHeight : 0.0;
            return m_boxBorder.ActualHeight + pointHeight;
        }


        private void UpdateArrowGeometry(double angleRads)
        {
            m_arrow.Data = ArrowPointData(m_boxBorder.ActualWidth, m_boxBorder.ActualHeight, angleRads);
        }

        private Geometry ArrowPointData(double width, double height, double edgeRotation)
        {
            double halfHeight = height / 2.0;
            double halfWidth = width / 2.0;
            double topEdgeAngle = Math.Atan2(halfHeight, halfWidth);

            switch (IntersectedEdge(edgeRotation, topEdgeAngle))
            {
                case Edge.Bottom:
                    {
                        m_arrowEdge = Edge.Bottom;
                        Point intersection = new Point(halfHeight / -Math.Tan(edgeRotation) + halfWidth, height);
                        return MakeArrow(new Point(intersection.X, intersection.Y - 1.0),
                                         new Point(intersection.X + ArrowSize / 2.0, intersection.Y + ArrowPointHeight),
                                         new Point(intersection.X + ArrowSize, intersection.Y - 1.0));
                    }

                case Edge.Left:
                    {
                        m_arrowEdge = Edge.Left;
                        Point intersection = new Point(0.0, halfWidth * Math.Tan(edgeRotation) + halfHeight);
                        return MakeArrow(new Point(intersection.X + 1.0, intersection.Y),
                                         new Point(intersection.X - ArrowPointHeight, intersection.Y + ArrowSize / 2.0),
                                         new Point(intersection.X + 1.0, intersection.Y + ArrowSize));
                    }

                case Edge.Top:
                    {
                        m_arrowEdge = Edge.Top;
                        Point intersection = new Point(halfHeight / Math.Tan(edgeRotation) + halfWidth, 0.0);
                        return MakeArrow(new Point(intersection.X, intersection.Y + 1.0),
                                         new Point(intersection.X + ArrowSize / 2.0, intersection.Y - ArrowPointHeight),
                                         new Point(intersection.X + ArrowSize, intersection.Y + 1.0));
                    }

                case Edge.Right:
                    {
                        m_arrowEdge = Edge.Right;
                        Point intersection = new Point(width, halfWidth * -Math.Tan(edgeRotation) + halfHeight);
                        return MakeArrow(new Point(intersection.X - 1.0, intersection.Y),
                                         new Point(intersection.X + ArrowPointHeight, intersection.Y + ArrowSize / 2.0),
                                         new Point(intersection.X - 1.0, intersection.Y + ArrowSize));
                    }

                default:
                    return null;
            }
        }

        private Edge IntersectedEdge(double edgeRotation, double topEdgeAngle)
        {
            if (edgeRotation < topEdgeAngle || edgeRotation > 2.0 * Math.PI - topEdgeAngle)
            {
                return Edge.Right;
            }
            else if (edgeRotation > Math.PI + topEdgeAngle)
            {
                return Edge.Bottom;
            }
            else if (edgeRotation > Math.PI - topEdgeAngle)
            {
                return Edge.Left;
            }
            else
            {
                return Edge.Top;
            }
        }

        private Geometry MakeArrow(Point p1, Point p2, Point p3)
        {
            LineSegment unstrokedClosingEdge = new LineSegment(p1, false);
            PathFigure triangle = new PathFigure(p1,
                                                 new PathSegment[]
                                                 {
                                                     new LineSegment(p2, true),
                                                     new LineSegment(p3, true),
                                                     unstrokedClosingEdge
                                                 },
                                                 true);
            return new PathGeometry(new PathFigure[] { triangle });
        }

        private static double Deg2Rad(double angle)
        {
            return angle * Math.PI / 180.0;
        }

        private static double Rad2Deg(double rads)
        {
            return rads * 180.0 / Math.PI;
        }
    }
}