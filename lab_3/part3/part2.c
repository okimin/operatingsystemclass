 #include <stdio.h>
     #include <unistd.h>
     #include <sys/wait.h>
     #include <time.h>

     int main(int argc, char *argv[])
     {   
         int child=fork();
         if (child==0) {
            char *cmd = "ls";
            argv[0] = "ls";
            argv[1] = "-lah";
            argv[2] = NULL;
            execvp(cmd, argv);
         }
    }