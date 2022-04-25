/*
** EPITECH PROJECT, 2021
** sysnavTask05
** File description:
** utils.c
*/

int count_char(char *str, char c)
{
    int res = 0;

    for (int i = 0; str[i] != '\0'; i++)
        res += str[i] == c ? 1 : 0;
    return (res);
}

int find_length(char *str)
{
    int i = 0;

    for (; str[i] != '\n'; i++);
    return (i);
}