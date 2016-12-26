//-----------------------------------------------------------------------
// <copyright file="VirtualKeyboardService.cs" company="Polaris Community">
//     This code is distributed under the Microsoft Public License (MS-PL).
// </copyright>
//-----------------------------------------------------------------------
namespace ExampleAppWPF.VirtualKeyboard
{
    using System.Runtime.InteropServices;

    /// <summary>
    /// Allows to interact with the Low Level Keyboard functions by handling the state of a
    /// virtual keyboard.
    /// </summary>
    /// <remarks>
    /// Relevant portions of this code were obtained from the following sources and are covered
    /// by their respective licenses:
    /// http://wosk.codeplex.com/SourceControl/list/changesets
    /// http://www.ownedcore.com/forums/mmo/warhammer-online/186390-sendinput-example-c.html
    /// http://stackoverflow.com/questions/3644881/simulating-keyboard-with-sendinput-api-in-directinput-applications
    /// </remarks>
    public sealed class VirtualKeyboardService
    {
        private void Initialize()
        {
        }

        #region Singleton Pattern w/ Constructor

        private VirtualKeyboardService()
            : base()
        {
            this.Initialize();
        }

        public static VirtualKeyboardService Instance
        {
            get
            {
                return SingletonVirtualKeyboardServiceCreator._Instance;
            }
        }

        private class SingletonVirtualKeyboardServiceCreator
        {
            private SingletonVirtualKeyboardServiceCreator() { }

            public static VirtualKeyboardService _Instance = new VirtualKeyboardService();
        }

        #endregion Singleton Pattern w/ Constructor

        public void PressAndRelease(KeysEx keyCode)
        {
            try
            {
                SendKey(keyCode);
            }
            catch
            { }

            ReleaseStickyKeys();
        }

        public void ReleaseStickyKeys()
        {
            //TODO: any key can be configured to be "sticky". check the "pressedKeys" collection/dictionary
            Shift = false;
            Alt = false;
            Ctrl = false;
            RightShift = false;
            RightAlt = false;
            RightCtrl = false;
            Win = false;
            CapsLock = false;
        }

        public void PressAndHold(KeysEx keyCode)
        {
            switch (keyCode)
            {
                case KeysEx.VK_LSHIFT:
                case KeysEx.VK_RSHIFT:
                case KeysEx.VK_SHIFT: this.Shift = !this.Shift; break;
                case KeysEx.VK_MENU: Alt = !Alt; break;
                case KeysEx.VK_CONTROL:
                case KeysEx.VK_RCONTROL:
                case KeysEx.VK_LCONTROL: this.Ctrl = !this.Ctrl; break;
                case KeysEx.VK_LWIN: this.Win = !this.Win; break;
            }

            //TODO: consider implementing collection of pressed keys
            // instead of handling all cases manually

            //VK keyCode = (VK)Enum.Parse(typeof(VK), key);
            //if (!pressedKeys.Keys.Contains(keyCode)) pressedKeys.Add(keyCode, false);
            //if (null==pressedKeys[keyCode]) ReleaseSticky(keyCode); else PressSticky(keyCode);
            //pressedKeys[keyCode] = !pressedKeys[keyCode];
        }

        private INPUT CreateInputKey(KeysEx keyCode, KEYBDINPUT_FLAGS dwFlags)
        {
            return new INPUT()
            {
                type = INPUT_TYPE.INPUT_KEYBOARD,
                u = new InputUnion
                {
                    ki = new KEYBDINPUT
                    {
                        wVk = (System.UInt16) keyCode,
                        wScan = 0,
                        dwFlags = dwFlags,
                        dwExtraInfo = NativeWin32.GetMessageExtraInfo()
                    }
                }
            };
        }

        private uint SendInputs(INPUT[] inputs)
        {
            System.UInt32 ret = NativeWin32.SendInput((System.UInt32) inputs.Length, inputs, Marshal.SizeOf(typeof(INPUT)));
            return ret == inputs.Length ? ret : NativeWin32.GetLastError();
        }

        private uint SendInput(INPUT input)
        {
            return SendInputs(new INPUT[] { input });
        }

        private INPUT CreateUtf16InputKey(ushort utf16, KEYBDINPUT_FLAGS dwFlags)
        {
            return new INPUT()
            {
                type = INPUT_TYPE.INPUT_KEYBOARD,
                u = new InputUnion
                {
                    ki = new KEYBDINPUT
                    {
                        wVk = 0,
                        wScan = utf16,
                        dwFlags = KEYBDINPUT_FLAGS.KEYEVENTF_UNICODE | dwFlags,
                        dwExtraInfo = (System.UIntPtr) 0
                    }
                }
            };
        }

