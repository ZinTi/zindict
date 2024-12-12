#include "about.h"

void Help(const char* mPath, const char* qStr){
   if(qStr==(void*)0){
      /*
      printf("In interactive mode, strings starting with \".\" or \":\" are treated as built-in commands, while those starting with \"?\" are queries about the command's functionality.\n");
      printf("List of all dict commands(case insensitive):\n");
      printf("    %-18s%s\n", "clear, cls", "Clear screen.");
      printf("    %-18s%s\n", "exit, quit", "Exit DICT.");
      printf("    %-18s%s\n", "help, manual", "Display this help.");
      printf("    %-18s%s\n", "prompt", "Change your prompt.");
      */
     printf(USER_MANUAL);
   }else{
      printf("To display how to use the \"%s\" commands.\n", qStr);
      printf("To be developed.\n");
   }
   return;
}

void About(void){
	printf("%s version %s %s\n", PROJ_NAME, PROJ_VER, COMPILED);
	printf("Copyleft (c) %s %s. Licensed under the GNU General Public License.\n", PROJ_YEARS, AUTHOR);
    printf("Email: %s\n\n", CONTACT);
}

int SetHomePath(char* homePath){
	if(homePath == (void*)0){
		puts("CheckEnv: Please allocate memory first!");
		return -1;
	}

#ifdef _WIN32
    // 获取当前程序的绝对路径（Windows）
    GetModuleFileName((void*)0, homePath, MAX_PATH);
#else
    // 获取当前程序的绝对路径（Unix-like）
    ssize_t len = readlink("/proc/self/exe", homePath, 259);
    if(len == -1){
        perror("readlink");
        return 1;
    }
    homePath[len] = '\0';
#endif

    // 从路径的末尾向前寻找两次目录分隔符
#ifdef _WIN32
    char sep = '\\'; // Windows 使用反斜杠作为分隔符
#else
    char sep = '/';  // Unix/Linux 使用斜杠作为分隔符
#endif
    int count = 0;
    for (int i = strlen(homePath) - 1; i >= 0; --i) {
        if (homePath[i] == sep) {
            count++;
            if (count == 2) { // 找到倒数第二个分隔符
                homePath[i] = '\0'; // 截断字符串到父目录
                break;
            }
        }
    }

    if (count < 2) {
        fprintf(stderr, "Error: Could not find parent directory.\n");
        return 1;
    }
    return 0;
}