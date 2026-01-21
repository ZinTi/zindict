#!/usr/bin/env bash

readonly dir_script="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly pkg_name_sqlite="sqlite-amalgamation-3510100"
# readonly pkg_name_readline="readline-8.3"
readonly dir_sqlite="${dir_script}/third_party/${pkg_name_sqlite}"
# readonly dir_readline="${dir_script}/third_party/${pkg_name_readline}"

######################################
# @brief Fetch sqlite library
######################################
function fn_fetch_sqlite {
    curl -k -L https://sqlite.org/2025/${pkg_name_sqlite}.zip -O
    unzip "${pkg_name_sqlite}.zip" -d third_party
    local link_path="third_party/sqlite"
    if [ -L "$link_path" ]; then
        unlink "$link_path"
    elif [ -d "$link_path" ]; then
        rm -rf "$link_path"
    fi
    # Note: The target path is relative to the link's directory, not the current working directory.
    # ln -s TARGET DIRECTORY
    ln -s "${pkg_name_sqlite}" "${link_path}"
}
######################################
# @brief Fetch readline library
######################################
# function fn_fetch_readline {
#     curl -k -L ftp://ftp.gnu.org/gnu/readline/${pkg_name_readline}.tar.gz -O
#     tar -zxf "${pkg_name_readline}.tar.gz" -C third_party
#     local link_path="third_party/readline"
#     if [ -L "$link_path" ]; then
#         unlink "$link_path"
#     elif [ -d "$link_path" ]; then
#         rm -rf "$link_path"
#     fi
#     ln -s "${pkg_name_readline}" "${link_path}"
# }

######################################
# @brief Check if directory exists
######################################
function fn_check_dir_exists() {
    local target_dir = "$1"

    if [ -d "$target_dir" ]; then
        if [[ "$target_dir" != /* ]]; then # if target_dir is not an absolute path
            target_dir="$(pwd)/$target_dir"
        fi
        echo "$target_dir"
        return 0
    else
        return 1
    fi
}

fn_check_dir_exists "$dir_sqlite"
if [ $? -eq 0 ]; then
    echo "Directory already exists: $dir_sqlite"
else
    echo "Fetching sqlite to: $dir_sqlite"
    fn_fetch_sqlite
fi
# fn_check_dir_exists "$dir_readline"
# if [ $? -eq 0 ]; then
#     echo "Directory already exists: $dir_readline"
# else
#     echo "Fetching readline to: $dir_readline"
#     fn_fetch_readline
# fi

echo "Fecthing dependencies Done."
