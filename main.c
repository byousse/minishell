// int main(int ac, char **av)
// {
//     char *buffer;
//     while(1)
//     {
//         printf("Minishel->>");
//         buffer = get_next_line(0);
//         let_see(buffer, av);
//     }
// }
// void let_see(char *buffer, char **av)
// {
//     int i = 0;
//     char **str;
//     str = ft_take_all_arg(av);
//     if (!str)
//         return ;
//     if(access(str[i], F_OK) == -1)
//         perror("command doesnt exist");
//     else
//     {
//         int fd = open("str[1]", O_RDONLY, 0777);
//         if (fd == -1)
//             execve()
//     }
// }