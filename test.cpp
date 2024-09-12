#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>

const int SIZE = 800;

struct passwd *inf;
struct group *info;


int main (int argc, char **argv)
{
    if (argc >= 3)
    {
        printf ("Слишком много аргументов командной строки\n");
        exit (EXIT_FAILURE);
    }

    if (argc == 1)
    {
        long int I = 0;
        long int father = 0;
        unsigned group_list[SIZE] = {};

        printf ("Юзер:%u\n", getuid());
        printf ("Группа:%u\n", getgid());

        inf = getpwuid (getuid());
        printf ("Имя пользователя: %s\n", inf->pw_name);

        info = getgrgid (getgid());
        printf ("Имя группы: %s\n", info->gr_name);

        getgroups (SIZE, group_list);

        for (int i = 0 ; group_list[i] != getgid(); i++)
        {
            printf ("Дополнительные группы:%u(%s)\n", group_list[i], getgrgid(group_list[i]) ->gr_name);
        }
        return 0;
    }

    else
    {
        if ((inf  = getpwnam (argv[1])) == NULL || (info = getgrnam (argv[1])) == NULL)
        {
            printf ("Не удалось найти такого пользователя или группу\n");
            exit (EXIT_FAILURE);
        }

        printf ("Юзер:%u\n", inf->pw_uid );
        printf ("Группа:%u\n", info->gr_gid);
        printf ("Имя пользователя: %s\n", inf->pw_name);
        printf ("Имя группы: %s\n", info->gr_name);

        unsigned group_list[SIZE] = {};
        int ngroups = 64;
        int check  = 0;
        check = getgrouplist (info->gr_name, info->gr_gid, group_list, &ngroups);
        

        for (int i = 0 ; i < ngroups; i++)
        {
            printf ("Дополнительные группы:%u(%s)\n", group_list[i], getgrgid(group_list[i]) ->gr_name);
        }
        return 0;
    }
}