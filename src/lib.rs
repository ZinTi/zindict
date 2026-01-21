// src/lib.rs

// 1. pub mod 允许外部代码使用以下模块
pub mod config; // src/config/mod.rs
pub mod dao; // src/dao/mod.rs
pub mod ffi; // src/ffi/mod.rs

// 2. use 起别名，pub use 导出别名

use std::io::{self, Write};

// use crate::ffi::binhub::{safe, colors};
// pub use crate::ffi::binhub::{binhub_tcolor_t, binhub_ansi_color_t, colors};
use crate::{config::config::PromptConf, ffi::binhub::safe::clear_screen};

pub struct App {
    conf: config::config::Config,
    hint: String,
    prompt: PromptConf,

}

impl App {
    pub fn new() -> Self {
        // 1. 加载配置（若不存在会自动创建默认配置）
        let conf = config::config::Config::load().expect("Failed to load config");

        // 2. 复制一份 prompt
        let prompt = conf.prompt.clone();

        // 3. 初始化 App 实例
        App {
            // 3.1 转移所有权
            conf: conf,
            prompt: prompt,

            // 3.2 初始化提示语
            hint: "Type \".help\" for usage hints.".to_string(),

        }
    }

    pub fn reload_config(&mut self) {
        self.conf = config::config::Config::load().expect("Failed to load config");
    }

    pub fn run(&mut self) {
        // 1. 打印 about 信息和提示
        config::about::about::print_about();
        println!("{}\n", self.hint);

        // 2. 运行 REPL
        loop {
            // 打印提示符
            cprint!(self.prompt.color, "{}", self.prompt.text);
            io::stdout().flush().unwrap();

            let mut your_word: String = String::new();
            if io::stdin().read_line(&mut your_word).is_ok() {
                your_word = your_word.trim_end_matches(['\n', '\r']).to_string(); // 去除换行符

                if let Some(first_char) = your_word.chars().next() {
                    match first_char {
                        '.' | ':' => { // 1. 以 . 或 : 开头的命令
                            let cmd_part = &your_word[1..];
                            
                            // 使用Rust的方式忽略大小写比较
                            if ["exit", "quit", "e", "q"].iter()
                                .any(|&cmd| cmd_part.eq_ignore_ascii_case(cmd)) {
                                cprint!(self.prompt.color, "Bye!");
                                break;
                            } else if ["clear", "cls"].iter()
                                .any(|&cmd| cmd_part.eq_ignore_ascii_case(cmd)) {
                                if false == clear_screen() { // 清屏
                                    cprintln!(self.conf.theme.error, "Failed to clear screen!");
                                }
                                continue;
                            } else if ["help", "manual"].iter()
                                .any(|&cmd| cmd_part.eq_ignore_ascii_case(cmd)) {
                                config::about::about::print_help("hello", "");
                                continue;
                            } else if cmd_part.len() >= 6 && cmd_part[..6].eq_ignore_ascii_case("prompt") {
                                if your_word.len() == 7 { // .prompt 长度为7
                                    self.prompt.text = self.conf.prompt.text.clone(); // 回到默认提示符
                                    println!("Returning to default PROMPT of {}", self.prompt.text);
                                } else {
                                    self.prompt.text = your_word[8..].to_string(); // 跳过 .prompt 和空格
                                    println!("PROMPT set to '{}'", self.prompt.text);
                                }
                                continue;
                            } else {
                                cprintln!(self.conf.theme.error, "Invalid command!");
                            }
                        }
                        '?' => { // 2. 以 ? 开头的帮助命令
                            // 查询命令
                            config::about::about::print_help("hello", &your_word);
                            continue;
                        }
                        _ => { // 3. 普通查询
                            match dao::dict::query_the_word(&your_word, &self.conf, true) {
                                Ok(_) => {
                                    cprint!(self.conf.prompt.color, "Done.");
                                    println!("\n");
                                },
                                Err(e) => {
                                    eprintln!("Error: {}", e);
                                },
                            };
                        }
                    }
                }
            }
        }

    }

    pub fn request_word(&self, word: &str) {
        match dao::dict::query_the_word(&word, &self.conf, true) {
            Ok(_) => {
                cprint!(self.conf.prompt.color, "Done.");
                println!("\n");
            },
            Err(e) => {
                eprintln!("Error: {}", e);
            },
        };

    }

}
