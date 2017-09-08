//-----------------------------------------------------------------------
// <copyright file="QuertyKeyboard.cs" company="Polaris Community">
//     This code is distributed under the Microsoft Public License (MS-PL).
// </copyright>
//-----------------------------------------------------------------------
namespace ExampleAppWPF.VirtualKeyboard
{
    using System;
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.Linq;
    using System.Windows;
    using System.Windows.Input;

    public delegate void CustomKeyEvent(string key);
    public delegate void ControlKeyEvent(int key);

    public class QuertyKeyboard : ControlBase
    {
        private enum ShiftState
        {
            ShiftUp,
            ShiftDown
        }

        private ShiftState m_shiftState = ShiftState.ShiftUp;

        public event CustomKeyEvent CustomKeyUp;
        public event ControlKeyEvent ControlKeyUp;

        private static List<VirtualKeyboardButton> KeyboardButtons = new List<VirtualKeyboardButton>();

        public static readonly DependencyProperty IsShiftPressedProperty =
            DependencyProperty.Register(
                "IsShiftPressed", typeof(bool), typeof(QuertyKeyboard),
                new FrameworkPropertyMetadata(false));

        public bool IsShiftPressed
        {
            get { return m_shiftState != ShiftState.ShiftUp; }
        }

        #region KeyboardLayout

        /// <summary>
        /// KeyboardLayout Dependency Property
        /// </summary>
        public static readonly DependencyProperty KeyboardLayoutProperty =
            DependencyProperty.Register(
                "KeyboardLayout",
                typeof(string),
                typeof(QuertyKeyboard),
                new FrameworkPropertyMetadata("QuertyState", new PropertyChangedCallback(OnKeyboardLayoutChanged)));

        /// <summary>
        /// Gets or sets the KeyboardLayout property.  This dependency property
        /// indicates the current layout of the on-screen Stringboard.
        /// </summary>
        public string KeyboardLayout
        {
            get { return (string)GetValue(KeyboardLayoutProperty); }
            set { SetValue(KeyboardLayoutProperty, value); }
        }

        /// <summary>
        /// Handles changes to the KeyboardLayout property.
        /// </summary>
        private static void OnKeyboardLayoutChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((QuertyKeyboard)d).OnKeyboardLayoutChanged(e);
        }

        /// <summary>
        /// Provides derived classes an opportunity to handle changes to the KeyboardLayout property.
        /// </summary>
        protected virtual void OnKeyboardLayoutChanged(DependencyPropertyChangedEventArgs e)
        {
            VisualStateManager.GoToState(this, (string) e.NewValue, true);
        }

        #endregion KeyboardLayout

        #region DisabledKeys

        /// <summary>
        /// DisabledKeys Dependency Property
        /// </summary>
        public static readonly DependencyProperty DisabledKeysProperty =
            DependencyProperty.Register("DisabledKeys", typeof(ObservableCollection<String>), typeof(QuertyKeyboard),
                new FrameworkPropertyMetadata(null,
                    new PropertyChangedCallback(OnDisabledKeysChanged)));

        /// <summary>
        /// Gets or sets the DisabledKeys property.  This dependency property
        /// indicates the observable collection of Strings that have been disabled on the Stringboard.
        /// </summary>
        public ObservableCollection<String> DisabledKeys
        {
            get { return (ObservableCollection<String>)GetValue(DisabledKeysProperty); }
            set { SetValue(DisabledKeysProperty, value); }
        }

