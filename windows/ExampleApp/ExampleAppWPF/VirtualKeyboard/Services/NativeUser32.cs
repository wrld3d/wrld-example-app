//-----------------------------------------------------------------------
// <copyright file="NativeUser32.cs" company="Polaris Community">
//     This code is distributed under the Microsoft Public License (MS-PL).
// </copyright>
// For win32 api and data layout see:
//   https://msdn.microsoft.com/en-us/library/windows/desktop/ms646310(v=vs.85).aspx
//-----------------------------------------------------------------------
namespace ExampleAppWPF.VirtualKeyboard
{
    using System.Runtime.InteropServices;

    enum KEYBDINPUT_FLAGS : System.UInt32
    {
        KEYEVENTF_EXTENDEDKEY = 0x0001,
        KEYEVENTF_KEYUP       = 0x0002,
        KEYEVENTF_SCANCODE    = 0x0008,
        KEYEVENTF_UNICODE     = 0x0004
    }

    enum INPUT_TYPE : System.UInt32
    {
        INPUT_MOUSE    = 0,
        INPUT_KEYBOARD = 1,
        INPUT_HARDWARE = 2,
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct KEYBDINPUT
    {
        public System.UInt16 wVk;
        public System.UInt16 wScan;
        public KEYBDINPUT_FLAGS dwFlags;
        public System.UInt32 time;
        public System.UIntPtr dwExtraInfo;
    };

    [StructLayout(LayoutKind.Sequential)]
    internal struct MOUSEINPUT
    {
        public System.Int32 dx;
        public System.Int32 dy;
        public System.UInt32 mouseData;
        public System.UInt32 dwFlags;
        public System.UInt32 time;
        public System.UIntPtr dwExtraInfo;
    };

    [StructLayout(LayoutKind.Sequential)]
    internal struct HARDWAREINPUT
    {
        public System.UInt32 uMsg;
        public System.UInt16 wParamL;
        public System.UInt16 wParamH;
    }

    [StructLayout(LayoutKind.Explicit)]
    struct InputUnion
    {
        [FieldOffset(0)]
        public MOUSEINPUT mi;
        [FieldOffset(0)]
        public KEYBDINPUT ki;
        [FieldOffset(0)]
        public HARDWAREINPUT hi;
    }

    struct INPUT
    {
        public INPUT_TYPE type;
        public InputUnion u;
    }

    /// <summary>
    /// Class wrapper for imported DLL functions
    /// </summary>
    internal static class NativeWin32
    {
        [DllImport("user32.DLL")]
        public static extern System.UInt32 SendInput(System.UInt32 nInputs, INPUT[] pInputs, int cbSize);

        [DllImport("user32.dll")]
        public static extern System.UIntPtr GetMessageExtraInfo();

        [DllImport("Kernel32.dll")]
        public static extern System.UInt32 GetLastError();
    }
}
