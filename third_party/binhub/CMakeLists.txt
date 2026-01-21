cmake_minimum_required(VERSION 3.20)
project(BinHubLibrary VERSION 0.0.1 LANGUAGES C)

# 设置项目选项
option(BUILD_SHARED_LIBS "Build shared libraries" OFF) # 不生成动态库
option(BUILD_STATIC_LIBS "Build static libraries" ON)
option(BUILD_TESTING "Build tests" ON)

# 设置C标准
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 公共头文件列表
set(PUBLIC_HEADERS
        include/binhub.h
        include/binhub_io.h
        include/binhub_macro.h
        include/binhub_rgb.h
        include/binhub_sllc.h
        include/binhub_slls.h
        include/binhub_string.h
)

# 源文件列表
set(SOURCES
        src/binhub.c
        src/binhub_io.c
        src/binhub_rgb.c
        src/binhub_sllc.c
        src/binhub_slls.c
        src/binhub_string.c
)

# 构建静态库（如果启用）
if(BUILD_STATIC_LIBS)
    add_library(binhub_static STATIC ${SOURCES})
    set_target_properties(binhub_static PROPERTIES
            OUTPUT_NAME "binhub"
            VERSION ${PROJECT_VERSION}
            PUBLIC_HEADER "${PUBLIC_HEADERS}"
    )

    # 设置包含目录 - PUBLIC属性让依赖此目标的项目也能包含这些头文件
    target_include_directories(binhub_static PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # 任何链接到本库的其他目标都需要包含此目录
            $<INSTALL_INTERFACE:include>
    )

    # 添加别名以便统一使用
    add_library(binhub::static ALIAS binhub_static)

    # 安装静态库
    install(TARGETS binhub_static
            EXPORT binhub-targets
            ARCHIVE DESTINATION lib
            PUBLIC_HEADER DESTINATION include
    )
endif()

# 构建共享库（如果启用）
if(BUILD_SHARED_LIBS)
    add_library(binhub_shared SHARED ${SOURCES})
    set_target_properties(binhub_shared PROPERTIES
            OUTPUT_NAME "binhub"
            VERSION ${PROJECT_VERSION}
            SOVERSION 1
            PUBLIC_HEADER "${PUBLIC_HEADERS}"
    )

    # 设置包含目录 - PUBLIC属性让依赖此目标的项目也能包含这些头文件
    target_include_directories(binhub_shared PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # 任何链接到本库的其他目标都需要包含此目录
            $<INSTALL_INTERFACE:include>
    )

    # 添加别名以便统一使用
    add_library(binhub::shared ALIAS binhub_shared)

    # 安装共享库
    install(TARGETS binhub_shared
            EXPORT binhub-targets
            LIBRARY DESTINATION lib
            RUNTIME DESTINATION bin  # Windows上DLL文件放在bin目录
            PUBLIC_HEADER DESTINATION include
    )
endif()

# 导出目标供其他项目使用
install(EXPORT binhub-targets
        FILE binhub-config.cmake
        NAMESPACE binhub::
        DESTINATION lib/cmake/binhub
)

# 添加测试（如果启用）
if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_main.c")
    enable_testing()
    add_executable(test_binhub tests/test_main.c)

    # 优先链接共享库，如果存在的话
    if(BUILD_SHARED_LIBS)
        target_link_libraries(test_binhub binhub_shared)
    elseif(BUILD_STATIC_LIBS)
        target_link_libraries(test_binhub binhub_static)
    endif()

    add_test(NAME binhub_test COMMAND test_binhub)
endif()

# 添加示例程序（如果存在）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
    add_executable(libbinhub_example
            src/main.c
    )

    # 优先链接共享库，如果存在的话
    if(BUILD_SHARED_LIBS)
        target_link_libraries(libbinhub_example binhub_shared)
    elseif(BUILD_STATIC_LIBS)
        target_link_libraries(libbinhub_example binhub_static)
    endif()
endif()

# 安装公共头文件
install(FILES ${PUBLIC_HEADERS} DESTINATION include)