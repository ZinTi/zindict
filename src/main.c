/***********************************************************
  * Copyleft (c) 2023-2025 Mr. ZENG Lai. All rights reserved.
  * 
  * Project: ZinDict
  * Description: 英汉词典
  * Version: 0.1.1
  * Author: Mr. ZENG Lai (Zin)
  * Contact: vip201@126.com
  * Last Modified: Sun Jun  1 13:36:30 2025
  * 
 ***********************************************************/
#include "main.h"

#include "about.h"
#include "str.h"

#define MAX_PATH 260
#ifdef _WIN32
    #define COMMAND_CLEAR                "CLS"
    #define DATABASE_FILENAME            "\\data\\dict.db"
#else
    #define COMMAND_CLEAR                "clear"
    #define DATABASE_FILENAME            "/data/dict.db"
#endif

/**
 * 修改 CodePage 为UTF-8（Windows）
 */
int ChCP(unsigned int newInputCP, unsigned int newOutputCP);

int main(int argc, char* argv[]){
   ChCP(65001, 65001);

   char* homePath = (char*)malloc(MAX_PATH);
   char* dbFilePath = (char*)malloc(MAX_PATH);
   if(SetHomePath(homePath)){ // return != 0
      exit(-1);
   }else{ // return == 0
      strcpy(dbFilePath, homePath);
   }

   strcat(dbFilePath, DATABASE_FILENAME);

   PROMPT prompt;
   strcpy(prompt.text, DEFAULT_PROMPT);
   prompt.color = defaultColor;

   if(argc>1){
      for(int i=1;i<argc;i++){
         QueryTheWord(argv[i], dbFilePath);
      }
   }else{
      About();
      printf("Enter \".help\" for usage hints.\n\n");

      char yourWord[MAX_SIZE_OF_WORD];
      while(1){
         ColorPrintf(defaultColor, (const char*)prompt.text);
         if(fgets(yourWord, sizeof(yourWord), stdin)){
            yourWord[strcspn(yourWord, "\n")] = '\0'; // 去除换行符
         }

         if('.'==yourWord[0] || ':'==yourWord[0]){
            if(!StrCmpIgnoreCase("exit", yourWord+1) || !StrCmpIgnoreCase("quit", yourWord+1) || !StrCmpIgnoreCase("e", yourWord+1) || !StrCmpIgnoreCase("q", yourWord+1)){
               ColorPrintf(defaultColor, "Bye!\n");
               break;
            }else if(!StrCmpIgnoreCase("clear", yourWord+1) || !StrCmpIgnoreCase("cls", yourWord+1)){
               int ret = system(COMMAND_CLEAR);
               continue;
            }else if(!StrCmpIgnoreCase("help", yourWord+1) || !StrCmpIgnoreCase("manual", yourWord+1)){
               Help(argv[0], NULL);
               continue;
            }else if(!StrNCmpIgnoreCase("prompt", yourWord+1, 6)){
               if(strlen(yourWord)==7){
                  strcpy(prompt.text, DEFAULT_PROMPT);
                  printf("Returning to default PROMPT of "DEFAULT_PROMPT"\n");
               }else{
                  strcpy(prompt.text, yourWord+8);
                  printf("PROMPT set to '%s'\n", prompt.text);
               }
               continue;
            }else{
               ColorPrintf(invalidColor, "Invalid command!\n");
            }

         }else if('?'==yourWord[0]){
            // 查询命令
            Help(argv[0], yourWord);
            continue;
         }else{
            QueryTheWord(yourWord, dbFilePath);
         }
      }
   }
   ChCP(0, 0); // 恢复
   return 0;
}

int ChCP(unsigned int newInputCP, unsigned int newOutputCP){
#ifdef _WIN32
   static unsigned int oldInputCP;
   static unsigned int oldOutputCP;
   if(newInputCP != 0){ //
      oldInputCP = GetConsoleCP();
      SetConsoleCP(newInputCP);
   }else{
      SetConsoleCP(oldInputCP);
   }

   if(newOutputCP != 0){
      oldOutputCP = GetConsoleOutputCP();
      SetConsoleOutputCP(newOutputCP);
   }else{
      SetConsoleOutputCP(oldOutputCP);
   }
#else
   // linux默认UTF-8编码，不需要特别指定。
#endif
   return 0;
}

static int ShowResult_callback(void *data, int argc, char **argv, char **azColName){
   //fprintf(stderr, "%s", (const char*)data);
   unsigned short oldColor;

   TextColor tempColor;
   for(int i=0; i<argc; i++){
      switch(i){
         case 0: // 单词
         tempColor = magentaColor; break;
         case 1: // 英式发音
         tempColor = grayColor; break;
         case 2: // 美式发音
         tempColor = grayColor; break;
         case 3: // 词义
         tempColor = lightblueColor; break;
         default:
         tempColor = defaultColor;
      }
      ColorPrintf(tempColor, "%s: ", azColName[i]); // 列名
      // 值
      if(!i){
         ColorPrintf(wordColor, "%s", argv[i] ? argv[i] : "NULL"); // 项目值
         putchar('\n');
      }else{
         printf("%s\n", argv[i] ? argv[i] : "NULL"); // 项目值
      }
   }
   putchar('\n');
   return 0;
}

int QueryTheWord(const char* word, const char* DB){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   rc = sqlite3_open(DB, &db);
   if( rc ){
      fprintf(stderr, "%s: %s\n", sqlite3_errmsg(db), DB);
      exit(0);
   }else{
      ColorPrintf(greenColor, "%s\n", (const char*)word); //
   }

   /* Create SQL statement */
   sql = (char*)malloc(MAX_SIZE_OF_SQL);
   sprintf(sql, "SELECT word_name AS 词语, ph_en AS 英音, ph_am AS 美音, means AS 释义 FROM iciba WHERE word_name LIKE '%s'", word);

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, ShowResult_callback, (void*)data, &zErrMsg); // data是回调函数的第一个参数
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   /*
   else{
      ColorPuts(0x08, "END", 2);
   }*/
   
   sqlite3_close(db);

   free(sql);
   return 0;
}


