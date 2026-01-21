// src/config/color_serde.rs
use crate::ffi::binhub::binhub_ansi_color_t;
use serde::{Deserialize, Deserializer, Serializer};
use std::str::FromStr;

/// 颜色字符串到枚举值的映射
#[derive(Debug, Clone, Copy)]
pub struct ColorMapping;

// 实现 ColorMapping
impl ColorMapping {
    /// 将字符串转换为颜色枚举
    pub fn from_str(s: &str) -> Result<binhub_ansi_color_t, String> {
        match s.to_uppercase().as_str() {
            // 标准颜色
            "CLR_NONE" => Ok(binhub_ansi_color_t::CLR_NONE),
            "CLR_BLACK" => Ok(binhub_ansi_color_t::CLR_BLACK),
            "CLR_RED" => Ok(binhub_ansi_color_t::CLR_RED),
            "CLR_GREEN" => Ok(binhub_ansi_color_t::CLR_GREEN),
            "CLR_YELLOW" => Ok(binhub_ansi_color_t::CLR_YELLOW),
            "CLR_BLUE" => Ok(binhub_ansi_color_t::CLR_BLUE),
            "CLR_MAGENTA" => Ok(binhub_ansi_color_t::CLR_MAGENTA),
            "CLR_CYAN" => Ok(binhub_ansi_color_t::CLR_CYAN),
            "CLR_WHITE" => Ok(binhub_ansi_color_t::CLR_WHITE),
            "CLR_BRT_BLACK" => Ok(binhub_ansi_color_t::CLR_BRT_BLACK),
            "CLR_BRT_RED" => Ok(binhub_ansi_color_t::CLR_BRT_RED),
            "CLR_BRT_GREEN" => Ok(binhub_ansi_color_t::CLR_BRT_GREEN),
            "CLR_BRT_YELLOW" => Ok(binhub_ansi_color_t::CLR_BRT_YELLOW),
            "CLR_BRT_BLUE" => Ok(binhub_ansi_color_t::CLR_BRT_BLUE),
            "CLR_BRT_MAGENTA" => Ok(binhub_ansi_color_t::CLR_BRT_MAGENTA),
            "CLR_BRT_CYAN" => Ok(binhub_ansi_color_t::CLR_BRT_CYAN),
            "CLR_BRT_WHITE" => Ok(binhub_ansi_color_t::CLR_BRT_WHITE),
            "CLR_RESET" => Ok(binhub_ansi_color_t::CLR_RESET),

            // 别名映射
            "CLR_GRAY" => Ok(binhub_ansi_color_t::CLR_BRT_BLACK),
            "GRAY" => Ok(binhub_ansi_color_t::CLR_BRT_BLACK),
            "GREY" => Ok(binhub_ansi_color_t::CLR_BRT_BLACK),

            // 简写形式（可选）
            "BLACK" => Ok(binhub_ansi_color_t::CLR_BLACK),
            "RED" => Ok(binhub_ansi_color_t::CLR_RED),
            "GREEN" => Ok(binhub_ansi_color_t::CLR_GREEN),
            "YELLOW" => Ok(binhub_ansi_color_t::CLR_YELLOW),
            "BLUE" => Ok(binhub_ansi_color_t::CLR_BLUE),
            "MAGENTA" => Ok(binhub_ansi_color_t::CLR_MAGENTA),
            "PURPLE" => Ok(binhub_ansi_color_t::CLR_MAGENTA),
            "CYAN" => Ok(binhub_ansi_color_t::CLR_CYAN),
            "WHITE" => Ok(binhub_ansi_color_t::CLR_WHITE),

            // 未识别的颜色
            _ => Err(format!("未知的颜色字符串: {}", s)),
        }
    }

    /// 将颜色枚举转换为字符串
    pub fn to_string(color: binhub_ansi_color_t) -> String {
        match color {
            binhub_ansi_color_t::CLR_NONE => "CLR_NONE",
            binhub_ansi_color_t::CLR_BLACK => "CLR_BLACK",
            binhub_ansi_color_t::CLR_RED => "CLR_RED",
            binhub_ansi_color_t::CLR_GREEN => "CLR_GREEN",
            binhub_ansi_color_t::CLR_YELLOW => "CLR_YELLOW",
            binhub_ansi_color_t::CLR_BLUE => "CLR_BLUE",
            binhub_ansi_color_t::CLR_MAGENTA => "CLR_MAGENTA",
            binhub_ansi_color_t::CLR_CYAN => "CLR_CYAN",
            binhub_ansi_color_t::CLR_WHITE => "CLR_WHITE",
            binhub_ansi_color_t::CLR_BRT_BLACK => "CLR_GRAY", // 使用别名保存
            binhub_ansi_color_t::CLR_BRT_RED => "CLR_BRT_RED",
            binhub_ansi_color_t::CLR_BRT_GREEN => "CLR_BRT_GREEN",
            binhub_ansi_color_t::CLR_BRT_YELLOW => "CLR_BRT_YELLOW",
            binhub_ansi_color_t::CLR_BRT_BLUE => "CLR_BRT_BLUE",
            binhub_ansi_color_t::CLR_BRT_MAGENTA => "CLR_BRT_MAGENTA",
            binhub_ansi_color_t::CLR_BRT_CYAN => "CLR_BRT_CYAN",
            binhub_ansi_color_t::CLR_BRT_WHITE => "CLR_BRT_WHITE",
            binhub_ansi_color_t::CLR_RESET => "CLR_RESET",
        }
        .to_string()
    }
}

// 为 binhub_ansi_color_t 实现 FromStr trait
impl FromStr for binhub_ansi_color_t {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        ColorMapping::from_str(s)
    }
}

/// 为 binhub_ansi_color_t 实现自定义序列化
pub mod ansi_color_serde {
    use super::*;

    pub fn serialize<S>(
        color: &binhub_ansi_color_t,
        serializer: S,
    ) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let color_str = ColorMapping::to_string(*color);
        serializer.serialize_str(&color_str)
    }

    pub fn deserialize<'de, D>(
        deserializer: D,
    ) -> Result<binhub_ansi_color_t, D::Error>
    where
        D: Deserializer<'de>,
    {
        let s = String::deserialize(deserializer)?;
        ColorMapping::from_str(&s).map_err(serde::de::Error::custom)
    }
}

/// 为 binhub_tcolor_t 实现自定义序列化
pub mod tcolor_serde {
    use crate::ffi::binhub::binhub_tcolor_t;
    use super::ansi_color_serde;
    use serde::{Deserialize, Deserializer, Serialize, Serializer};

    #[derive(Serialize, Deserialize)]
    struct TColorHelper {
        #[serde(with = "ansi_color_serde")]
        fg: crate::ffi::binhub::binhub_ansi_color_t,
        #[serde(with = "ansi_color_serde")]
        bg: crate::ffi::binhub::binhub_ansi_color_t,
    }

    pub fn serialize<S>(
        color: &binhub_tcolor_t,
        serializer: S,
    ) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let helper = TColorHelper {
            fg: color.fg,
            bg: color.bg,
        };
        helper.serialize(serializer)
    }

    pub fn deserialize<'de, D>(
        deserializer: D,
    ) -> Result<binhub_tcolor_t, D::Error>
    where
        D: Deserializer<'de>,
    {
        let helper = TColorHelper::deserialize(deserializer)?;
        Ok(binhub_tcolor_t {
            fg: helper.fg,
            bg: helper.bg,
        })
    }
}
