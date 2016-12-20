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
    using System.Windows.Controls;
    using System.Windows.Input;

    public delegate void CustomKeyEvent(string key);

    [TemplateVisualState(Name = VisualStateQuertyName, GroupName = VisualStateGroupKeyboardLayoutName)]
    [TemplateVisualState(Name = VisualStateNumericName, GroupName = VisualStateGroupKeyboardLayoutName)]

    public class QuertyKeyboard : ControlBase
    {
        #region Template Parts

        public event CustomKeyEvent CustomKeyUp;

        private static List<VirtualKeyboardButton> KeyboardButtons = new List<VirtualKeyboardButton>();

        private bool isShiftPressed = false;

        #endregion Template Parts

        #region Visual states

        private const String VisualStateGroupKeyboardLayoutName = "KeyboardLayoutStates";
        private const String VisualStateQuertyName = "QuertyState";
        private const String VisualStateNumericName = "NumericState";

        private VisualStateGroup KeyboardLayoutVisualStateGroup;
        private VisualState QuertyVisualState;
        private VisualState NumericVisualState;

        #endregion Visual states

        public static readonly DependencyProperty IsShiftPressedProperty =
            DependencyProperty.Register(
                "IsShiftPressed", typeof(bool), typeof(QuertyKeyboard),
                new FrameworkPropertyMetadata(false));

        public bool IsShiftPressed
        {
            get { return isShiftPressed; }
            set {
                isShiftPressed = value;
                SetValue(IsShiftPressedProperty, value);
            }
        }

        #region KeyboardLayout

        /// <summary>
        /// KeyboardLayout Dependency Property
        /// </summary>
        public static readonly DependencyProperty KeyboardLayoutProperty =
            DependencyProperty.Register("KeyboardLayout", typeof(KeyboardLayout), typeof(QuertyKeyboard),
                new FrameworkPropertyMetadata((KeyboardLayout.QuertyState),
                    new PropertyChangedCallback(OnKeyboardLayoutChanged)));

        /// <summary>
        /// Gets or sets the KeyboardLayout property.  This dependency property
        /// indicates the current layout of the on-screen Stringboard.
        /// </summary>
        public KeyboardLayout KeyboardLayout
        {
            get { return (KeyboardLayout)GetValue(KeyboardLayoutProperty); }
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
            VisualStateManager.GoToState(this, e.NewValue.ToString(), true);
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

        public int MaxLength
        {
            get { return maxLength; }
            set { maxLength = value; }
        }

        int maxLength = int.MaxValue;

        public KeyboardKeyStrokeHandler KeyStrokeHandler
        {
            get { return keyStrokeHandler; }
            set { keyStrokeHandler = value; }
        }

        KeyboardKeyStrokeHandler keyStrokeHandler = KeyboardKeyStrokeHandler.VirtualKeyboardBased;

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
            if (CustomKeyUp != null)
            {
                CustomKeyUp(key);
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

                    SetShift(false);
                    break;

                case VirtualKeyboardButton.KeyType.Control:
                    VirtualKeyboardControlButton controlButton = (VirtualKeyboardControlButton)key;
                    VirtualKeyboardService.Instance.SendKey((KeysEx)controlButton.GetKeyControlInputValue());
                    break;

                case VirtualKeyboardButton.KeyType.Special:
                    VirtualKeyboardSpecialButton specialButton = (VirtualKeyboardSpecialButton)key;
                    HandleCustomKey(specialButton.GetKeySpecialInputValue());
                    break;

                default:
                    break;
            }
        }

        private void HandleCustomKey(string specialValue)
        {
            switch (specialValue)
            {
                case "AlphaSwitch":
                    OnAlphaSwitchPressed();
                    break;

                case "NumericSwitch":
                    OnNumericSwitchPressed();
                    break;

                case "ShiftKey":
                    OnShiftPressed();
                    break;

                default:
                    OnCustomKeyEvent(specialValue);
                    break;
            }
        }

        private void SetShift(bool isPressed)
        {
            IsShiftPressed = isPressed;
            UpdateButtonLabels();
        }

        private void OnAlphaSwitchPressed()
        {
            KeyboardLayout = KeyboardLayout.QuertyState;
        }

        private void OnNumericSwitchPressed()
        {
            KeyboardLayout = KeyboardLayout.NumericState;
        }

        private void OnShiftPressed()
        {
            SetShift(!IsShiftPressed);
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

            KeyboardLayoutVisualStateGroup = GetTemplateChild(VisualStateGroupKeyboardLayoutName) as VisualStateGroup;
            QuertyVisualState = GetTemplateChild(VisualStateQuertyName) as VisualState;
            NumericVisualState = GetTemplateChild(VisualStateNumericName) as VisualState;

            UpdateKeyboardButtons();

            foreach (var key in KeyboardButtons)
            {
                //element.TouchUp += new EventHandler<TouchEventArgs>(Button_TouchUp);
                var touchUpEventListener = new WeakEventListener<QuertyKeyboard, object, TouchEventArgs>(this);
                touchUpEventListener.OnEventAction = (instance, source, eventArgs) =>
                    instance.Button_TouchUp(source, eventArgs);
                touchUpEventListener.OnDetachAction = (weakEventListenerParameter) =>
                    key.TouchUp -= weakEventListenerParameter.OnEvent;
                key.TouchUp += touchUpEventListener.OnEvent;

                //element.Click += new RoutedEventHandler(Button_Click);
                var clickEventListener = new WeakEventListener<QuertyKeyboard, object, RoutedEventArgs>(this);
                clickEventListener.OnEventAction = (instance, source, eventArgs) =>
                    instance.Button_Click(source, eventArgs);
                clickEventListener.OnDetachAction = (weakEventListenerParameter) =>
                    key.Click -= weakEventListenerParameter.OnEvent;
                key.Click += clickEventListener.OnEvent;

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

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var key = sender as VirtualKeyboardButton;
            OnExecuteVirtualKeyStroke(key.Name, key);
        }

        private void Button_TouchUp(object sender, TouchEventArgs e)
        {
            // I dont even think this needs to be here at all...
            //var button = sender as Button;
            //var keyStroke = button.CommandParameter as String;
            //OnExecuteVirtualKeyStroke ( keyStroke );
        }

        public void ReleaseKeys()
        {
            VirtualKeyboardService.Instance.ReleaseStickyKeys();
        }
    }

    public enum KeyboardLayout
    {
        QuertyState,
        NumericState,
    }

    public enum KeyboardKeyStrokeHandler
    {
        VirtualKeyboardBased,
        StringBased
    }
}
