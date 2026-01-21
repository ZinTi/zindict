// src/config/about.rs

pub mod about {

    // Project information
    pub const NAME: &str = "ZinDict";
    pub const VERSION: &str = env!("CARGO_PKG_VERSION");
    pub const YEARS: &str = "2023-2026";
    pub const AUTHOR: &str = "ZENG Lai (Zin)";
    pub const COMPILED_DATETIME: &str = env!("COMPILED_DATETIME");
    pub const PLATFORM: &str = env!("PLATFORM");

    // 系统特定版本信息
    #[cfg(target_os = "windows")]
    pub const FULL_VERSION: &str = concat!(env!("CARGO_PKG_VERSION"), "-WinNT");

    #[cfg(target_os = "linux")]
    pub const FULL_VERSION: &str = concat!(env!("CARGO_PKG_VERSION"), "-GNU/Linux");

    #[cfg(target_os = "macos")]
    pub const FULL_VERSION: &str = concat!(env!("CARGO_PKG_VERSION"), "-macOS");

    #[cfg(not(any(target_os = "windows", target_os = "linux", target_os = "macos")))]
    pub const FULL_VERSION: &str = concat!(env!("CARGO_PKG_VERSION"), "-Unknown");

    pub const USER_MANUAL_ZH: &str = include_str!("../resources/manuals/user_manual_zh_CN.txt");
    pub const USER_MANUAL_EN: &str = include_str!("../resources/manuals/user_manual_en_US.txt");

    pub const USER_MANUAL: &str = concat!(
        include_str!("../resources/manuals/user_manual_zh_CN.txt"),
        "\n\n",
        include_str!("../resources/manuals/user_manual_en_US.txt")
    );

    /**
     * @brief 打印帮助文档，查找命令帮助
     */
    #[allow(unused_variables)]
    pub fn print_help(m_path: &str, target: &str) {
        if target.is_empty() {
            println!("{}", USER_MANUAL);
        } else {
            println!("To display how to use the \"{}\" commands.", target);
            println!("To be developed.");
        }
    }

    pub fn print_about() {
        println!("{} v{} ({}) | {}", NAME, VERSION, PLATFORM, COMPILED_DATETIME);
        println!("Copyright (c) {} {}. Licensed under the GPL.\n", YEARS, AUTHOR);
    }


}