        /// <summary>
        /// Handles changes to the DisabledKeys property.
        /// </summary>
        private static void OnDisabledKeysChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((QuertyKeyboard)d).OnDisabledKeysChanged(e);
        }

        /// <summary>
        /// Provides derived classes an opportunity to handle changes to the DisabledKeys property.
        /// </summary>
        protected virtual void OnDisabledKeysChanged(DependencyPropertyChangedEventArgs e)
        {
            var DisabledKeys = e.OldValue as ObservableCollection<String>;
            if (DisabledKeys != null)
            {
                DisabledKeys.CollectionChanged -= new System.Collections.Specialized.NotifyCollectionChangedEventHandler(DisabledKeys_CollectionChanged);
            }
            DisabledKeys = e.NewValue as ObservableCollection<String>;
            if (DisabledKeys != null)
            {
                DisabledKeys.CollectionChanged += new System.Collections.Specialized.NotifyCollectionChangedEventHandler(DisabledKeys_CollectionChanged);
            }
        }

        #endregion DisabledKeys

        static QuertyKeyboard()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(QuertyKeyboard), new FrameworkPropertyMetadata(typeof(QuertyKeyboard)));
            Application.Current.Exit += new ExitEventHandler(Application_Exit);
        }

        private IEnumerable<VirtualKeyboardButton> FindVisualChildren(DependencyObject obj)
        {
            if (obj == null)
            {
                yield break;
            }

            for (int i = 0; i < System.Windows.Media.VisualTreeHelper.GetChildrenCount(obj); ++i)
            {
                var child = System.Windows.Media.VisualTreeHelper.GetChild(obj, i);
                if (child != null && child is VirtualKeyboardButton)
                {
                    yield return (VirtualKeyboardButton)child;
                }
                else
                {
                    foreach (VirtualKeyboardButton recChild in FindVisualChildren(child))
                    {
                        yield return recChild;
                    }
                }
            }
        }

        static void Application_Exit(object sender, ExitEventArgs e)
        {
            VirtualKeyboardService.Instance.ReleaseStickyKeys();
        }

        private void OnCustomKeyEvent(string key)
        {
            if (key == "ShiftKey")
            {
                UpdateKeyboardShift(IsShiftPressed ? ShiftState.ShiftUp: ShiftState.ShiftDown);
            }
            else if (CustomKeyUp != null)
            {
                UpdateKeyboardShift(ShiftState.ShiftUp);
                CustomKeyUp(key);
            }
        }

        private void OnControlKeyEvent(KeysEx controlInputValue)
        {
            if (ControlKeyUp != null)
            {
                UpdateKeyboardShift(ShiftState.ShiftUp);
                ControlKeyUp((int)controlInputValue);
            }
        }

        private void DisabledKeys_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            var disabledKeyArray = (from String disabledKey in e.NewItems
                                    select disabledKey).ToArray();
            var enabledKeyArray = (from String enabledKey in e.OldItems
                                   select enabledKey).ToArray();
            switch (e.Action)
            {
                case System.Collections.Specialized.NotifyCollectionChangedAction.Add:
                    OnNewDisabledKeys(disabledKeyArray);
                    break;
                case System.Collections.Specialized.NotifyCollectionChangedAction.Reset:
                case System.Collections.Specialized.NotifyCollectionChangedAction.Remove:
                    OnNewEnabledKeys(enabledKeyArray);
                    break;
                case System.Collections.Specialized.NotifyCollectionChangedAction.Replace:
                    OnNewDisabledKeys(disabledKeyArray);
                    OnNewEnabledKeys(enabledKeyArray);
                    break;
                default:
                case System.Collections.Specialized.NotifyCollectionChangedAction.Move:
                    break;
            }
        }

        private void OnNewEnabledKeys(string[] enabledKeyArray)
        {
            foreach (var enabledKey in enabledKeyArray)
            {
                var element = GetTemplateChild(enabledKey) as VirtualKeyboardButton;
                element.IsEnabled = true;
            }
        }

        private void OnNewDisabledKeys(string[] disabledKeyArray)
        {
            foreach (var disabledKey in disabledKeyArray)
            {
                var element = GetTemplateChild(disabledKey) as VirtualKeyboardButton;
                element.IsEnabled = false;
            }
        }

        private void OnExecuteVirtualKeyStroke(string partName, VirtualKeyboardButton key)
        {
            if (!OnCanExecuteStringStroke(partName)) { return; }

            VirtualKeyboardButton.KeyType type = key.GetKeyType();
            switch (type)
            {
                case VirtualKeyboardButton.KeyType.Input:
                    VirtualKeyboardInputButton inputButton = (VirtualKeyboardInputButton)key;
                    string keyInput = inputButton.GetKeyInputValue();
                    string keyShiftInput = inputButton.GetKeyShiftInputValue();
                    VirtualKeyboardService.Instance.SendKey(IsShiftPressed && !String.IsNullOrEmpty(keyShiftInput)
                        ? keyShiftInput[0]
                        : keyInput[0]);
                    UpdateKeyboardShift(ShiftState.ShiftUp);
                    break;

                case VirtualKeyboardButton.KeyType.Control:
                    VirtualKeyboardControlButton controlButton = (VirtualKeyboardControlButton)key;
                    VirtualKeyboardService.Instance.SendKey((KeysEx)controlButton.GetKeyControlInputValue());
                    OnControlKeyEvent((KeysEx)controlButton.GetKeyControlInputValue());
                    break;

                case VirtualKeyboardButton.KeyType.Special:
                    VirtualKeyboardSpecialButton specialButton = (VirtualKeyboardSpecialButton)key;
                    OnCustomKeyEvent(specialButton.GetKeySpecialInputValue());
                    break;

                default:
                    break;
            }
        }

        private void UpdateKeyboardShift(ShiftState shiftState)
        {
            if (m_shiftState != shiftState)
            {
                m_shiftState = shiftState;
                SetValue(IsShiftPressedProperty, IsShiftPressed);

                UpdateButtonLabels();
            }
        }

        private void UpdateButtonLabels()
        {
            foreach (var key in KeyboardButtons)
            {
                if (key.GetKeyType() == VirtualKeyboardButton.KeyType.Input)
                {
                    VirtualKeyboardInputButton inputButton = (VirtualKeyboardInputButton)key;
                    if (inputButton.GetAutoLabel())
                    {
                        string shiftInputValue = inputButton.GetKeyShiftInputValue();
                        inputButton.Content = IsShiftPressed && !String.IsNullOrEmpty(shiftInputValue)
                            ? shiftInputValue
                            : inputButton.GetKeyInputValue();
                    }
                }
            }
        }

        private bool OnCanExecuteStringStroke(String String)
        {
            if (DisabledKeys == null) { return true; }
            return !DisabledKeys.Contains(String);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            UpdateKeyboardButtons();

            foreach (var key in KeyboardButtons)
            {
                key.PreviewMouseDown += new MouseButtonEventHandler(Button_MouseDown);
                key.PreviewMouseUp += new MouseButtonEventHandler(Button_MouseUp);
                key.PreviewTouchDown += Button_TouchDown;
                key.PreviewTouchUp += Button_TouchUp;

                UpdateButtonLabels();
            }
        }

        private void UpdateKeyboardButtons()
        {
            KeyboardButtons.Clear();
            foreach (var c in FindVisualChildren(this))
            {
                KeyboardButtons.Add(c);
            }
        }

        private void Button_MouseDown(object sender, MouseEventArgs e)
        {
        }

        private void Button_MouseUp(object sender, MouseEventArgs e)
        {
            var key = sender as VirtualKeyboardButton;
            OnExecuteVirtualKeyStroke(key.Name, key);
        }

        private void Button_TouchDown(object sender, TouchEventArgs e)
        {
            e.Handled = true;
        }

        private void Button_TouchUp(object sender, TouchEventArgs e)
        {
            var key = sender as VirtualKeyboardButton;
            OnExecuteVirtualKeyStroke(key.Name, key);
        }

        public void ReleaseKeys()
        {
            VirtualKeyboardService.Instance.ReleaseStickyKeys();
        }
    }
}
