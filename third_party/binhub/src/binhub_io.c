#include "binhub_io.h"

// 定义打印函数
int binhub_cprintf(binhub_tcolor_t color, const char* format, ...) {
#ifdef _WIN32
    // Windows 平台
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD original_attrs;

    // 获取原始控制台属性
    GetConsoleScreenBufferInfo(h_console, &consoleInfo);
    original_attrs = consoleInfo.wAttributes;

    // 定义颜色代码
    WORD fg_color_map[] = {
        0,     // 黑色
        0x4,   // 红色
        0x2,   // 绿色
        0x6,   // 黄色
        0x1,   // 蓝色
        0x5,   // 品红
        0x3,   // 青色
        0x7,   // 白色
        0x8,   // 明亮黑色
        0xC,   // 明亮红色
        0xA,   // 明亮绿色
        0xE,   // 明亮黄色
        0x9,   // 明亮蓝色
        0xD,   // 明亮品红
        0xB,   // 明亮青色
        0xF    // 明亮白色
    };

    WORD bg_color_map[] = {
        0,      // 黑色
        0x40,   // 红色
        0x20,   // 绿色
        0x60,   // 黄色
        0x10,    // 蓝色
        0x50,    // 品红
        0x30,    // 青色
        0x70,    // 白色
        0x80,    // 明亮黑色
        0xC0,    // 明亮红色
        0xA0,    // 明亮绿色
        0xE0,    // 明亮黄色
        0x90,    // 明亮蓝色
        0xD0,    // 明亮品红
        0xB0,    // 明亮青色
        0xF0     // 明亮白色
    };

    // 获取当前背景色部分
    WORD current_bg = original_attrs & 0xF0; // 高4位是背景色
    WORD new_attrs = fg_color_map[color.fg];

    // 设置背景色
    if(color.bg != CLR_NONE){
        new_attrs |= bg_color_map[color.bg];
    }else {
        new_attrs |= current_bg; // 保留当前背景色
    }

    // 设置颜色
    //SetConsoleTextAttribute(h_console, fg_color_map[color.fg] | bg_color_map[color.bg]);
    SetConsoleTextAttribute(h_console, new_attrs);

    // 打印内容
    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);

    // 恢复原始属性
    SetConsoleTextAttribute(h_console, original_attrs);
#else
    // Linux 平台
    const char* fg_color_map[] = {
        "\033[30m", // 黑色
        "\033[31m", // 红色
        "\033[32m", // 绿色
        "\033[33m", // 黄色
        "\033[34m", // 蓝色
        "\033[35m", // 品红
        "\033[36m", // 青色
        "\033[37m", // 白色
        "\033[90m", // 明亮黑色
        "\033[91m", // 明亮红色
        "\033[92m", // 明亮绿色
        "\033[93m", // 明亮黄色
        "\033[94m", // 明亮蓝色
        "\033[95m", // 明亮品红
        "\033[96m", // 明亮青色
        "\033[97m", // 明亮白色
        "\033[0m"   // 重置
    };

    const char* bg_color_map[] = {
        "\033[40m", // 黑色
        "\033[41m", // 红色
        "\033[42m", // 绿色
        "\033[43m", // 黄色
        "\033[44m", // 蓝色
        "\033[45m", // 品红
        "\033[46m", // 青色
        "\033[47m", // 白色
        "\033[100m", // 明亮黑色
        "\033[101m", // 明亮红色
        "\033[102m", // 明亮绿色
        "\033[103m", // 明亮黄色
        "\033[104m", // 明亮蓝色
        "\033[105m", // 明亮品红
        "\033[106m", // 明亮青色
        "\033[107m", // 明亮白色
        "\033[0m"    // 重置
    };

    if(color.bg != CLR_NONE){
        // 设置前景色和背景色
        printf("%s%s", fg_color_map[color.fg], bg_color_map[color.bg]);
    }else {
        printf("%s", fg_color_map[color.fg]);
    }

    // 打印内容
    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);

    // 重置颜色
    printf("\033[0m");
#endif
    return ret;
}

/**
 * @brief 打印错误信息到标准错误输出
 * @param str 错误信息
 */
void binhub_cperror(const char *str){
    binhub_chcolor(BINHUB_COLOR_INIT(CLR_RED, CLR_NONE));
    perror(str);
    binhub_chcolor(BINHUB_COLOR_INIT(CLR_WHITE, CLR_NONE));
}

/**
 * @brief 输出自定义错误信息(custom/colorful error)
 * @param format 格式化字符串
 * @param ... 可变参数列表
 */
