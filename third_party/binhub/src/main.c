/**
 * @file main.cpp 测试文件
 */
#include "binhub.h"

int main(int argc, char* argv[]) {
    const binhub_tcolor_t color1 = {CLR_RED, CLR_NONE};
    const binhub_tcolor_t color2 = {CLR_MAGENTA, CLR_NONE};
    const binhub_tcolor_t color3 = {CLR_BLUE, CLR_NONE};

    binhub_whereami();

    binhub_cprintf(color2, "Hello, %s!\n", "BinHub");

    binhub_sllc_t sllc_1 = binhub_sllc_init();
    binhub_sllc_append_str(sllc_1, "Hello, ");
    binhub_sllc_append_str(sllc_1, "SLLC!");
    binhub_sllc_print(sllc_1);
    const char* str1 = binhub_sllc_to_str(sllc_1);
    binhub_cprintf(color3, "%s\n", str1);
    binhub_sllc_free(sllc_1);

    binhub_slls_t slls_1 = binhub_slls_init();
    binhub_slls_insert_head(slls_1, "Hello");
    binhub_slls_insert_head(slls_1, "SLLS");
    binhub_slls_insert_head(slls_1, "World");
    binhub_slls_insert_head(slls_1, "Link");
    binhub_slls_print(slls_1);
    binhub_slls_sort_asc(slls_1);
    binhub_slls_print(slls_1);
    binhub_slls_free(slls_1);

    return 0;
}