@echo off
setlocal

    @REM ================= golobal variables =================
    set dir_script=%~dp0
    set pkg_name_sqlite="sqlite-amalgamation-3510100"
    :: set pkg_name_readline="readline-8.3"
    set dir_sqlite="%dir_script%\third_party\%pkg_name_sqlite%"
    :: set dir_readline="%dir_script%\third_party\%pkg_name_readline%"

    @REM ================= main program =================
    call :main %*
    if %errorlevel% neq 0 (
        echo "Failed to execute script, error code: %errorlevel%"
    ) else (
        echo "Fetching dependencies done."
    )
    exit /b %errorlevel%

    @REM ================= label(func) definition =================
    :main
        @REM check if the directory (sqlite) exists.
        call :label_check_dir_exists "%dir_sqlite%"
        set error1=%errorlevel%
        if %error1% neq 0 (
            echo "Fetching sqlite to: %dir_sqlite%"
            call :label_fetch_sqlite
        )

        @REM check if the directory (readline) exists.
        @REM call :label_check_dir_exists "%dir_readline%"
        @REM set error2=%errorlevel%
        @REM if %error2% neq 0 (
        @REM     echo "Fetching readline to: %dir_readline%"
        @REM     call :label_fetch_readline
        @REM )

        exit /b 0

    :fetch_sqlite
        curl -k -L https://sqlite.org/2025/%pkg_name_sqlite%.zip -O
        unzip "%pkg_name_sqlite%.zip" -d third_party
        :: Note: The target path is relative to the link's directory, not the current working directory.
        :: MKLINK /D Link Target
        mklink /D "third_party\sqlite" %pkg_name_sqlite%
        exit /b

    @REM :fetch_readline
    @REM     curl -k -L ftp://ftp.gnu.org/gnu/readline/%pkg_name_readline%.tar.gz -O
    @REM     tar -zxf %pkg_name_readline%.tar.gz -C third_party
    @REM     mklink /D third_party\readline %pkg_name_readline%
    @REM     exit /b


    @REM ====================================================
    @REM @brief: label_check_dir_exists
    @REM purpose: check if a directory exists.
    @REM parameter: %1 - the directory path to check.
    @REM return: ERRORLEVEL: 0-directory exists, 1-directory does not exist.
    @REM example: call :label_check_dir_exists "C:\Windows"
    @REM ====================================================
    :label_check_dir_exists
        setlocal
        if "%~1"=="" (
            echo error: missing directory path.
            endlocal
            exit /b 2
        )

        @REM check if the directory exists.
        if exist "%~1\" (
            @REM the directory exists.
            endlocal
            exit /b 0
        ) else (
            @REM the directory does not exist.
            endlocal
            exit /b 1
        )



endlocal
