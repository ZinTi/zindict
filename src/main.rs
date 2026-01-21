// src/main.rs

use zindict::App;
use zindict::ffi::binhub::{binhub_console_encoding_t};
use zindict::ffi::binhub::safe;  // 导入 safe 模块

fn main() {

    // 设置控制台编码为UTF-8
    safe::setenc(binhub_console_encoding_t::ENCODING_UTF8).unwrap();

    // 获取命令行参数
    let args: Vec<String> = std::env::args().collect();

    let mut app: App = App::new();

    if args.len() > 1 {
        for i in 1..args.len() {
            app.request_word(&args[i]);
        }

    } else {
        app.run();
    }



}
