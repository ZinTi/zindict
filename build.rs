use chrono::Local;

fn main() {
    let now = Local::now();
    let formatted = now.format("%Y-%m-%d %H:%M:%S").to_string();
    let compiled_datetime = format!("Built: {}", formatted);
    let platform = std::env::var("TARGET").unwrap();

    println!("cargo:rustc-env=COMPILED_DATETIME={}", compiled_datetime);
    println!("cargo:rustc-env=PLATFORM={}", platform);

    println!("cargo:rustc-link-lib=static=binhub"); // 告诉链接器链接静态库 binhub
    println!("cargo:rustc-link-search=native=./lib"); // 设置库的搜索路径

    // 如果是 Windows 平台，可能需要链接额外的库
    #[cfg(windows)]
    {
        // Windows 控制台相关库
        println!("cargo:rustc-link-lib=dylib=kernel32");
        println!("cargo:rustc-link-lib=dylib=user32");
        println!("cargo:rustc-link-lib=dylib=advapi32");
    }
}
