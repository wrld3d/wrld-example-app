using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class InteriorsExplorerTutorialView : ButtonBase
    {
        private const int DialogGap = 10;

        private InteriorsExplorerTutorialDialogView m_exitDialog;

        private InteriorsExplorerTutorialDialogView m_changeFloorDialog;
        
        public InteriorsExplorerTutorialView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(InteriorsExplorerTutorialView), new FrameworkPropertyMetadata(typeof(InteriorsExplorerTutorialView)));
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            
            MainWindow mainWindow = (MainWindow) Application.Current.MainWindow;
            mainWindow.AddHandler(UIElement.MouseLeftButtonDownEvent, (RoutedEventHandler) OnMouseLeftButtonDown, true);
            mainWindow.AddHandler(UIElement.TouchDownEvent, (RoutedEventHandler) OnMouseLeftButtonDown, true);

            m_exitDialog = (InteriorsExplorerTutorialDialogView) GetTemplateChild("ExitDialog");
			m_exitDialog.ApplyTemplate();
			m_exitDialog.SetDialogText(Properties.Resources.InteriorsExplorerTutorialView_ExitDialogTitle.Replace("\\n", "\n"),
										Properties.Resources.InteriorsExplorerTutorialView_ExitDialogDescription.Replace("\\n", "\n"));

			m_changeFloorDialog = (InteriorsExplorerTutorialDialogView) GetTemplateChild("ChangeFloorDialog");
			m_changeFloorDialog.ApplyTemplate();
			m_changeFloorDialog.SetDialogText(Properties.Resources.InteriorsExplorerTutorialView_ChangeFloorDialogTitle.Replace("\\n", "\n"),
												Properties.Resources.InteriorsExplorerTutorialView_ChangeFloorDialogDescription.Replace("\\n", "\n"));
		}

        public void OnMouseLeftButtonDown(object sender, RoutedEventArgs e)
        {
            Hide();
        }

        public void RepositionDialogs(float newPositionX,
                                        float dismissButtonPositionY,
                                        float dismissButtonHeight,
                                        float floorChangeButtonPositionY,
                                        float floorChangeButtonHeight,
                                        bool showChangeFloorDialog,
										Thickness rootContainerMargin)
        {
            double exitDialogY = Application.Current.MainWindow.Height - dismissButtonPositionY;

            double changeDialogY = Application.Current.MainWindow.Height - floorChangeButtonPositionY;

            double exitDialogHeight = m_exitDialog.GetHeight();

            int offset = 0;

            int currentDialogGap = (int) (exitDialogY - changeDialogY - exitDialogHeight);
            if(currentDialogGap < DialogGap)
            {
                offset = (DialogGap - currentDialogGap) / 2;

                exitDialogY += offset;

                changeDialogY -= offset;
            }

            m_exitDialog.RepositionDialog(Application.Current.MainWindow.Width - newPositionX, exitDialogY, rootContainerMargin, offset);

			m_changeFloorDialog.RepositionDialog(Application.Current.MainWindow.Width - newPositionX, changeDialogY, rootContainerMargin, -offset);
            m_changeFloorDialog.Visibility = showChangeFloorDialog ? Visibility.Visible : Visibility.Hidden;
        }

        public void AnimateTo(double t, double delayMilliseconds, bool animateDialogsAtSameTime)
        {
			m_exitDialog.AnimateTo(t, delayMilliseconds + (animateDialogsAtSameTime ? 0 : InteriorsExplorerTutorialDialogView.AnimationTimeMilliseconds * 0.8f));
			m_changeFloorDialog.AnimateTo(t, delayMilliseconds);
        }

		public void Show(bool showExitDialog, bool showChangeFloorDialog)
		{
			Visibility = Visibility.Visible;

			m_exitDialog.Opacity = showExitDialog ? 1 : 0;
			m_changeFloorDialog.Opacity = showChangeFloorDialog ? 1 : 0;
		}

		public void Hide()
		{
			Visibility = Visibility.Hidden;
		}
	}
}
