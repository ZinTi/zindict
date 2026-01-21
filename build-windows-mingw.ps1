# 1. Build dependencies
cmake -S . -B "target/cmake_build" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build "target/cmake_build" --parallel ${env:NUMBER_OF_PROCESSORS}
Remove-Item ".\zindict-v*\bin\*" -Force # binhub example

# 2. Build project
cargo build --release

# 3. Move executable to target directory
Write-Output "=== Copying file to target directory... ==="
$targetDir = Get-ChildItem -Directory -Filter "zindict-v*" | Select-Object -First 1 # 先找到目标目录
if ($targetDir) {
    # 确保bin目录存在
    $binDir = Join-Path $targetDir.FullName "bin"
    if (-not (Test-Path $binDir)) {
        New-Item -ItemType Directory -Path $binDir -Force
    }

    # 移动文件到bin目录
    Move-Item -Path ".\target\release\*.exe" -Destination $binDir -ErrorAction SilentlyContinue
    Move-Item -Path ".\target\release\*.rlib" -Destination $binDir -ErrorAction SilentlyContinue

    # 复制其他文件
    if (Test-Path ".\data\") {
        Copy-Item -Path ".\data\" -Destination $targetDir.FullName -Recurse
    }

    if (Test-Path ".\docs\") {
        Copy-Item -Path ".\docs\" -Destination $targetDir.FullName -Recurse
    }

    Copy-Item -Path ".\LICENSE" -Destination $targetDir.FullName -ErrorAction SilentlyContinue
    Copy-Item -Path ".\README.md" -Destination $targetDir.FullName -ErrorAction SilentlyContinue

    Write-Output "Files copied to: $($targetDir.FullName)"
} else {
    Write-Error "Target directory not found! No directory matches pattern 'zindict-v*'"
}
