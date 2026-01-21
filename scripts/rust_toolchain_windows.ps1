# 函数声明并定义：检查并切换到 Rust 工具链指定版本
function Set-RustToolchain {
    param(
        [Parameter(Mandatory=$true)]
        [string]$TargetVersion
    )

    # 检查当前Rust是否安装
    $rustcPath = Get-Command rustc -ErrorAction SilentlyContinue
    if (-not $rustcPath) {
        Write-Host "未检测到Rust安装，将直接安装 $TargetVersion 版本..." -ForegroundColor Yellow
        # 使用rustup安装指定版本
        rustup install stable-$TargetVersion
        rustup default stable-$TargetVersion
        return
    }

    # 获取当前Rust版本和目标平台信息
    $rustInfo = rustc -vV
    $currentTarget = ($rustInfo | Select-String "host:").ToString().Split(':')[1].Trim()

    Write-Host "当前Rust版本: $currentTarget" -ForegroundColor Cyan
    Write-Host "目标版本: $TargetVersion" -ForegroundColor Cyan

    # 如果当前已经是目标版本，无需操作
    if ($currentTarget -eq $TargetVersion) {
        Write-Host "当前已安装目标版本 $TargetVersion，无需更改。" -ForegroundColor Green
        return
    }

    Write-Host "检测到版本不一致，开始更新..." -ForegroundColor Yellow

    # 检查是否已安装rustup
    $rustupPath = Get-Command rustup -ErrorAction SilentlyContinue
    if (-not $rustupPath) {
        Write-Host "未检测到rustup，推荐使用rustup安装..." -ForegroundColor Yellow

        # 下载并安装rustup
        Write-Host "正在安装rustup..." -ForegroundColor Yellow
        Invoke-WebRequest -Uri "https://win.rustup.rs/x86_64" -OutFile "rustup-init.exe"
        Start-Process -FilePath ".\rustup-init.exe" -ArgumentList "-y" -Wait
        Remove-Item "rustup-init.exe" -Force

        # 刷新环境变量
        $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    }

    # 如果通过rustup安装，使用rustup切换版本
    if ($rustupPath) {
        Write-Host "使用rustup切换版本..." -ForegroundColor Yellow

        # 添加目标版本工具链
        rustup toolchain install stable-$TargetVersion

        # 设置为默认工具链
        rustup default stable-$TargetVersion

        Write-Host "已成功切换到 $TargetVersion 版本" -ForegroundColor Green
    }
    else {
        # 如果不是通过rustup安装，需要手动卸载并重新安装
        Write-Host "检测到独立安装的Rust，需要手动卸载..." -ForegroundColor Yellow
        Write-Host "请按以下步骤操作：" -ForegroundColor Yellow
        Write-Host "1. 在控制面板 -> 程序和功能中卸载Rust" -ForegroundColor Yellow
        Write-Host "2. 从 https://rustup.rs/ 下载rustup安装器" -ForegroundColor Yellow
        Write-Host "3. 运行 rustup-init.exe" -ForegroundColor Yellow
        Write-Host "4. 执行: rustup install stable-$TargetVersion" -ForegroundColor Yellow
        Write-Host "5. 执行: rustup default stable-$TargetVersion" -ForegroundColor Yellow
    }
}
