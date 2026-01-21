// src/dao/dict.rs

use rusqlite::{Connection, Result, params};
use std::path::Path;
// use crate::ffi::binhub::{binhub_ansi_color_t, binhub_tcolor_t};
use crate::{cprint};
use crate::config::config::{Config};

/// 显示查询结果的回调函数
pub fn show_result(row: &rusqlite::Row, headers: &[String], conf: &Config) -> Result<()> {
    // 遍历每一列
    for (i, header) in headers.iter().enumerate() {
        // 获取该列的值
        let value: Option<String> = row.get(i)?;
        let value_str = value.as_deref().unwrap_or("NULL");

        match i {
            0 => { // 单词
                cprint!(conf.theme.word_name.header, "{}: ", header); // 表头
                cprint!(conf.theme.word_name.value, "{}", value_str); // 值
                println!(); // 单独换行（避免换行符颜色错误）
            }
            1 => { // 英式发音(1)
                cprint!(conf.theme.ph_en.header, "{}: ", header); // 表头
                cprint!(conf.theme.ph_en.value, "{}", value_str); // 值
                println!();
            }
            2 => { // 美式发音(2)
                cprint!(conf.theme.ph_am.header, "{}: ", header); // 表头
                cprint!(conf.theme.ph_am.value, "{}", value_str); // 值
                println!();
            }
            3 => { // 词义
                cprint!(conf.theme.means.header, "{}: ", header); // 表头
                cprint!(conf.theme.means.value, "{}", value_str); // 值
                println!();
            }
            _ => { // 其他列
                cprint!(conf.theme.means.header, "{}: ", header); // 表头
                cprint!(conf.theme.means.value, "{}", value_str); // 值
                println!();
            }
        }
    }
    println!();
    Ok(())
}

/// 检查表是否存在
pub fn table_exists(conn: &Connection, table_name: &str) -> Result<bool> {
    let sql = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name = ?1";
    let exists: i64 = conn.query_row(sql, params![table_name], |row| row.get(0))?;
    Ok(exists > 0)
}

/// 查询单词函数，支持精确匹配和通配符
pub fn query_the_word(
    word: &str, 
    conf: &Config,
    exact_match: bool
) -> Result<()> {
    let conn = Connection::open(Path::new(&conf.database.path))?;

    // 检查表是否存在
    if !table_exists(&conn, &conf.database.main_table)? {
        eprintln!("错误: 表 '{}' 不存在", &conf.database.main_table);
        return Ok(());
    }

    cprint!(conf.theme.word_echo, "{}", word);
    println!();

    let sql = format!(
        r#"SELECT 
            word_name AS 词语, 
            ph_en AS 英音, 
            ph_am AS 美音, 
            means AS 释义 
        FROM {} 
        WHERE word_name LIKE ?1"#,
        &conf.database.main_table
    );

    let mut stmt = conn.prepare(&sql)?;
    let headers: Vec<String> = stmt.column_names()
        .into_iter()
        .map(|s| s.to_string())
        .collect();

    // 根据是否精确匹配构建查询参数
    let pattern = if exact_match {
        word.to_string()  // 精确匹配
    } else {
        format!("%{}%", word)  // 模糊匹配
    };

    let mut rows = stmt.query([&pattern])?;

    let mut found = false;
    while let Some(row) = rows.next()? {
        show_result(&row, &headers, &conf)?;
        found = true;
    }

    if !found {
        println!("无匹配: {}", word);
    }

    Ok(())
}

/// 使用更高级的API，支持多种查询方式
pub fn query_with_options(
    word: &str, 
    conf: &Config,
    pattern: &str,
    limit: Option<i32>
) -> Result<()> {
    let conn = Connection::open(Path::new(&conf.database.path))?;

    // 检查表是否存在
    if !table_exists(&conn, &conf.database.main_table)? {
        eprintln!("错误: 表 '{}' 不存在", &conf.database.main_table);
        return Ok(());
    }

    cprint!(conf.theme.word_echo, "查询: {}", word);
    println!();

    // 构建动态SQL
    let mut sql = format!(
        r#"SELECT 
            word_name AS 词语, 
            ph_en AS 英音, 
            ph_am AS 美音, 
            means AS 释义 
        FROM {} 
        WHERE word_name LIKE ?1"#,
        &conf.database.main_table
    );

    if let Some(limit) = limit {
        sql.push_str(&format!(" LIMIT {}", limit));
    }

    let mut stmt = conn.prepare(&sql)?;
    let headers: Vec<String> = stmt.column_names()
        .into_iter()
        .map(|s| s.to_string())
        .collect();

    let mut rows = stmt.query([pattern])?;

    let mut found = false;
    while let Some(row) = rows.next()? {
        show_result(&row, &headers, &conf)?;
        found = true;
    }

    if !found {
        println!("无匹配的单词");
    }

    Ok(())
}

