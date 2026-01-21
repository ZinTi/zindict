// src/config/config.rs

use std::fmt::Debug;
use std::fs;
// use std::env;
use std::path::{Path, PathBuf};
use anyhow::{Context, Result};
use serde::{Deserialize, Serialize};

use crate::config::color_serde;
use crate::ffi::binhub::{binhub_ansi_color_t, binhub_tcolor_t};

const DEFAULT_MAIN_TABLE: &str = "iciba";
// const DEFAULT_HISTORY_PATH: &str = "../data/history.txt";
const DEFAULT_PROMPT_TEXT: &str = "Eng> ";

/// 1. [database] 数据库配置
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct DatabaseConf {
    pub path: String,
    pub main_table: String,
}

/// 2.1 [readline.history] 历史记录配置
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct HistoryConf {
    pub enable: bool,
    pub path: String,
    pub max_size: u32,
}

/// 2.2 [readline.autocomplete] 自动补全配置
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct AutocompleteConf {
    pub enable: bool,
    pub max_suggestions: u32,
}

/// 2. [readline] 行编辑器配置
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct ReadlineConf {
    pub history: HistoryConf,
    pub autocomplete: AutocompleteConf,
}

/// 3. [prompt] 提示符配置
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct PromptConf {
    #[serde(with = "color_serde::tcolor_serde")]
    pub color: binhub_tcolor_t,
    pub text: String,
}

/// 表头-表值 颜色对配置
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct ColumnColorPair {
    #[serde(with = "color_serde::tcolor_serde")]
    pub header: binhub_tcolor_t,
    #[serde(with = "color_serde::tcolor_serde")]
    pub value: binhub_tcolor_t,
}

/// 颜色配置
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct ThemeConf {
    pub enable: bool,
    #[serde(with = "color_serde::tcolor_serde")]
    pub word_echo: binhub_tcolor_t,
    #[serde(with = "color_serde::tcolor_serde")]
    pub error: binhub_tcolor_t,
    pub word_name: ColumnColorPair,
    pub ph_en: ColumnColorPair,
    pub ph_am: ColumnColorPair,
    pub means: ColumnColorPair,
}

/// 主配置结构
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Config {
    pub database: DatabaseConf,
    pub readline: ReadlineConf,
    pub prompt: PromptConf,
    pub theme: ThemeConf,
}

impl Default for Config {
    fn default() -> Self {

        // 获取模块所在目录绝对路径
        let data_path: String = get_module_dir_absolute().unwrap();
        let data_path: PathBuf = PathBuf::from(&data_path);
        let data_path: PathBuf = match data_path.parent() { // 匹配父目录
            Some(parent) => parent.join("data"),
            None => PathBuf::from("/data"), // 如果已经在根目录，使用根目录下的data
        };
        let db_path: String = data_path.join("dict.db").to_string_lossy().replace('\\', "/"); // 再次转换为字符串并确保使用正斜杠
        let history_path: String = data_path.join("history.txt").to_string_lossy().replace('\\', "/");

        Config {
            database: DatabaseConf {
                path: db_path,
                main_table: DEFAULT_MAIN_TABLE.to_string(),
            },
            readline: ReadlineConf {
                history: HistoryConf {
                    enable: true,
                    path: history_path,
                    max_size: 200,
                },
                autocomplete: AutocompleteConf {
                    enable: true,
                    max_suggestions: 10,
                },
            },
            prompt: PromptConf {
                color: binhub_tcolor_t {
                    fg: binhub_ansi_color_t::CLR_BRT_CYAN,
                    bg: binhub_ansi_color_t::CLR_NONE,
                },
                text: DEFAULT_PROMPT_TEXT.to_string(),
            },
            theme: ThemeConf {
                enable: true,
                word_echo: binhub_tcolor_t {
                    fg: binhub_ansi_color_t::CLR_BRT_GREEN,
                    bg: binhub_ansi_color_t::CLR_NONE,
                },
                error: binhub_tcolor_t {
                    fg: binhub_ansi_color_t::CLR_BRT_RED,
                    bg: binhub_ansi_color_t::CLR_NONE,
                },
                word_name: ColumnColorPair {
                    header: binhub_tcolor_t {
                        fg: binhub_ansi_color_t::CLR_BRT_MAGENTA,
                        bg: binhub_ansi_color_t::CLR_NONE,
                    },
                    value: binhub_tcolor_t {
                        fg: binhub_ansi_color_t::CLR_BLUE,
                        bg: binhub_ansi_color_t::CLR_BRT_YELLOW,
                    },
                },
                ph_en: ColumnColorPair {
                    header: binhub_tcolor_t {
                        fg: binhub_ansi_color_t::CLR_BRT_BLACK,
                        bg: binhub_ansi_color_t::CLR_NONE,
                    },
                    value: binhub_tcolor_t {
                        fg: binhub_ansi_color_t::CLR_WHITE,
                        bg: binhub_ansi_color_t::CLR_NONE,
                    },
                },
                ph_am: ColumnColorPair {
                    header: binhub_tcolor_t {
                        fg: binhub_ansi_color_t::CLR_BRT_BLACK,
                        bg: binhub_ansi_color_t::CLR_NONE,
                    },
                    value: binhub_tcolor_t {
                        fg: binhub_ansi_color_t::CLR_WHITE,
                        bg: binhub_ansi_color_t::CLR_NONE,
                    },
                },
                means: ColumnColorPair {
                    header: binhub_tcolor_t {
                        fg: binhub_ansi_color_t::CLR_BLUE,
                        bg: binhub_ansi_color_t::CLR_NONE,
                    },
                    value: binhub_tcolor_t {
                        fg: binhub_ansi_color_t::CLR_WHITE,
                        bg: binhub_ansi_color_t::CLR_NONE,
                    },
                },
            },
        }
    }
}

