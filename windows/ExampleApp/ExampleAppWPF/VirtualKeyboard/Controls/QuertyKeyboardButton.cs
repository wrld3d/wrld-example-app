//-----------------------------------------------------------------------
// <copyright file="QuertyKeyboardButton.cs" company="Polaris Community">
//     This code is distributed under the Microsoft Public License (MS-PL).
// </copyright>
//-----------------------------------------------------------------------
namespace ExampleAppWPF.VirtualKeyboard
{
    using System.Windows;
    using System.Windows.Media.Animation;
    using System.Windows.Controls;

    [TemplatePart(Name = PressedStoryboardPartName, Type = typeof(Storyboard))]
    public class QuertyKeyboardButton : Button
    {

        #region PressedStoryboard Template Part
        private const string PressedStoryboardPartName = "PressedStoryboard";
        private Storyboard PressedStoryboardPart;
        #endregion

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            PressedStoryboardPart = this.GetTemplateChild(PressedStoryboardPartName) as Storyboard;
        }

        protected override void OnMouseDown(System.Windows.Input.MouseButtonEventArgs e)
        {
            TryPlayPressedStoryboard();
            base.OnMouseDown(e);
        }

        private void TryPlayPressedStoryboard()
        {
            if (PressedStoryboardPart != null)
            {
                PressedStoryboardPart.Begin();
            }
        }


    }
}