/// 通用的查询函数，可以指定列名
pub fn query_with_columns(
    word: &str,
    conf: &Config,
    columns: &[(&str, &str)], // (列名, 别名)
) -> Result<()> {
    let conn = Connection::open(Path::new(&conf.database.path))?;

    // 检查表是否存在
    if !table_exists(&conn, &conf.database.main_table)? {
        eprintln!("错误: 表 '{}' 不存在", &conf.database.main_table);
        return Ok(());
    }

    // 构建列名部分
    let columns_str: Vec<String> = columns
        .iter()
        .map(|(col, alias)| {
            if col == alias {
                col.to_string()
            } else {
                format!("{} AS {}", col, alias)
            }
        })
        .collect();

    // 构建SQL查询
    let sql = format!(
        "SELECT {} FROM {} WHERE word_name LIKE ?1",
        columns_str.join(", "),
        &conf.database.main_table
    );

    let mut stmt = conn.prepare(&sql)?;
    let _headers: Vec<String> = columns
        .iter()
        .map(|(_, alias)| alias.to_string())
        .collect();

    let mut rows = stmt.query([format!("%{}%", word)])?;

    let mut found = false;
    while let Some(row) = rows.next()? {
        for (i, (_col, alias)) in columns.iter().enumerate() {
            let value: Option<String> = row.get(i)?;
            let value_str = value.as_deref().unwrap_or("NULL");

            // 简单颜色处理
            if *alias == "词语" || *alias == "单词" || *alias == "word" || *alias == "word_name" {
                cprint!(conf.theme.word_name.header, "{}: ", alias);
                cprint!(conf.theme.word_name.value, "{}", value_str);
                println!();
            } else if *alias == "释义" || *alias == "意思" || *alias == "meaning" || *alias == "means" {
                cprint!(conf.theme.means.header, "{}: ", alias);
                cprint!(conf.theme.means.value, "{}", value_str);
                println!();
            } else if *alias == "英音" || *alias == "英式音" || *alias == "英语音" || *alias == "英语发音" || *alias == "ph_en" {
                cprint!(conf.theme.ph_en.header, "{}: ", alias);
                cprint!(conf.theme.ph_en.value, "{}", value_str);
                println!();
            } else if *alias == "美音" || *alias == "美式音" || *alias == "美语音" || *alias == "美语发音" || *alias == "ph_am" {
                cprint!(conf.theme.ph_am.header, "{}: ", alias);
                cprint!(conf.theme.ph_am.value, "{}", value_str);
                println!();
            } else { // 其他列
                cprint!(conf.theme.means.header, "{}: ", alias); // 表头
                cprint!(conf.theme.means.value, "{}", value_str); // 值
                println!();
            }
        }
        println!();
        found = true;
    }

    if !found {
        println!("无匹配: {}", word);
    }

    Ok(())
}

/// 列出表中的所有单词
pub fn list_all_words(conf: &Config, limit: Option<usize>) -> Result<()> {
    let conn = Connection::open(Path::new(&conf.database.path))?;

    // 检查表是否存在
    if !table_exists(&conn, &conf.database.main_table)? {
        eprintln!("错误: 表 '{}' 不存在", &conf.database.main_table);
        return Ok(());
    }

    let mut sql = format!("SELECT word_name FROM {} ORDER BY word_name", &conf.database.main_table);
    if let Some(limit) = limit {
        sql.push_str(&format!(" LIMIT {}", limit));
    }

    let mut stmt = conn.prepare(&sql)?;
    let mut rows = stmt.query([])?;

    println!("表 '{}' 中的单词列表:", &conf.database.main_table);
    let mut count = 0;

    while let Some(row) = rows.next()? {
        let word: String = row.get(0)?;
        println!("{}. {}", count + 1, word);
        count += 1;
    }

    println!("\n总计: {} 个单词", count);

    Ok(())
}