impl Config {
    /// 从配置文件读取配置
    pub fn load() -> Result<Self> {
        let config_path = get_config_path()?;

        // 如果配置文件不存在，创建默认配置
        if !config_path.exists() {
            println!("配置文件不存在，正在创建默认配置文件...");
            let default_config = Config::default();
            default_config.save(&config_path)?;
            println!("默认配置文件已创建: {:?}", config_path);
            return Ok(default_config);
        }

        // 读取并解析配置文件
        let config_content: String = fs::read_to_string(&config_path)
            .with_context(|| format!("无法读取配置文件: {:?}", config_path))?;

        let config: Config = toml::from_str(&config_content)
            .with_context(|| format!("配置文件格式错误: {:?}", config_path))?;

        Ok(config)
    }

    /// 保存配置到文件
    pub fn save(&self, path: &Path) -> Result<()> {
        let toml_content = toml::to_string_pretty(self)
            .context("序列化配置失败")?;

        // 确保目录存在
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent).context("创建配置目录失败")?;
        }

        fs::write(path, toml_content)
            .with_context(|| format!("写入配置文件失败: {:?}", path))?;

        Ok(())
    }

    /// 更新配置并保存
    pub fn update(&mut self) -> Result<()> {
        let config_path: PathBuf = get_config_path()?;
        self.save(&config_path)
    }
}

/// 模块公开的读取配置函数
pub fn read_config() -> Result<Config> {
    Config::load()
}

/// 获取当前模块所在目录
pub fn get_module_dir() -> Result<String, Box<dyn std::error::Error>> {
    // 获取当前可执行文件的路径
    let mut module_dir: PathBuf = std::env::current_exe().context("无法获取可执行文件路径")?;
    module_dir.pop();  // 移除可执行文件名，得到目录

    let mut module_dir: String = module_dir.to_string_lossy().to_string(); // 将路径转换为字符串，并统一使用正斜杠

    // 在 Windows 上，统一使用正斜杠
    #[cfg(target_os = "windows")]
    {
        module_dir = module_dir.replace('\\', "/");
    }

    Ok(module_dir)
}

/// 获取当前模块所在目录的绝对路径（与 get_module_dir 的区别主要在于 ①对符号链接的处理 和 ②是否可能返回相对路径）
// 使用 std::fs::canonicalize 获取绝对路径的版本
pub fn get_module_dir_absolute() -> Result<String, Box<dyn std::error::Error>> {
    let exe_path: PathBuf = std::env::current_exe()?;

    // 获取绝对路径
    let absolute_path: PathBuf = if exe_path.is_absolute() {
        exe_path
    } else {
        std::fs::canonicalize(exe_path)?
    };

    let module_dir: &Path = absolute_path.parent()
        .ok_or("无法获取所在目录")?;

    let mut module_dir: String = module_dir.to_string_lossy().to_string();

    // 统一使用正斜杠
    #[cfg(target_os = "windows")]
    {
        module_dir = module_dir.replace('\\', "/");
    }

    Ok(module_dir)
}

/// 获取可执行文件所在目录的配置文件路径
fn get_config_path() -> Result<PathBuf> {
    let mut exe_path: PathBuf = std::env::current_exe().context("无法获取可执行文件路径")?;

    exe_path.pop();  // 移除可执行文件名，得到目录

    let config_path: PathBuf = exe_path.join("zindict.toml"); // 构建配置文件路径

    Ok(config_path)
}
