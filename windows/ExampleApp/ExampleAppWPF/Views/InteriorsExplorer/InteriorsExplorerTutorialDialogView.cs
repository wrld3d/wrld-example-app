using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class InteriorsExplorerTutorialDialogView : ControlBase
    {
		public const Double AnimationTimeMilliseconds = 250;
		
		private const int DialogOutlineSize = 2;

        private Grid m_container;
		private Grid m_outline;
		private Image m_outlineArrow;
		private Grid m_label;
		private Image m_arrow;
		private TextBlock m_title;
        private TextBlock m_description;

		public InteriorsExplorerTutorialDialogView() {}

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            
            m_container = (Grid) GetTemplateChild("DialogContainer");
            m_container.Opacity = 0;
			m_outline = (Grid) GetTemplateChild("DialogOutline");
			m_outlineArrow = (Image) GetTemplateChild("DialogOutlineArrow");
			m_label = (Grid) GetTemplateChild("DialogLabel");
			m_arrow = (Image) GetTemplateChild("DialogArrow");

			m_title = (TextBlock) GetTemplateChild("DialogTitle");
			m_description = (TextBlock) GetTemplateChild("DialogDescription");
        }

        public void RepositionDialog(double xPosition,
                                        double yPosition,
                                        Thickness rootContainerMargin,
                                        int arrowOffset)
        {
			ResizeDialog();
			
			Thickness containerMargin = m_container.Margin;
			containerMargin.Right = xPosition;
			containerMargin.Bottom = yPosition - m_container.Height;

			double offsetY = arrowOffset;

			if(containerMargin.Bottom < 0)
			{
                offsetY -= containerMargin.Bottom;
				containerMargin.Bottom = 0;
			}

            Thickness arrowMargin = m_arrow.Margin;
			arrowMargin.Top = Math.Round((m_outline.Height / 2) - (m_arrow.Height / 2)) + offsetY;
			m_arrow.Margin = arrowMargin;

			Thickness outlineArrowMargin = m_outlineArrow.Margin;
			outlineArrowMargin.Top = arrowMargin.Top - 1;
			m_outlineArrow.Margin = outlineArrowMargin;

			containerMargin.Bottom -= rootContainerMargin.Bottom;
			m_container.Margin = containerMargin;
        }
        public void AnimateTo(double t, double delayMilliseconds)
        {
            DoubleAnimation animation = new DoubleAnimation();
            animation.From = m_container.Opacity;
			animation.To = t;
			animation.Duration = new Duration(TimeSpan.FromMilliseconds(AnimationTimeMilliseconds));
			animation.BeginTime = TimeSpan.FromMilliseconds(delayMilliseconds);
            m_container.BeginAnimation(OpacityProperty, animation);
        }

		public void SetDialogText(string title, string description)
		{
			m_title.Text = title;
			m_description.Text = description;
		}

        public double GetHeight()
        {
            return m_container.Height;
        }

		private void ResizeDialog()
		{
			Thickness titleMargin = m_title.Margin;
			Thickness descriptionMargin = m_description.Margin;

			m_label.Height = descriptionMargin.Top + m_description.ActualHeight + descriptionMargin.Bottom;
			m_outline.Height = m_label.Height + (DialogOutlineSize * 2);
			m_container.Height = m_outline.Height;

			Thickness arrowMargin = m_arrow.Margin;
			arrowMargin.Top = Math.Round((m_outline.Height / 2) - (m_arrow.Height / 2));
			m_arrow.Margin = arrowMargin;

			Thickness outlineArrowMargin = m_outlineArrow.Margin;
			outlineArrowMargin.Top = arrowMargin.Top - 1;
			m_outlineArrow.Margin = outlineArrowMargin;
		}
    }
}
