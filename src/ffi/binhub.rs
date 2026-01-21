// src/ffi/binhub.rs

//! FFI bindings for binhub_io C library
#![allow(non_camel_case_types)]

use libc::{c_int, c_char};

// 定义颜色枚举
#[repr(C)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum binhub_ansi_color_t {
    CLR_NONE = -1,
    CLR_BLACK = 0,
    CLR_RED = 1,
    CLR_GREEN = 2,
    CLR_YELLOW = 3,
    CLR_BLUE = 4,
    CLR_MAGENTA = 5,
    CLR_CYAN = 6,
    CLR_WHITE = 7,
    CLR_BRT_BLACK = 8,
    CLR_BRT_RED = 9,
    CLR_BRT_GREEN = 10,
    CLR_BRT_YELLOW = 11,
    CLR_BRT_BLUE = 12,
    CLR_BRT_MAGENTA = 13,
    CLR_BRT_CYAN = 14,
    CLR_BRT_WHITE = 15,
    CLR_RESET = 16,
}

// 灰色别名
pub const CLR_GRAY: binhub_ansi_color_t = binhub_ansi_color_t::CLR_BRT_BLACK;

// 文本颜色结构体
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct binhub_tcolor_t {
    pub fg: binhub_ansi_color_t,
    pub bg: binhub_ansi_color_t,
}

// 定义编码类型枚举
#[repr(C)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum binhub_console_encoding_t {
    ENCODING_GBK = 0,
    ENCODING_UTF8 = 1,
}

// 颜色初始化宏的Rust版本
#[macro_export]
macro_rules! BINHUB_COLOR_INIT {
    ($fg:expr, $bg:expr) => {
        binhub_tcolor_t { fg: $fg, bg: $bg }
    };
}

// 函数声明
unsafe extern "C" {
    // binhub库函数

    /**
     * @brief 彩色格式化打印函数
     * @param color 颜色
     * @param format 字符串格式
     * @param ... 其他变量
     * @return int 如果成功，则返回写入的字符总数，否则返回一个负数
     */
    pub fn binhub_cprintf(color: binhub_tcolor_t, format: *const c_char, ...) -> c_int;

    /**
     * @brief 打印系统错误信息到 stderr (colorful perror)
     * @param str 错误信息
     */
    pub fn binhub_cperror(str: *const c_char);

    /**
     * @brief 输出自定义错误信息(custom/colorful error)
     * @param format 格式化字符串
     * @param ... 可变参数列表
     */
    pub fn binhub_cerr(format: *const c_char, ...);

    /**
     * @brief 输出自定义致命错误信息并终止程序（custom/colorful error - fatal）
     * @param format 格式化字符串
     * @param ... 可变参数列表
     */
    pub fn binhub_cerr_f(format: *const c_char, ...);

    /**
     * @brief 输出自定义警告信息（custom/colorful warn）
     * @param format 格式化字符串
     * @param ... 可变参数列表
     */
    pub fn binhub_cwarn(format: *const c_char, ...);

    /**
     * @brief 修改命令行颜色
     * @param color 颜色
     */
    pub fn binhub_chcolor(color: binhub_tcolor_t);

    /**
     * @brief win32 控制台颜色属性映射为 binhub_tcolor_t 类型
     * @param win32_color_attr win32 颜色属性
     */
    pub fn binhub_win_attr_to_tcolor(win32_color_attr: u8) -> binhub_tcolor_t;

    /**
     * @brief 设置控制台编码
     * @param encoding 编码类型：ENCODING_GBK 或 ENCODING_UTF8
     * @return int 成功返回0，失败返回非0错误码
     */
    pub fn binhub_setenc(encoding: binhub_console_encoding_t) -> c_int;

    /**
     * @brief 猜测数据的字符集编码是否为 UTF-8 格式
     * @param data 判断目标
     * @param len 数据长度
     * @return 如果返回值为 true 代表可能是 UTF-8
     */
    pub fn is_data_utf8(data: *const c_char, len: c_int) -> bool;

    /**
     * @brief 根据目标源文件自动选择活动代码页 CodePage
     * @param filename 目标文件名
     * @return 成功返回0，失败返回非0错误码
     */
    pub fn binhub_setcp_auto(filename: *const c_char) -> c_int;

    /**
     * @brief 进度条动画-转圈
     * @param text 文本提示
     * @param style 风格
     */
    pub fn load_loop(text: *const c_char, style: c_int);

    /**
     * @brief 清屏（包括可视区域 viewport，和滚动缓冲区 scrollback buffer）
     * @return bool 成功返回true，失败返回false
     * @details Windows 平台下使用原生 API 函数
     */
    pub fn binhub_clear_screen() -> bool;
}

// 安全的Rust包装函数
pub mod safe {
    use super::*;
    use std::ffi::CString;
    use std::process;

    /// 安全的彩色打印函数（仅支持无参数格式）
    pub fn cprintf(color: binhub_tcolor_t, text: &str) -> std::io::Result<i32> {
        let c_text = CString::new(text).map_err(|_| std::io::Error::new(
            std::io::ErrorKind::InvalidData, "字符串包含空字符"
        ))?;

        unsafe {
            let result = binhub_cprintf(color, c_text.as_ptr());
            if result >= 0 {
                Ok(result)
            } else {
                Err(std::io::Error::last_os_error())
            }
        }
    }

