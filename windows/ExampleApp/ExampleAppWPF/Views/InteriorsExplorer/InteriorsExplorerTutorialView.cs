using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    public class InteriorsExplorerTutorialView : ButtonBase
    {
        private InteriorsExplorerTutorialDialogView m_exitDialog;

        private InteriorsExplorerTutorialDialogView m_changeFloorDialog;
        
        public InteriorsExplorerTutorialView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(InteriorsExplorerTutorialView), new FrameworkPropertyMetadata(typeof(InteriorsExplorerTutorialView)));
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            Click += OnViewClicked;
            
            m_exitDialog = (InteriorsExplorerTutorialDialogView) GetTemplateChild("ExitDialog");
			m_exitDialog.ApplyTemplate();
			m_exitDialog.setDialogText(Properties.Resources.InteriorsExplorerTutorialView_ExitDialogTitle.Replace("\\n", "\n"),
										Properties.Resources.InteriorsExplorerTutorialView_ExitDialogDescription.Replace("\\n", "\n"));

			m_changeFloorDialog = (InteriorsExplorerTutorialDialogView) GetTemplateChild("ChangeFloorDialog");
			m_changeFloorDialog.ApplyTemplate();
			m_changeFloorDialog.setDialogText(Properties.Resources.InteriorsExplorerTutorialView_ChangeFloorDialogTitle.Replace("\\n", "\n"),
												Properties.Resources.InteriorsExplorerTutorialView_ChangeFloorDialogDescription.Replace("\\n", "\n"));
		}

        public void OnViewClicked(object sender, RoutedEventArgs e)
        {
            hide();
        }

        public void repositionDialogs(float newPositionX,
                                        float dismissButtonPositionY,
                                        float dismissButtonHeight,
                                        float floorChangeButtonPositionY,
                                        float floorChangeButtonHeight,
                                        bool showChangeFloorDialog,
										Thickness rootContainerMargin)
        {
			m_exitDialog.repositionDialog(Application.Current.MainWindow.Width - newPositionX, Application.Current.MainWindow.Height - dismissButtonPositionY, rootContainerMargin);

			m_changeFloorDialog.repositionDialog(Application.Current.MainWindow.Width - newPositionX, Application.Current.MainWindow.Height - floorChangeButtonPositionY, rootContainerMargin);
            m_changeFloorDialog.Visibility = showChangeFloorDialog ? Visibility.Visible : Visibility.Hidden;
        }
        public void animateTo(double t, double delayMilliseconds, bool animateDialogsAtSameTime)
        {
			m_exitDialog.animateTo(t, delayMilliseconds);
			m_changeFloorDialog.animateTo(t, delayMilliseconds + (animateDialogsAtSameTime ? 0 : InteriorsExplorerTutorialDialogView.AnimationTimeMilliseconds * 0.8f));
        }

		public void show(bool showExitDialog, bool showChangeFloorDialog)
		{
			Visibility = Visibility.Visible;

			m_exitDialog.Opacity = showExitDialog ? 1 : 0;
			m_changeFloorDialog.Opacity = showChangeFloorDialog ? 1 : 0;
		}

		public void hide()
		{
			Visibility = Visibility.Hidden;
		}
	}
}