        private uint SendUtf16Input(ushort utf16)
        {
            return SendInputs(new INPUT[] { CreateUtf16InputKey(utf16, 0), CreateUtf16InputKey(utf16, KEYBDINPUT_FLAGS.KEYEVENTF_KEYUP) });
        }

        public void SendKey(ushort utf16)
        {
            SendUtf16Input(utf16);
        }

        public void PressAndReleaseKey(KeysEx keyCode)
        {
            SendInputs(new INPUT[]
            {
                CreateInputKey(keyCode, 0),
                CreateInputKey(keyCode, KEYBDINPUT_FLAGS.KEYEVENTF_KEYUP)
            });
        }

        public void PressKey(KeysEx keyCode)
        {
            SendInput(CreateInputKey(keyCode, 0));
        }

        public void ReleaseKey(KeysEx keyCode)
        {
            SendInput(CreateInputKey(keyCode, KEYBDINPUT_FLAGS.KEYEVENTF_KEYUP));
        }

        public void SendKey(KeysEx keyCode)
        {
            PressAndReleaseKey(keyCode);
        }

        private bool _LeftShift;
        private bool _RightShift;
        private bool _CapsLock;

        public bool LeftShift
        {
            get { return _LeftShift; }
            set
            {
                if (_LeftShift != value)
                {
                    _LeftShift = value;
                    if (_LeftShift) PressKey(KeysEx.VK_LSHIFT); else ReleaseKey(KeysEx.VK_LSHIFT);
                }
            }
        }

        public bool RightShift
        {
            get { return _RightShift; }
            set
            {
                if (_RightShift != value)
                {
                    _RightShift = value;
                    if (_RightShift) PressKey(KeysEx.VK_RSHIFT); else ReleaseKey(KeysEx.VK_RSHIFT);
                }
            }
        }

        public bool Shift
        {
            get { return (LeftShift || RightShift); }
            set
            {
                if (LeftShift != value) // since we don't know which Shift user wants, we have to assume one.
                {
                    LeftShift = value;
                    if (Shift) PressKey(KeysEx.VK_SHIFT); else ReleaseKey(KeysEx.VK_SHIFT);
                }
            }
        }

        public bool CapsLock
        {
            get { return _CapsLock; }
            set
            {
                if (_CapsLock != value)
                {
                    _CapsLock = value;
                    if (_CapsLock) PressKey(KeysEx.VK_CAPITAL); else ReleaseKey(KeysEx.VK_CAPITAL);
                }
            }
        }

        private bool _LeftAlt;
        private bool _RightAlt;

        public bool LeftAlt
        {
            get { return _LeftAlt; }
            set
            {
                if (_LeftAlt != value)
                {
                    _LeftAlt = value;
                    if (_LeftAlt) PressKey(KeysEx.VK_MENU); else ReleaseKey(KeysEx.VK_MENU);
                }
            }
        }

        public bool RightAlt
        {
            get { return _RightAlt; }
            set
            {
                if (_RightAlt != value)
                {
                    _RightAlt = value;
                    if (_RightAlt) PressKey(KeysEx.VK_RMENU); else ReleaseKey(KeysEx.VK_RMENU);
                }
            }
        }

        public bool Alt
        {
            get { return (LeftAlt || RightAlt); }
            set
            {
                if (LeftAlt != value)
                {
                    LeftAlt = value;
                    if (LeftAlt) PressKey(KeysEx.VK_MENU); else ReleaseKey(KeysEx.VK_MENU);
                }
            }
        }

        private bool LeftCtrl { get; set; }

        private bool RightCtrl { get; set; }

        public bool Ctrl
        {
            get { return (LeftCtrl || RightCtrl); }
            set
            {
                if (LeftCtrl != value)
                {
                    LeftCtrl = value;
                    if (LeftCtrl) PressKey(KeysEx.VK_CONTROL); else ReleaseKey(KeysEx.VK_CONTROL);
                }
            }
        }

        private bool LeftWin { get; set; }

        public bool Win
        {
            get { return LeftWin; }
            set
            {
                if (LeftWin != value)
                {
                    LeftWin = value;
                    if (LeftWin) PressKey(KeysEx.VK_LWIN); else ReleaseKey(KeysEx.VK_LWIN);
                }
            }
        }
    }
}
