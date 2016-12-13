using System.Diagnostics;
using System.Windows;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public static class XamlHelpers
    {
        public static void SetThicknessAnimationMarginValue(Storyboard storyboard, Thickness margin)
        {
            var animation = storyboard.Children;
            for (int i = 0; i < animation.Count; ++i)
            {
                if (animation[i] is ThicknessAnimationUsingKeyFrames)
                {
                    var iconAnimKeyFrame = ((ThicknessAnimationUsingKeyFrames)animation[i]).KeyFrames[0];
                    Debug.Assert(iconAnimKeyFrame != null, "iconAnimKeyFrame cannot be null");
                    iconAnimKeyFrame.Value = margin;
                    return;
                }
            }

            Debug.WriteLine("ThicknessAnimationUsingKeyFrames animation could not be found");
        }

        public static void UpdateThicknessAnimationMarginValue(Storyboard storyboard, string animationName)
        {
            Thickness margin = (Thickness)Application.Current.Resources[animationName + "Margin"];
            Debug.Assert(margin != null, "margin cannot be null");
            XamlHelpers.SetThicknessAnimationMarginValue(storyboard, margin);
        }
    }
}
