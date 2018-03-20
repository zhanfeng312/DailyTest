#include <stdio.h>
#include <string.h>

int dhcp_translate_prop_escape_character(char *tmp_prop_value, char *actual_opt60_prop_value)
{
    if (!tmp_prop_value || !actual_opt60_prop_value)
    {
        return -1;
    }

    char *p = tmp_prop_value;
    char *p_tmp = NULL;
    while ((p_tmp = strstr(p, "%20")) != NULL) {
        *p_tmp = 0;
        p_tmp += 3;
        strcat(actual_opt60_prop_value, p);
        strcat(actual_opt60_prop_value, " ");
        p = p_tmp;
    }

    strcat(actual_opt60_prop_value, p);

    return 0;
}

int main()
{
    char prop_value[32] = "udhcp%201.12.1";
    char actual_opt60_prop_value[32] = { '\0' };

    dhcp_translate_prop_escape_character(prop_value, actual_opt60_prop_value);

    printf("%s\n", actual_opt60_prop_value);
}