void binhub_cerr(const char *format, ...) {
    binhub_chcolor(BINHUB_COLOR_INIT(CLR_RED, CLR_NONE));
    va_list args; // 创建可变参数列表指针
    va_start(args, format); // 初始化可变参数列表
    vfprintf(stderr, format, args);
    va_end(args); // 清理可变参数列表
    fputc('\n', stderr); // 添加换行并刷新缓冲区
    fflush(stderr);  // 确保错误信息立即显示
    binhub_chcolor(BINHUB_COLOR_INIT(CLR_WHITE, CLR_NONE));
}

/**
 * @brief 输出自定义致命错误信息并终止程序（custom/colorful error - fatal）
 * @param format 格式化字符串
 * @param ... 可变参数列表
 */
void binhub_cerr_f(const char *format, ...) {
    binhub_chcolor(BINHUB_COLOR_INIT(CLR_RED, CLR_NONE));
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputc('\n', stderr);
    fflush(stderr);
	binhub_chcolor(BINHUB_COLOR_INIT(CLR_WHITE, CLR_NONE));
    exit(EXIT_FAILURE); // 终止程序执行
}

/**
 * @brief 输出自定义警告信息（custom/colorful warn）
 * @param format 格式化字符串
 * @param ... 可变参数列表
 */
void binhub_cwarn(const char *format, ...) {
    binhub_chcolor(BINHUB_COLOR_INIT(CLR_YELLOW, CLR_NONE));
    va_list args; // 创建可变参数列表指针
    va_start(args, format); // 初始化可变参数列表
    vfprintf(stderr, format, args);
    va_end(args); // 清理可变参数列表
    fputc('\n', stderr); // 添加换行并刷新缓冲区
    fflush(stderr);  // 确保错误信息立即显示
    binhub_chcolor(BINHUB_COLOR_INIT(CLR_WHITE, CLR_NONE));
}

void binhub_chcolor(binhub_tcolor_t color){
#ifdef _WIN32
    // Windows 平台
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD original_attrs;

    // 获取原始控制台属性
    GetConsoleScreenBufferInfo(h_console, &consoleInfo);
    original_attrs = consoleInfo.wAttributes;

    // 定义颜色代码
    WORD fg_color_map[] = {
        0,     // 黑色
        0x4,   // 红色
        0x2,   // 绿色
        0x6,   // 黄色
        0x1,   // 蓝色
        0x5,   // 品红
        0x3,   // 青色
        0x7,   // 白色
        0x8,   // 明亮黑色
        0xC,   // 明亮红色
        0xA,   // 明亮绿色
        0xE,   // 明亮黄色
        0x9,   // 明亮蓝色
        0xD,   // 明亮品红
        0xB,   // 明亮青色
        0xF    // 明亮白色
    };

    WORD bg_color_map[] = {
        0,      // 黑色
        0x40,   // 红色
        0x20,   // 绿色
        0x60,   // 黄色
        0x10,    // 蓝色
        0x50,    // 品红
        0x30,    // 青色
        0x70,    // 白色
        0x80,    // 明亮黑色
        0xC0,    // 明亮红色
        0xA0,    // 明亮绿色
        0xE0,    // 明亮黄色
        0x90,    // 明亮蓝色
        0xD0,    // 明亮品红
        0xB0,    // 明亮青色
        0xF0     // 明亮白色
    };

    // 获取当前背景色部分
    WORD current_bg = original_attrs & 0xF0; // 高4位是背景色
    WORD new_attrs = fg_color_map[color.fg];

    // 设置背景色
    if(color.bg != CLR_NONE){
        new_attrs |= bg_color_map[color.bg];
    }else {
        new_attrs |= current_bg; // 保留当前背景色
    }

    // 设置颜色
    //SetConsoleTextAttribute(h_console, fg_color_map[color.fg] | bg_color_map[color.bg]);
    SetConsoleTextAttribute(h_console, new_attrs);
#else
    // Linux 平台
    const char* fg_color_map[] = {
        "\033[30m", // 黑色
        "\033[31m", // 红色
        "\033[32m", // 绿色
        "\033[33m", // 黄色
        "\033[34m", // 蓝色
        "\033[35m", // 品红
        "\033[36m", // 青色
        "\033[37m", // 白色
        "\033[90m", // 明亮黑色
        "\033[91m", // 明亮红色
        "\033[92m", // 明亮绿色
        "\033[93m", // 明亮黄色
        "\033[94m", // 明亮蓝色
        "\033[95m", // 明亮品红
        "\033[96m", // 明亮青色
        "\033[97m", // 明亮白色
        "\033[0m"   // 重置
    };

    const char* bg_color_map[] = {
        "\033[40m", // 黑色
        "\033[41m", // 红色
        "\033[42m", // 绿色
        "\033[43m", // 黄色
        "\033[44m", // 蓝色
        "\033[45m", // 品红
        "\033[46m", // 青色
        "\033[47m", // 白色
        "\033[100m", // 明亮黑色
        "\033[101m", // 明亮红色
        "\033[102m", // 明亮绿色
        "\033[103m", // 明亮黄色
        "\033[104m", // 明亮蓝色
        "\033[105m", // 明亮品红
        "\033[106m", // 明亮青色
        "\033[107m", // 明亮白色
        "\033[0m"    // 重置
    };

    if(color.bg != CLR_NONE){
        // 设置前景色和背景色
        printf("%s%s", fg_color_map[color.fg], bg_color_map[color.bg]);
    }else {
        printf("%s", fg_color_map[color.fg]);
    }
#endif
}

