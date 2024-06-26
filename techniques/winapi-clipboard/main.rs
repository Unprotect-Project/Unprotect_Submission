#![warn(unused)]
#![warn(deprecated)]

use std::ffi::OsStr;
use std::mem::zeroed;
use std::os::windows::ffi::OsStrExt;
use std::ptr;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::Ordering;
use winapi::shared::minwindef::*;
use winapi::shared::windef::*;
use winapi::um::libloaderapi::*;
use winapi::um::winuser::*;
use winapi::um::winbase::GlobalLock;
use winapi::um::winbase::GlobalUnlock;

fn to_wstring(s: &str) -> Vec<u16> {
    OsStr::new(s)
        .encode_wide()
        .chain(std::iter::once(0))
        .collect()
}

static ADDED_LISTENER: AtomicBool = AtomicBool::new(false);

pub unsafe extern "system" fn window_proc(
    hwnd: HWND,
    msg: UINT,
    wparam: WPARAM,
    lparam: LPARAM,
) -> LRESULT {
    match msg {
        WM_CREATE => {
            let add_result = AddClipboardFormatListener(hwnd);
            if add_result == 1 {
                ADDED_LISTENER.store(true, Ordering::Relaxed);
                0
            } else {
                -1
            }
        }
        WM_DESTROY => {
            if ADDED_LISTENER.swap(false, Ordering::Relaxed) {
                RemoveClipboardFormatListener(hwnd);
            }
            PostQuitMessage(0);
            0
        }
        WM_CLIPBOARDUPDATE => {
            if OpenClipboard(ptr::null_mut()) != 0 {
                let handle = GetClipboardData(CF_UNICODETEXT);
                if !handle.is_null() {
                    let ptr = GlobalLock(handle) as *const u16;
                    if !ptr.is_null() {
                        let len = (0..).take_while(|&i| *ptr.add(i) != 0).count();
                        let slice = std::slice::from_raw_parts(ptr, len);
                        let string = String::from_utf16_lossy(slice);
                        println!("Clipboard updated.");
                        println!("Clipboard content: {}", string);
                        GlobalUnlock(handle);
                    }
                }
                CloseClipboard();
            }
            0
        }
        _ => DefWindowProcW(hwnd, msg, wparam, lparam),
    }
}

fn main() {
    unsafe {
        let hinst = GetModuleHandleW(ptr::null_mut());
        let wnd_class = WNDCLASSW {
            hInstance: hinst,
            lpfnWndProc: Some(window_proc),
            lpszClassName: to_wstring("ClipboardMessageWindow").as_ptr(),
            ..zeroed::<WNDCLASSW>()
        };
        if RegisterClassW(&wnd_class) == 0 {
            panic!("RegisterClassEx failed");
        }

        let hwnd = CreateWindowExW(
            0,
            wnd_class.lpszClassName,
            ptr::null(),
            0,
            0,
            0,
            0,
            0,
            HWND_MESSAGE,
            ptr::null_mut(),
            hinst,
            ptr::null_mut(),
        );
        if hwnd == ptr::null_mut() {
            panic!("CreateWindowEx failed");
        }

        let mut msg = std::mem::zeroed();
        loop {
            let res = GetMessageW(&mut msg, ptr::null_mut(), 0, 0);
            if res == 0 || res == -1 {
                break;
            }

            DispatchMessageW(&msg);
        }
    }
}
