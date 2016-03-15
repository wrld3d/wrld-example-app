using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class StoryboardRunner
    {
        private Storyboard m_storyboard;
        private List<FrameworkElement> m_targets = new List<FrameworkElement>();

        public event Action AllCompleted;

        public bool IsAnimating { get { return m_targets.Any(); } }

        public StoryboardRunner(Storyboard storyboard)
        {
            m_storyboard = storyboard;
        }

        public void Begin(List<FrameworkElement> targets)
        {
            m_targets.AddRange(targets);
            m_storyboard.Completed += OnCompleted;
            foreach (var target in m_targets)
            {
                Storyboard.SetTarget(m_storyboard, target);
                m_storyboard.Begin(target);
            }
        }

        private void OnCompleted(object sender, EventArgs e)
        {
            var clock = sender as Clock;
            var target = Storyboard.GetTarget(clock.Timeline) as FrameworkElement;

            m_targets.Remove(target);
            if (!m_targets.Any())
            {
                m_storyboard.Completed -= OnCompleted;
                if (AllCompleted != null)
                    AllCompleted();
            }
        }
    }
}