binhub_tcolor_t binhub_win_attr_to_tcolor(uint8_t win32_color_attr){
    uint8_t high_nibble, low_nibble;
    // 提取高位（前4位）和低位（后4位）
    high_nibble = (win32_color_attr >> 4) & 0x0F;
    low_nibble = win32_color_attr & 0x0F;

    binhub_tcolor_t color;
    switch(low_nibble){
        case 0x0: color.fg = CLR_BLACK; break;
        case 0x1: color.fg = CLR_BLUE; break;
        case 0x2: color.fg = CLR_GREEN; break;
        case 0x3: color.fg = CLR_CYAN; break;
        case 0x4: color.fg = CLR_RED; break;
        case 0x5: color.fg = CLR_MAGENTA; break;
        case 0x6: color.fg = CLR_YELLOW; break;
        case 0x7: color.fg = CLR_WHITE; break;
        case 0x8: color.fg = CLR_BRT_BLACK; break;
        case 0x9: color.fg = CLR_BRT_BLUE; break;
        case 0xA: color.fg = CLR_BRT_GREEN; break;
        case 0xB: color.fg = CLR_BRT_CYAN; break;
        case 0xC: color.fg = CLR_BRT_RED; break;
        case 0xD: color.fg = CLR_BRT_MAGENTA; break;
        case 0xE: color.fg = CLR_BRT_YELLOW; break;
        case 0xF: color.fg = CLR_BRT_WHITE; break;
    }
    switch(high_nibble){
        case 0x0: color.bg = CLR_BLACK; break;
        case 0x1: color.bg = CLR_BLUE; break;
        case 0x2: color.bg = CLR_GREEN; break;
        case 0x3: color.bg = CLR_CYAN; break;
        case 0x4: color.bg = CLR_RED; break;
        case 0x5: color.bg = CLR_MAGENTA; break;
        case 0x6: color.bg = CLR_YELLOW; break;
        case 0x7: color.bg = CLR_WHITE; break;
        case 0x8: color.bg = CLR_BRT_BLACK; break;
        case 0x9: color.bg = CLR_BRT_BLUE; break;
        case 0xA: color.bg = CLR_BRT_GREEN; break;
        case 0xB: color.bg = CLR_BRT_CYAN; break;
        case 0xC: color.bg = CLR_BRT_RED; break;
        case 0xD: color.bg = CLR_BRT_MAGENTA; break;
        case 0xE: color.bg = CLR_BRT_YELLOW; break;
        case 0xF: color.bg = CLR_BRT_WHITE; break;
    }
    return color;
}

/**
 * @brief 设置控制台编码（跨平台实现）
 * @param encoding 编码类型：ENCODING_GBK 或 ENCODING_UTF8
 * @return int 成功返回0，失败返回非0错误码
 */
int binhub_setenc(enum binhub_console_encoding_t encoding) {
    int result = 0;

#if defined(_WIN32) || defined(_WIN64)

    unsigned int code_page;
    switch (encoding) {
        case ENCODING_GBK:
            code_page = 936; // GBK代码页
            break;
        case ENCODING_UTF8:
            code_page = 65001; // UTF-8代码页
            break;
        default:
            return -1; // 不支持的编码类型
    }

    // 设置控制台输入和输出编码
    if (!SetConsoleCP(code_page) || !SetConsoleOutputCP(code_page)) {
        result = GetLastError();
        fprintf(stderr, "设置控制台编码失败，错误码: %d\n", result);
    }

#elif defined(__linux__) || defined(__unix__)

    const char* locale_name;
    switch (encoding) {
        case ENCODING_GBK:
            locale_name = "zh_CN.GBK";
            break;
        case ENCODING_UTF8:
            locale_name = "zh_CN.UTF-8";
            break;
        default:
            return -1; // 不支持的编码类型
    }

    // 设置locale
    if (setlocale(LC_ALL, locale_name) == NULL) {
        fprintf(stderr, "警告: 无法设置locale为 %s\n", locale_name);

        // 尝试设置仅字符类型
        if (setlocale(LC_CTYPE, locale_name) == NULL) {
            fprintf(stderr, "错误: 也无法设置LC_CTYPE为 %s\n", locale_name);
            result = -2;
        }
    }

    // 对于Linux，还需要确保终端本身支持该编码，通知用户手动配置终端
    if (result == 0) {
        // 检查当前编码是否设置成功
        const char* currentCodeset = nl_langinfo(CODESET);
        if (strcasecmp(currentCodeset, (encoding == ENCODING_GBK) ? "GBK" : "UTF-8") != 0) {
            fprintf(stderr, "提示: 终端编码可能需要手动设置。当前编码: %s\n", currentCodeset);
            fprintf(stderr, "对于大多数终端，您可以在设置中更改字符编码。\n");
        }
    }
#else
    // 其他不支持的平台
    fprintf(stderr, "错误: 不支持的操作系统平台\n");
    result = -3;
#endif

    return result;
}

