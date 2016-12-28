//-----------------------------------------------------------------------
// <copyright file="KeysEx.cs" company="Polaris Community">
//     This code is distributed under the Microsoft Public License (MS-PL).
// </copyright>
//-----------------------------------------------------------------------
namespace ExampleAppWPF.VirtualKeyboard
{
    /// <summary>
    /// Enumeration with most of the Virtual Key of the Windows OS.
    /// </summary>
    /// <remarks>
    /// Relevant portions of this code were obtained from the following sources
    /// and are covered by their respective licenses:
    /// http://blogs.msdn.com/b/michkap/archive/2006/03/23/558658.aspx
    /// </remarks>
    public enum KeysEx : ushort
    {
        None = 0x00,
        VK_LBUTTON = System.Windows.Forms.Keys.LButton,             // 0x01
        VK_RBUTTON = System.Windows.Forms.Keys.RButton,             // 0x02
        VK_CANCEL = System.Windows.Forms.Keys.Cancel,              // 0x03
        VK_MBUTTON = System.Windows.Forms.Keys.MButton,             // 0x04
        VK_XBUTTON1 = System.Windows.Forms.Keys.XButton1,            // 0x05
        VK_XBUTTON2 = System.Windows.Forms.Keys.XButton2,            // 0x06
        /*
         * 0x07 : unassigned
         */
        VK_BACK = System.Windows.Forms.Keys.Back,                // 0x08
        VK_TAB = System.Windows.Forms.Keys.Tab,                 // 0x09
        /*
         * 0x0A - 0x0B : reserved
         */
        VK_CLEAR = System.Windows.Forms.Keys.Clear,               // 0x0C
        VK_RETURN = System.Windows.Forms.Keys.Return,              // 0x0D, System.Windows.Forms.Keys.Enter
        VK_SHIFT = System.Windows.Forms.Keys.ShiftKey,            // 0x10
        VK_CONTROL = System.Windows.Forms.Keys.ControlKey,          // 0x11
        VK_MENU = System.Windows.Forms.Keys.Menu,                // 0x12
        VK_PAUSE = System.Windows.Forms.Keys.Pause,               // 0x13
        VK_CAPITAL = System.Windows.Forms.Keys.Capital,             // 0x14, System.Windows.Forms.Keys.CapsLock
        VK_KANA = System.Windows.Forms.Keys.KanaMode,            // 0x15
        VK_HANGEUL = System.Windows.Forms.Keys.HanguelMode,         // 0x15, System.Windows.Forms.Keys.HangulMode
        VK_JUNJA = System.Windows.Forms.Keys.JunjaMode,           // 0x17
        VK_FINAL = System.Windows.Forms.Keys.FinalMode,           // 0x18
        VK_HANJA = System.Windows.Forms.Keys.HanjaMode,           // 0x19
        VK_KANJI = System.Windows.Forms.Keys.KanjiMode,           // 0x19
        VK_ESCAPE = System.Windows.Forms.Keys.Escape,              // 0x1B
        VK_CONVERT = System.Windows.Forms.Keys.IMEConvert,          // 0x1C
        VK_NONCONVERT = System.Windows.Forms.Keys.IMENonconvert,       // 0x1D
        VK_ACCEPT = System.Windows.Forms.Keys.IMEAceept,           // 0x1E, System.Windows.Forms.Keys.IMEAccept
        VK_MODECHANGE = System.Windows.Forms.Keys.IMEModeChange,       // 0x1F
        VK_SPACE = System.Windows.Forms.Keys.Space,               // 0x20
        VK_PRIOR = System.Windows.Forms.Keys.Prior,               // 0x21, System.Windows.Forms.Keys.PageUp
        VK_NEXT = System.Windows.Forms.Keys.Next,                // 0x22, System.Windows.Forms.Keys.PageDown
        VK_END = System.Windows.Forms.Keys.End,                 // 0x23
        VK_HOME = System.Windows.Forms.Keys.Home,                // 0x24
        VK_LEFT = System.Windows.Forms.Keys.Left,                // 0x25
        VK_UP = System.Windows.Forms.Keys.Up,                  // 0x26
        VK_RIGHT = System.Windows.Forms.Keys.Right,               // 0x27
        VK_DOWN = System.Windows.Forms.Keys.Down,                // 0x28
        VK_SELECT = System.Windows.Forms.Keys.Select,              // 0x29
        VK_PRINT = System.Windows.Forms.Keys.Print,               // 0x2A
        VK_EXECUTE = System.Windows.Forms.Keys.Execute,             // 0x2B
        VK_SNAPSHOT = System.Windows.Forms.Keys.Snapshot,            // 0x2C, System.Windows.Forms.Keys.PrintScreen
        VK_INSERT = System.Windows.Forms.Keys.Insert,              // 0x2D
        VK_DELETE = System.Windows.Forms.Keys.Delete,              // 0x2E
        VK_HELP = System.Windows.Forms.Keys.Help,                // 0x2F
        VK_0 = System.Windows.Forms.Keys.D0,                  // 0x30
        VK_1 = System.Windows.Forms.Keys.D1,                  // 0x31
        VK_2 = System.Windows.Forms.Keys.D2,                  // 0x32
        VK_3 = System.Windows.Forms.Keys.D3,                  // 0x33
        VK_4 = System.Windows.Forms.Keys.D4,                  // 0x34
        VK_5 = System.Windows.Forms.Keys.D5,                  // 0x35
        VK_6 = System.Windows.Forms.Keys.D6,                  // 0x36
        VK_7 = System.Windows.Forms.Keys.D7,                  // 0x37
        VK_8 = System.Windows.Forms.Keys.D8,                  // 0x38
        VK_9 = System.Windows.Forms.Keys.D9,                  // 0x39
        /*
         * 0x40 : unassigned
         */
        VK_A = System.Windows.Forms.Keys.A,                   // 0x41
        VK_B = System.Windows.Forms.Keys.B,                   // 0x42
        VK_C = System.Windows.Forms.Keys.C,                   // 0x43
        VK_D = System.Windows.Forms.Keys.D,                   // 0x44
        VK_E = System.Windows.Forms.Keys.E,                   // 0x45
        VK_F = System.Windows.Forms.Keys.F,                   // 0x46
        VK_G = System.Windows.Forms.Keys.G,                   // 0x47
        VK_H = System.Windows.Forms.Keys.H,                   // 0x48
        VK_I = System.Windows.Forms.Keys.I,                   // 0x49
        VK_J = System.Windows.Forms.Keys.J,                   // 0x4A
        VK_K = System.Windows.Forms.Keys.K,                   // 0x4B
        VK_L = System.Windows.Forms.Keys.L,                   // 0x4C
        VK_M = System.Windows.Forms.Keys.M,                   // 0x4D
        VK_N = System.Windows.Forms.Keys.N,                   // 0x4E
        VK_O = System.Windows.Forms.Keys.O,                   // 0x4F
        VK_P = System.Windows.Forms.Keys.P,                   // 0x50
        VK_Q = System.Windows.Forms.Keys.Q,                   // 0x51
        VK_R = System.Windows.Forms.Keys.R,                   // 0x52
        VK_S = System.Windows.Forms.Keys.S,                   // 0x53
        VK_T = System.Windows.Forms.Keys.T,                   // 0x54
        VK_U = System.Windows.Forms.Keys.U,                   // 0x55
        VK_V = System.Windows.Forms.Keys.V,                   // 0x56
        VK_W = System.Windows.Forms.Keys.W,                   // 0x57
        VK_X = System.Windows.Forms.Keys.X,                   // 0x58
        VK_Y = System.Windows.Forms.Keys.Y,                   // 0x59
        VK_Z = System.Windows.Forms.Keys.Z,                   // 0x5A
        VK_LWIN = System.Windows.Forms.Keys.LWin,                // 0x5B
        VK_RWIN = System.Windows.Forms.Keys.RWin,                // 0x5C
        VK_APPS = System.Windows.Forms.Keys.Apps,                // 0x5D
        /*
         * 0x5E : reserved
         */
        VK_SLEEP = 0x5f,                     // 0x5f, System.Windows.Forms.Keys.Sleep
        VK_NUMPAD0 = System.Windows.Forms.Keys.NumPad0,             // 0x60
        VK_NUMPAD1 = System.Windows.Forms.Keys.NumPad1,             // 0x61
        VK_NUMPAD2 = System.Windows.Forms.Keys.NumPad2,             // 0x62
        VK_NUMPAD3 = System.Windows.Forms.Keys.NumPad3,             // 0x63
        VK_NUMPAD4 = System.Windows.Forms.Keys.NumPad4,             // 0x64
        VK_NUMPAD5 = System.Windows.Forms.Keys.NumPad5,             // 0x65
        VK_NUMPAD6 = System.Windows.Forms.Keys.NumPad6,             // 0x66
        VK_NUMPAD7 = System.Windows.Forms.Keys.NumPad7,             // 0x67
        VK_NUMPAD8 = System.Windows.Forms.Keys.NumPad8,             // 0x68
        VK_NUMPAD9 = System.Windows.Forms.Keys.NumPad9,             // 0x69
        VK_MULTIPLY = System.Windows.Forms.Keys.Multiply,            // 0x6A
        VK_ADD = System.Windows.Forms.Keys.Add,                 // 0x6B
        VK_SEPARATOR = System.Windows.Forms.Keys.Separator,           // 0x6C
        VK_SUBTRACT = System.Windows.Forms.Keys.Subtract,            // 0x6D
        VK_DECIMAL = System.Windows.Forms.Keys.Decimal,             // 0x6E
        VK_DIVIDE = System.Windows.Forms.Keys.Divide,              // 0x6F
        VK_F1 = System.Windows.Forms.Keys.F1,                  // 0x70
        VK_F2 = System.Windows.Forms.Keys.F2,                  // 0x71
        VK_F3 = System.Windows.Forms.Keys.F3,                  // 0x72
        VK_F4 = System.Windows.Forms.Keys.F4,                  // 0x73
        VK_F5 = System.Windows.Forms.Keys.F5,                  // 0x74
        VK_F6 = System.Windows.Forms.Keys.F6,                  // 0x75
        VK_F7 = System.Windows.Forms.Keys.F7,                  // 0x76
        VK_F8 = System.Windows.Forms.Keys.F8,                  // 0x77
        VK_F9 = System.Windows.Forms.Keys.F9,                  // 0x78
        VK_F10 = System.Windows.Forms.Keys.F10,                 // 0x79
        VK_F11 = System.Windows.Forms.Keys.F11,                 // 0x7A
        VK_F12 = System.Windows.Forms.Keys.F12,                 // 0x7B
        VK_F13 = System.Windows.Forms.Keys.F13,                 // 0x7C
        VK_F14 = System.Windows.Forms.Keys.F14,                 // 0x7D
        VK_F15 = System.Windows.Forms.Keys.F15,                 // 0x7E
        VK_F16 = System.Windows.Forms.Keys.F16,                 // 0x7F
        VK_F17 = System.Windows.Forms.Keys.F17,                 // 0x80
        VK_F18 = System.Windows.Forms.Keys.F18,                 // 0x81
        VK_F19 = System.Windows.Forms.Keys.F19,                 // 0x82
        VK_F20 = System.Windows.Forms.Keys.F20,                 // 0x83
        VK_F21 = System.Windows.Forms.Keys.F21,                 // 0x84
        VK_F22 = System.Windows.Forms.Keys.F22,                 // 0x85
        VK_F23 = System.Windows.Forms.Keys.F23,                 // 0x86
        VK_F24 = System.Windows.Forms.Keys.F24,                 // 0x87
        /*
         * 0x88 - 0x8F : unassigned
         */
        VK_NUMLOCK = System.Windows.Forms.Keys.NumLock,             // 0x90
        VK_SCROLL = System.Windows.Forms.Keys.Scroll,              // 0x91
        VK_OEM_NEC_EQUAL = 0x92,                     // 0x92, NEC PC-9800 kbd definition
        VK_OEM_FJ_JISHO = 0x92,                     // 0x92, Fujitsu/OASYS kbd definition
        VK_OEM_FJ_MASSHOU = 0x93,                     // 0x93, Fujitsu/OASYS kbd definition
        VK_OEM_FJ_TOUROKU = 0x94,                     // 0x94, Fujitsu/OASYS kbd definition
        VK_OEM_FJ_LOYA = 0x95,                     // 0x95, Fujitsu/OASYS kbd definition
        VK_OEM_FJ_ROYA = 0x96,                     // 0x96, Fujitsu/OASYS kbd definition
        /*
         * 0x97 - 0x9F : unassigned
         */
        VK_LSHIFT = System.Windows.Forms.Keys.LShiftKey,           // 0xA0
        VK_RSHIFT = System.Windows.Forms.Keys.RShiftKey,           // 0xA1
        VK_LCONTROL = System.Windows.Forms.Keys.LControlKey,         // 0xA2
        VK_RCONTROL = System.Windows.Forms.Keys.RControlKey,         // 0xA3
        VK_LMENU = System.Windows.Forms.Keys.LMenu,               // 0xA4
        VK_RMENU = System.Windows.Forms.Keys.RMenu,               // 0xA5
        VK_BROWSER_BACK = System.Windows.Forms.Keys.BrowserBack,         // 0xA6
        VK_BROWSER_FORWARD = System.Windows.Forms.Keys.BrowserForward,      // 0xA7
        VK_BROWSER_REFRESH = System.Windows.Forms.Keys.BrowserRefresh,      // 0xA8
        VK_BROWSER_STOP = System.Windows.Forms.Keys.BrowserStop,         // 0xA9
        VK_BROWSER_SEARCH = System.Windows.Forms.Keys.BrowserSearch,       // 0xAA
        VK_BROWSER_FAVORITES = System.Windows.Forms.Keys.BrowserFavorites,    // 0xAB
        VK_BROWSER_HOME = System.Windows.Forms.Keys.BrowserHome,         // 0xAC
        VK_VOLUME_MUTE = System.Windows.Forms.Keys.VolumeMute,          // 0xAD
        VK_VOLUME_DOWN = System.Windows.Forms.Keys.VolumeDown,          // 0xAE
        VK_VOLUME_UP = System.Windows.Forms.Keys.VolumeUp,            // 0xAF
        VK_MEDIA_NEXT_TRACK = System.Windows.Forms.Keys.MediaNextTrack,      // 0xB0
        VK_MEDIA_PREV_TRACK = System.Windows.Forms.Keys.MediaPreviousTrack,  // 0xB1
        VK_MEDIA_STOP = System.Windows.Forms.Keys.MediaStop,           // 0xB2
        VK_MEDIA_PLAY_PAUSE = System.Windows.Forms.Keys.MediaPlayPause,      // 0xB3
        VK_LAUNCH_MAIL = System.Windows.Forms.Keys.LaunchMail,          // 0xB4
        VK_LAUNCH_MEDIA_SELECT = System.Windows.Forms.Keys.SelectMedia,         // 0xB5
        VK_LAUNCH_APP1 = System.Windows.Forms.Keys.LaunchApplication1,  // 0xB6
        VK_LAUNCH_APP2 = System.Windows.Forms.Keys.LaunchApplication2,  // 0xB7
        /*
         * 0xB8 - 0xB9 : reserved
         */
        VK_OEM_1 = System.Windows.Forms.Keys.OemSemicolon,        // 0xBA, System.Windows.Forms.Keys.Oem1
        VK_OEM_PLUS = System.Windows.Forms.Keys.Oemplus,             // 0xBB
        VK_OEM_COMMA = System.Windows.Forms.Keys.Oemcomma,            // 0xBC
        VK_OEM_MINUS = System.Windows.Forms.Keys.OemMinus,            // 0xBD
        VK_OEM_PERIOD = System.Windows.Forms.Keys.OemPeriod,           // 0xBE
        VK_OEM_2 = System.Windows.Forms.Keys.OemQuestion,         // 0xBF, System.Windows.Forms.Keys.Oem2
        VK_OEM_3 = System.Windows.Forms.Keys.Oemtilde,            // 0xC0, System.Windows.Forms.Keys.Oem3
        /*
         * 0xC1 - 0xD7 : reserved
         */
        /*
         * 0xD8 - 0xDA : unassigned
         */
        VK_OEM_4 = System.Windows.Forms.Keys.OemOpenBrackets,     // 0xDB, System.Windows.Forms.Keys.Oem4
        VK_OEM_5 = System.Windows.Forms.Keys.OemPipe,             // 0xDC, System.Windows.Forms.Keys.Oem5
        VK_OEM_6 = System.Windows.Forms.Keys.OemCloseBrackets,    // 0xDD, System.Windows.Forms.Keys.Oem6
        VK_OEM_7 = System.Windows.Forms.Keys.OemQuotes,           // 0xDE, System.Windows.Forms.Keys.Oem7
        VK_OEM_8 = System.Windows.Forms.Keys.Oem8,                // 0xDF
        /*
         * 0xE0 : reserved
         */
        VK_OEM_AX = 0xE1,                     // 0xE1, 'AX' key on Japanese AX kbd
        VK_OEM_102 = System.Windows.Forms.Keys.OemBackslash,        // 0xE2, System.Windows.Forms.Keys.Oem102
        VK_ICO_HELP = 0xE3,                     // 0xE3, Help key on ICO
        VK_ICO_00 = 0xE4,                     // 0xE4, 00 key on ICO
        VK_PROCESSKEY = System.Windows.Forms.Keys.ProcessKey,          // 0xE5
        VK_ICO_CLEAR = 0xE6,                     // 0xE6
        VK_PACKET = 0xE7,                     // 0xE7, System.Windows.Forms.Keys.Packet
        /*
         * 0xE8 : unassigned
         */
        VK_OEM_RESET = 0xE9,                     // 0xE9, Nokia/Ericsson definition
        VK_OEM_JUMP = 0xEA,                     // 0xEA, Nokia/Ericsson definition
        VK_OEM_PA1 = 0xEB,                     // 0xEB, Nokia/Ericsson definition
        VK_OEM_PA2 = 0xEC,                     // 0xEC, Nokia/Ericsson definition
        VK_OEM_PA3 = 0xED,                     // 0xED, Nokia/Ericsson definition
        VK_OEM_WSCTRL = 0xEE,                     // 0xEE, Nokia/Ericsson definition
        VK_OEM_CUSEL = 0xEF,                     // 0xEF, Nokia/Ericsson definition
        VK_OEM_ATTN = 0xF0,                     // 0xF0, Nokia/Ericsson definition
        VK_OEM_FINISH = 0xF1,                     // 0xF1, Nokia/Ericsson definition
        VK_OEM_COPY = 0xF2,                     // 0xF2, Nokia/Ericsson definition
        VK_OEM_AUTO = 0xF3,                     // 0xF3, Nokia/Ericsson definition
        VK_OEM_ENLW = 0xF4,                     // 0xF4, Nokia/Ericsson definition
        VK_OEM_BACKTAB = 0xF5,                     // 0xF5, Nokia/Ericsson definition
        VK_ATTN = System.Windows.Forms.Keys.Attn,                // 0xF6
        VK_CRSEL = System.Windows.Forms.Keys.Crsel,               // 0xF7
        VK_EXSEL = System.Windows.Forms.Keys.Exsel,               // 0xF8
        VK_EREOF = System.Windows.Forms.Keys.EraseEof,            // 0xF9
        VK_PLAY = System.Windows.Forms.Keys.Play,                // 0xFA
        VK_ZOOM = System.Windows.Forms.Keys.Zoom,                // 0xFB
        VK_NONAME = System.Windows.Forms.Keys.NoName,              // 0xFC
        VK_PA1 = System.Windows.Forms.Keys.Pa1,                 // 0xFD
        VK_OEM_CLEAR = System.Windows.Forms.Keys.OemClear,            // 0xFE
        /*
         * 0xFF : reserved
         */

        VK_RPARENTHESES = 0x130,
        VK_EXCLAMATION = 0x131,
        VK_AT = 0x132,
        VK_NUMBERSIGN = 0x133,
        VK_DOLLAR = 0x134,
        VK_PERCENTAGE = 0x135,
        VK_CIRCUMFLEX = 0x136,
        VK_AMPERSAND = 0x137,
        VK_LPARENTHESES = 0x139,
    }
}
