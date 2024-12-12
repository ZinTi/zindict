cmake_minimum_required(VERSION 3.12)
project(ZinDict LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置目标平台子目录
if(WIN32)
    set(THIRD_PARTY_PLATFORM "windows_x86_64")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")  # MinGW-w64 静态库后缀
elseif(UNIX AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(THIRD_PARTY_PLATFORM "linux_x86_64")
endif()

# SQLite3 静态库路径
set(SQLite3_LIBRARIES
        ${CMAKE_SOURCE_DIR}/third_party/sqlite-3.50.0/lib/${THIRD_PARTY_PLATFORM}
)

# 生成可执行文件
add_executable(dict
        src/main.c
        src/about.c
        src/color.c
        src/str.c
)

# 包含项目头文件和第三方库头文件
target_include_directories(dict PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/third_party/sqlite-3.50.0/include
)

# 链接静态库
target_link_directories(dict
        PUBLIC ${SQLite3_LIBRARIES}
)
target_link_libraries(dict
        PRIVATE sqlite3                     # libsqlite3.a
)
