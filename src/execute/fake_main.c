#include "./mini_exec.h"

int main(int ac, char **av, char **env)
{
    t_pipeline one, two, three; //english

    one.next = 0;
    // two.next = 0;
    // two.next = &three;
    // three.next = 0;

    t_cmd_block un, deux, trois; //french

    one.cmd_block = &un;
    two.cmd_block = &deux;
    three.cmd_block = &trois;

    un.cmd = ft_split("echo ha -n", ' ');
    deux.cmd = ft_split("cat -e", ' ');
    trois.cmd = ft_split("cat", ' ');

    t_redirect dos, tres;
    trois.redirect = 0;

    un.redirect = &dos;
    dos.type = 1;
    dos.filename = "happy";
    dos.next = &tres;

    tres.type = 3;
    tres.filename = "sad";
    tres.next = 0;
    // // trois.redirect = 0;
    // // (void)(tres);
    // trois.redirect = &tres;
    // tres.type = 3;
    // tres.filename = "result";
    // tres.next = 0;

    (void)(ac);
    (void)(av);
    // printf("check\n");
    mini_execute(&one, env);
    return (0);
}

// cat a | cat < happy | cat > result





// 이거로는 나중에 
// cat a | cat < happy < sad | cat > result