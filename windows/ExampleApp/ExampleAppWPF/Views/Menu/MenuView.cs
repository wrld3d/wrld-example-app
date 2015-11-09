using ExampleApp;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace ExampleAppWPF
{
    public abstract class MenuView : Button
    {
        protected ListBox m_list = null;
        protected Button m_dragTabView;
        protected bool m_dragInProgress = false;
        protected bool m_loggingEnabled = false;

        protected IntPtr m_nativeCallerPointer;

        protected double m_stateChangeAnimationTimeMilliseconds = 200;
        protected double m_mainContainerVisibleOnScreenWhenClosedDip = 0;

        protected double m_offscreenYPx;
        protected double m_closedYPx;
        protected double m_openYPx;

        protected double m_mainContainerOffscreenOffsetXPx;
        protected double m_totalWidthPx;
        protected double m_offscreenXPx;
        protected double m_closedXPx;
        protected double m_openXPx;

        protected double m_dragStartPosXPx;
        protected double m_controlStartPosXPx;

        protected double m_touchAnchorXPx;
        protected double m_touchAnchorYPx;

        protected double m_dragThresholdPx;

        protected bool m_dragAnchorSet = false;
        protected bool m_canBeginDrag = false;

        protected bool m_animating = false;
        protected Point m_animationEndPos = new Point();
        protected Point m_animationStartPos = new Point();
        protected Point m_animationCurrentPos = new Point();

        protected bool m_isFirstAnimationCeremony = true;

        MainWindow m_mainWindow;

        protected abstract void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap);

        static MenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MenuView), new FrameworkPropertyMetadata(typeof(MenuView)));
        }

        public MenuView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            int dragThesholdDip = 10;
            m_dragThresholdPx = ConversionHelpers.AndroidToWindowsDip(dragThesholdDip);

            Click += MenuView_Click;

            m_mainWindow = (MainWindow)Application.Current.MainWindow;
        }

        

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

               
        }


        protected void MenuView_Click(object sender, RoutedEventArgs e)
        {
            if (m_animating)
            {
                return;
            }

            MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
        }

        public void Destroy()
        {
            //m_mainWindow.SizeChanged -= PerformLayout;
            m_mainWindow.MainGrid.Children.Remove(this);
        }

        public bool IsAnimating()
        {
            return m_animating;
        }

        public bool IsDragging()
        {
            return m_dragInProgress;
        }
        protected void MenuView_MouseMove(object sender, MouseEventArgs e)
        {
            if (m_animating || !CanInteract())
            {
                m_dragAnchorSet = false;
                return;
            }

            if (!m_canBeginDrag)
            {
                m_canBeginDrag = MenuViewCLIMethods.TryBeginDrag(m_nativeCallerPointer);
            }

            var mousePosition = e.GetPosition(m_mainWindow.MainGrid);
            int xPx = (int)(mousePosition.X);
            int yPx = (int)(mousePosition.Y);

            // :TODO: need to re-write this across multiple events
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                m_touchAnchorXPx = xPx;
                m_touchAnchorYPx = yPx;
                m_dragAnchorSet = true;
            }
            else if (e.LeftButton == MouseButtonState.Released)
            {
                m_canBeginDrag = false;
                if (m_dragInProgress)
                {
                    HandleDragFinish(xPx, yPx);
                }
                else if (m_dragAnchorSet)
                {
                    RaiseEvent(new RoutedEventArgs(Button.ClickEvent));
                }
                m_dragAnchorSet = false;
            }
            else
            {
                if (m_dragInProgress)
                {
                    HandleDragUpdate(xPx, yPx);
                }
                else if (m_canBeginDrag && m_dragAnchorSet)
                {
                    double mag = Math.Sqrt((m_touchAnchorXPx - xPx) * (m_touchAnchorXPx - xPx) + (m_touchAnchorYPx - yPx) * (m_touchAnchorYPx - yPx));

                    if (mag >= m_dragThresholdPx)
                    {
                        HandleDragStart(xPx, yPx);
                    }
                }
            }
        }

        protected void HandleDragStart(int xPx, int yPx)
        {
            m_dragInProgress = true;
            m_dragStartPosXPx = xPx;
            m_controlStartPosXPx = ViewXPx();
            Debug.WriteLine("ACTION_DOWN x: {0}", xPx);

            MenuViewCLIMethods.ViewDragStarted(m_nativeCallerPointer);
        }

        protected abstract void HandleDragUpdate(int xPx, int yPx);
        protected abstract void HandleDragFinish(int xPx, int yPx);

        public void UpdateAnimation(float deltaSeconds)
        {
            Vector totalDelta = m_animationEndPos - m_animationStartPos;
                //PointFExtensions.vectorSubtract(m_animationEndPos, m_animationStartPos);
            double totalDeltaLen = totalDelta.Length;
            bool done;

            if (totalDeltaLen > 0.001)
            {
                double animationUnitsPerSecond = (totalDeltaLen / (m_stateChangeAnimationTimeMilliseconds / 1e3));
                double frameDeltaUnits = animationUnitsPerSecond * deltaSeconds;
                Vector norm = totalDelta / totalDeltaLen;
                Vector delta = norm * frameDeltaUnits;
                m_animationCurrentPos += delta;

                Vector currentPosDirToEnd = m_animationEndPos - m_animationCurrentPos;
                currentPosDirToEnd.Normalize();
                
                double dp = Vector.Multiply(currentPosDirToEnd, norm);
                done = dp < 0.0;
            }
            else
            {
                done = true;
            }

            AnimateToCurrentPos(false);

            if (done)
            {
                m_animationCurrentPos.X = m_animationEndPos.X;
                m_animationCurrentPos.Y = m_animationEndPos.Y;

                AnimateToCurrentPos(false);

                Debug.WriteLine("animation complete", "(" + m_animationCurrentPos.X + "," + m_animationCurrentPos.Y + ")");

                bool closed = (m_animationEndPos.X == m_closedXPx && m_animationStartPos.X != m_animationEndPos.X) ||
                                 (m_animationEndPos.Y == m_closedYPx && m_animationStartPos.Y != m_animationEndPos.Y);

                bool open = (m_animationEndPos.X == m_openXPx && m_animationStartPos.X != m_animationEndPos.X) ||
                               (m_animationEndPos.Y == m_openYPx && m_animationStartPos.Y != m_animationEndPos.Y);

                if (closed)
                {
                    MenuViewCLIMethods.ViewCloseCompleted(m_nativeCallerPointer);
                    m_mainWindow.EnableInput();
                }
                else if (open)
                {
                    AnimateToCurrentPos(true);
                    MenuViewCLIMethods.ViewOpenCompleted(m_nativeCallerPointer);
                    m_mainWindow.DisableInput();
                }

                m_animating = false;
            }
        }

        void AnimateToCurrentPos(bool animationCompleteAndOpen)
        {
            SetViewX(m_animationCurrentPos.X);
            SetViewY(m_animationCurrentPos.Y);
            m_list.IsHitTestVisible = animationCompleteAndOpen;
        }

        public float NormalisedAnimationProgress()
        {
            float totalDistance = (float)(m_animationEndPos - m_animationStartPos).Length;
            float currentDistance = (float)(m_animationEndPos - m_animationCurrentPos).Length;
            float result = currentDistance / totalDistance;
            result = Math.Max(Math.Min(result, 1.0f), 0.0f);

            if (m_animationEndPos.X != m_animationStartPos.X)
            {
                if (m_animationEndPos.X == m_openXPx)
                {
                    result = 1.0f - result;
                }
            }
            else if (m_animationEndPos.Y != m_animationStartPos.Y)
            {
                if (m_animationEndPos.Y == m_openYPx)
                {
                    result = 1.0f - result;
                }
            }

            return result;
        }

        public virtual void AnimateToClosedOnScreen()
        {
            bool shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && ViewXPx() != m_closedXPx);

            if (shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.X != m_closedXPx))
            {
                double newXPx = m_closedXPx;
                Debug.WriteLine("AnimateToClosedOnScreen x: {0}", newXPx);
                AnimateViewToX(newXPx);
            }
        }

        public virtual void AnimateToOpenOnScreen()
        {
            bool shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && ViewXPx() != m_openXPx);

            if (shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.X != m_openXPx))
            {
                double newXPx = m_openXPx;
                Debug.WriteLine("AnimateToOpenOnScreen x: {0}", newXPx);
                AnimateViewToX(newXPx);
            }
        }

        public void AnimateOffScreen()
        {
            Dispatcher.Invoke(() =>
            {
                bool shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && ViewXPx() != m_offscreenXPx);

                if (shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.X != m_offscreenXPx))
                {
                    double newXPx = m_offscreenXPx;
                    Debug.WriteLine("AnimateOffScreen x: {0}", newXPx);
                    AnimateViewToX(newXPx);
                }
            });
        }

        public void AnimateToIntermediateOnScreenState(float onScreenState)
        {
            if (m_animating)
            {
                return;
            }

            double viewXPx = ViewXPx();
            double newXPx = m_offscreenXPx + (((m_closedXPx - m_offscreenXPx) * onScreenState) + 0.5);

            if (!m_dragInProgress && viewXPx != newXPx)
            {
                Debug.WriteLine("AnimateToIntermediateOnScreenState x: {0}", newXPx);
                SetViewX(newXPx);
            }
        }

        public void AnimateToIntermediateOpenState(float openState)
        {
            if (m_animating)
            {
                return;
            }

            double newXPx = m_closedXPx + (((m_openXPx - m_closedXPx) * openState) + 0.5);

            if (!m_dragInProgress && ViewXPx() != newXPx)
            {
                Debug.WriteLine("AnimateToIntermediateOpenState x: {0}", newXPx);
                SetViewX(newXPx);
            }
        }

        public void PopulateData(
            IntPtr nativeCallerPointer,
            string[] groupNames,
            int[] groupSizes,
            bool[] groupIsExpandable,
            string[] childJson)
        {
            List<string> groups = groupNames.ToList();
            List<bool> groupsExpandable = groupIsExpandable.ToList();
            Dictionary<string, List<string>> childMap = new Dictionary<string, List<string>>();
            int childIndex = 0;
            for (int groupIndex = 0; groupIndex < groups.Count; groupIndex++)
            {
                int size = groupSizes[groupIndex];
                List<string> children = new List<string>();
                for (int i = 0; i < size; i++)
                {
                    children.Add(childJson[childIndex]);
                    childIndex++;
                }

                childMap[groupNames[groupIndex]] = children;
            }

            RefreshListData(groups, groupsExpandable, childMap);
        }

        protected void AnimateViewToX(double xAsPx)
        {
            if (xAsPx == m_offscreenXPx || xAsPx == m_closedXPx)
            {
                m_animationStartPos.X = m_isFirstAnimationCeremony ? m_offscreenXPx : m_openXPx;
            }
            else if (xAsPx == m_openXPx)
            {
                m_animationStartPos.X = m_closedXPx;
            }
            else
            {
                throw new ArgumentException(string.Format("Invalid animation target {0} ", xAsPx));
            }

            m_isFirstAnimationCeremony = false;

            m_animationStartPos.Y =
                m_animationCurrentPos.Y =
                    m_animationEndPos.Y = ViewYPx();

            m_animationCurrentPos.X = ViewXPx();
            m_animationEndPos.X = xAsPx;

            m_animating = true;
        }

        protected void AnimateViewToY(double yAsPx)
        {
            bool fromOffScreen = (ViewYPx() == m_offscreenYPx);

            if (yAsPx == m_offscreenYPx || yAsPx == m_closedYPx)
            {
                m_animationStartPos.Y = (m_isFirstAnimationCeremony || fromOffScreen) ? m_offscreenYPx : m_openYPx;
            }
            else if (yAsPx == m_openYPx)
            {
                m_animationStartPos.Y = m_closedYPx;
            }
            else
            {
                throw new ArgumentException(string.Format("Invalid animation target {0}", yAsPx));
            }

            m_isFirstAnimationCeremony = false;

            m_animationStartPos.X =
                m_animationCurrentPos.X =
                    m_animationEndPos.X = ViewXPx();

            m_animationCurrentPos.Y = ViewYPx();
            m_animationEndPos.Y = yAsPx;

            m_animating = true;
        }
        protected void SetViewX(double viewXPx)
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            Debug.WriteLine("SetViewX {0}", viewXPx);
            RenderTransform = new TranslateTransform(viewXPx, currentPosition.Y);
        }

        protected void SetViewY(double viewYPx)
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            Debug.WriteLine("SetViewY {0}", viewYPx);
            RenderTransform = new TranslateTransform(currentPosition.X, viewYPx);
        }

        protected int ViewXPx()
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            int x = (int)currentPosition.X;
            return x;
        }

        protected int ViewYPx()
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            int y = (int)currentPosition.Y;
            return y;
        }

        protected bool StartedClosed(double controlStartPosXDip)
        {
            double deltaClosed = Math.Abs(controlStartPosXDip - m_closedXPx);
            double deltaOpen = Math.Abs(controlStartPosXDip - m_openXPx);
            return deltaClosed < deltaOpen;
        }

        protected bool CanInteract()
        {
            return m_dragInProgress || IsClosed() || IsOpen();
        }

        protected bool IsClosed()
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            return currentPosition.X == m_closedXPx;
        }

        protected bool IsOpen()
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            return currentPosition.X == m_openXPx;
        }
    }
}