bool is_data_utf8(const char* data, int len) {
    int i = 0;
    while (i < len) {
        if ((data[i] & 0x80) == 0) {  // 0xxxxxxx
            i++;
        } else if ((i + 1 < len) && ((data[i] & 0xE0) == 0xC0) && ((data[i + 1] & 0xC0) == 0x80)) {  // 110xxxxx 10xxxxxx
            i += 2;
        } else if ((i + 2 < len) && ((data[i] & 0xF0) == 0xE0) && ((data[i + 1] & 0xC0) == 0x80) && ((data[i + 2] & 0xC0) == 0x80)) {  // 1110xxxx 10xxxxxx 10xxxxxx
            i += 3;
        } else {
            return false;  // 不是 UTF-8
        }
    }
    return true;  // 是 UTF-8
}

int binhub_setcp_auto(const char* filename) {
    const binhub_tcolor_t color_failed = { CLR_RED, CLR_NONE };
    const binhub_tcolor_t color_success = { CLR_BLACK, CLR_BRT_MAGENTA };
    FILE* input_file = fopen(filename, "rb");
    if (!input_file) {
        binhub_cprintf(color_failed, "Failed to open input file!\n");
        exit(1);
    }

    // 获取文件大小
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    // 分配内存读取文件内容
    char* data = (char*)malloc(file_size);
    if (!data) {
        fclose(input_file);
        binhub_cprintf(color_failed, "Memory allocation failed!\n");
        exit(1);
    }
    int returnValue = fread(data, 1, file_size, input_file);
    fclose(input_file);

    // 检测是否为UTF-8
    bool isUTF8 = is_data_utf8(data, file_size);
    free(data);

    if (isUTF8) {
        binhub_setenc(ENCODING_UTF8);
        binhub_cprintf(color_success, "Set CodePage: CP65001/UTF-8");
        putchar('\n');
    } else {
        binhub_setenc(ENCODING_GBK);
        binhub_cprintf(color_success, "Set CodePage: CP936/GBK");
        putchar('\n');
    }
    return 0;
}


void load_loop(const char* text, int style){
#if defined(_WIN32) || defined(_WIN64)
    char* sym_braille[9] = {"⣷","⣯","⣟","⡿","⢿","⣻","⣽","⣾","⣿"};
    char* sym_ascii[4] = {"-","\\","|","/"};
    typedef struct {
        char** sym; // 字符数组指针
        int num;    // 字符数
        int sleep;  // 字符速度（休眠时间）
    } load_loop_attr_t;
    load_loop_attr_t style_attr1 = {sym_braille, 9, 60};
    load_loop_attr_t style_attr2 = {sym_ascii, 4, 180};

    unsigned int init_input_cp, init_output_cp;
    init_input_cp = GetConsoleCP();
    init_output_cp = GetConsoleOutputCP();
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出句柄
    CONSOLE_CURSOR_INFO cursor_info;                // 光标信息变量
    GetConsoleCursorInfo(h_out, &cursor_info);       // 获取当前光标信息
    cursor_info.dwSize = 25;
    cursor_info.bVisible = 0;                       // 隐藏光标
    SetConsoleCursorInfo(h_out, &cursor_info);

    // 显示Load Loop
    int sleepnum = (style==0 ? style_attr1.sleep : style_attr2.sleep);
    for(int i = 0 ; ; i++){
        i %= (style==0 ? style_attr1.num : style_attr2.num);                            // 循环符号数组
        printf("\r%s %s", (style==0 ? style_attr1.sym[i] : style_attr2.sym[i]), text);     // 使用符号输出进度
        Sleep(sleepnum);                        // 休眠
    }

    cursor_info.bVisible = 1;                       // 重新显示光标
    SetConsoleCursorInfo(h_out, &cursor_info);
    SetConsoleCP(init_input_cp);
    SetConsoleOutputCP(init_output_cp);
#else
#endif
}

bool binhub_clear_screen() {
#if defined(_WIN32) || defined(_WIN64)
    // 不使用 Windows API 是为了保持兼容性
    return system("cls") == 0;
#else
    return system("clear") == 0;
#endif
}