using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public class WorldPinOnMapView : ControlBase
    {
        protected IntPtr m_nativeCallerPointer;
        private int m_stateChangeAnimationTimeMilliseconds = 200;
        private TextBlock m_titleView;
        private TextBlock m_detailsView;
        private Image m_poiRatingImage;
        private Image m_poiAccreditationImage;
        private TextBlock m_reviewsCountView;
        private Image m_downArrow;
        private StackPanel m_mainPanel;
        private MainWindow m_currentWindow;
        private StackPanel m_reviewImageAndNumber;

        private const int MaxSubtitleLength = 22;

        private ControlClickHandler m_clickHandler;

        static WorldPinOnMapView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(WorldPinOnMapView), new FrameworkPropertyMetadata(typeof(WorldPinOnMapView)));
        }

        public WorldPinOnMapView(IntPtr nativeCallerPointer, float offset)
        {
            Width = Double.NaN;
            Height = Double.NaN;

            m_nativeCallerPointer = nativeCallerPointer;
            
            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            Background = new SolidColorBrush(Colors.Cyan);
            UseLayoutRounding = true;
            SnapsToDevicePixels = true;

            Visibility = Visibility.Hidden;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_mainPanel = (StackPanel)GetTemplateChild("SearchResultOnMapView");
            m_titleView = (TextBlock)GetTemplateChild("SearchResultOnMapViewTitle");
            m_detailsView = (TextBlock)GetTemplateChild("SearchResultOnMapViewDetails");
            m_poiRatingImage = (Image)GetTemplateChild("SearchResultOnMapViewImage");
            m_downArrow = (Image)GetTemplateChild("DownArrow");
            m_reviewsCountView = (TextBlock)GetTemplateChild("SearchResultOnMapReviewCount");
            m_poiAccreditationImage = (Image)GetTemplateChild("SearchResultOnMapAccreditationLogo");
            m_reviewImageAndNumber = (StackPanel)GetTemplateChild("ReviewsPanel");

            m_clickHandler = new ControlClickHandler(OnMouseLeftButtonUp, this);
        }

        private void OnMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            ExampleApp.WorldPinOnMapCLI.OnSelected(m_nativeCallerPointer);
        }

        private string GetSanitizedSubtitle(string subtitle)
        {
            var result = subtitle.Replace("\n", "");
            result = result.Replace("\t", " ");
            result = result.Replace("\r", "");

            if(result.Length > MaxSubtitleLength)
            {
                result = result.Remove(MaxSubtitleLength) + "...";
            }

            return result;
        }

        public void Show(string title, string subtitle, string ratingsImg, int reviewCount, float modality)
        {
            Visibility = Visibility.Visible;
            
            if (reviewCount == 0)
            {
                m_detailsView.Text = GetSanitizedSubtitle(subtitle);

                if (ratingsImg.Length != 0)
                {
                    m_poiAccreditationImage.Visibility = Visibility.Visible;
                }
                else
                {
                    m_poiAccreditationImage.Visibility = Visibility.Collapsed;
                }

                m_detailsView.Visibility = string.IsNullOrWhiteSpace(m_detailsView.Text) ? Visibility.Collapsed : Visibility.Visible;
                m_reviewImageAndNumber.Visibility = Visibility.Collapsed;
            }
            else
            {
                m_poiRatingImage.Source = StartupResourceLoader.GetBitmap(ratingsImg + ".png");
                m_reviewsCountView.Text = " (" + reviewCount.ToString() + ")";

                m_reviewImageAndNumber.Visibility = Visibility.Visible;
                m_detailsView.Visibility = Visibility.Collapsed;
                m_poiAccreditationImage.Visibility = Visibility.Visible;
            }

            m_titleView.Text = title;

            var targetAlpha = 1.0f - modality;
            AnimateToAlpha(targetAlpha);

            IsEnabled = targetAlpha > 0.0f ? true : false;
        }

        public void UpdateScreenLocation(float x, float y)
        {
            m_mainPanel.RenderTransform =
                new TranslateTransform(
                   x - (0.5 * RenderSize.Width),
                   y - (0.5 * RenderSize.Height) - (m_mainPanel.ActualHeight * 0.5));
        }

        public void UpdateScreenVisibility(float onScreenState)
        {
            AnimateToAlpha(onScreenState);

            IsEnabled = onScreenState > 0.0f ? true : false;
        }

        public void Dismiss()
        {
            AnimateToAlpha(0.0f);
            IsEnabled = false;
        }

        private void AnimateToAlpha(float targetAlpha)
        {
            System.Windows.Media.Animation.DoubleAnimation trans = new System.Windows.Media.Animation.DoubleAnimation();
            trans.From = this.Opacity;
            trans.To = targetAlpha;
            trans.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));
            this.BeginAnimation(OpacityProperty, trans);
        }
    }
}