    /// 打印系统错误信息
    pub fn cperror(msg: &str) {
        let c_msg = CString::new(msg).unwrap_or_else(|_| CString::new("").unwrap());
        unsafe {
            binhub_cperror(c_msg.as_ptr());
        }
    }

    /// 输出自定义错误信息
    pub fn cerr(text: &str) {
        let c_text = CString::new(text).unwrap_or_else(|_| CString::new("").unwrap());
        unsafe {
            binhub_cerr(c_text.as_ptr());
        }
    }

    /// 输出致命错误并终止程序
    pub fn cerr_f(text: &str) -> ! {
        let c_text = CString::new(text).unwrap_or_else(|_| CString::new("").unwrap());
        unsafe {
            binhub_cerr_f(c_text.as_ptr());
        }
        process::exit(1);
    }

    /// 输出自定义警告信息
    pub fn cwarn(text: &str) {
        let c_text = CString::new(text).unwrap_or_else(|_| CString::new("").unwrap());
        unsafe {
            binhub_cwarn(c_text.as_ptr());
        }
    }

    /// 修改命令行颜色
    pub fn chcolor(color: binhub_tcolor_t) {
        unsafe {
            binhub_chcolor(color);
        }
    }

    /// 设置控制台编码
    pub fn setenc(encoding: binhub_console_encoding_t) -> std::io::Result<()> {
        unsafe {
            let result = binhub_setenc(encoding);
            if result == 0 {
                Ok(())
            } else {
                Err(std::io::Error::from_raw_os_error(result))
            }
        }
    }

    /// 猜测数据是否为UTF-8编码
    pub fn is_utf8(data: &[u8]) -> bool {
        let ptr = data.as_ptr() as *const c_char;
        let len = data.len() as c_int;
        unsafe {
            is_data_utf8(ptr, len)
        }
    }

    /// 自动设置代码页
    pub fn setcp_auto(filename: &str) -> std::io::Result<()> {
        let c_filename = CString::new(filename).map_err(|_| std::io::Error::new(
            std::io::ErrorKind::InvalidData, "文件名包含空字符"
        ))?;

        unsafe {
            let result = binhub_setcp_auto(c_filename.as_ptr());
            if result == 0 {
                Ok(())
            } else {
                Err(std::io::Error::from_raw_os_error(result))
            }
        }
    }

    /// 显示加载动画
    pub fn load_loop_animation(text: &str, style: i32) {
        let c_text = CString::new(text).unwrap_or_else(|_| CString::new("").unwrap());
        unsafe {
            load_loop(c_text.as_ptr(), style);
        }
    }

    pub fn clear_screen() -> bool {
        unsafe {
            binhub_clear_screen()
        }
    }

    /// 创建颜色结构
    pub fn make_color(fg: binhub_ansi_color_t, bg: binhub_ansi_color_t) -> binhub_tcolor_t {
        binhub_tcolor_t { fg, bg }
    }

    /// 重置颜色
    pub fn reset_color() {
        let color = binhub_tcolor_t {
            fg: binhub_ansi_color_t::CLR_RESET,
            bg: binhub_ansi_color_t::CLR_RESET,
        };
        unsafe {
            binhub_chcolor(color);
        }
    }
}

// 预定义颜色常量
pub mod colors {
    use super::*;

    pub const RED: binhub_tcolor_t = binhub_tcolor_t {
        fg: binhub_ansi_color_t::CLR_RED,
        bg: binhub_ansi_color_t::CLR_NONE,
    };

    pub const ERROR: binhub_tcolor_t = RED;

    pub const WARNING: binhub_tcolor_t = binhub_tcolor_t {
        fg: binhub_ansi_color_t::CLR_YELLOW,
        bg: binhub_ansi_color_t::CLR_NONE,
    };

    pub const SUCCESS: binhub_tcolor_t = binhub_tcolor_t {
        fg: binhub_ansi_color_t::CLR_GREEN,
        bg: binhub_ansi_color_t::CLR_NONE,
    };

    pub const INFO: binhub_tcolor_t = binhub_tcolor_t {
        fg: binhub_ansi_color_t::CLR_BLUE,
        bg: binhub_ansi_color_t::CLR_NONE,
    };

    pub const DEBUG: binhub_tcolor_t = binhub_tcolor_t {
        fg: binhub_ansi_color_t::CLR_MAGENTA,
        bg: binhub_ansi_color_t::CLR_NONE,
    };
}

// 方便的使用宏
#[macro_export]
macro_rules! cprint {
    ($color:expr, $($arg:tt)*) => {{
        use $crate::ffi::binhub::safe;
        let text = format!($($arg)*);
        let _ = safe::cprintf($color, &text);
    }};
}

#[macro_export]
macro_rules! cprintln {
    ($color:expr, $($arg:tt)*) => {{
        use $crate::ffi::binhub::safe;
        let text = format!($($arg)*);
        let _ = safe::cprintf($color, &format!("{}\n", text));
    }};
}

#[macro_export]
macro_rules! error {
    ($($arg:tt)*) => {{
        use $crate::ffi::binhub::safe;
        let text = format!($($arg)*);
        safe::cerr(&text);
    }};
}

#[macro_export]
macro_rules! error_f {
    ($($arg:tt)*) => {{
        use $crate::ffi::binhub::safe;
        let text = format!($($arg)*);
        safe::cerr_f(&text);
    }};
}

#[macro_export]
macro_rules! warn {
    ($($arg:tt)*) => {{
        use $crate::ffi::binhub::safe;
        let text = format!($($arg)*);
        safe::cwarn(&text);
    }};
}
