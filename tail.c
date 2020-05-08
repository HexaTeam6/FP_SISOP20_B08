#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[20002];

void tail(int argc, char *argv[]);

int main(int argc, char *argv[]){
    if (argc <= 1){
        printf(1, "tail: need argument at least 1 argument!\n");
        exit();
    }
    else{
        tail(argc, argv);
    }

    exit();
}

void tail(int argc, char *argv[]){
    int i, j;
    for (i = 1; i < argc; i++){
        int fd;
        if ((fd = open(argv[i], O_RDWR)) < 0){
            printf(1, "tail: cannot open %s\n", argv[i]);
            exit();
        }
        printf(1, "file name: %s\n", argv[i]);

        char data[20002];
        int n, iter = 0, count = 0, total = 0, start = 0;

        while ((n = read(fd, buf, sizeof(buf))) > 0){
            for (j = 0; j < n; j++){
                data[iter] = (char)buf[j];
                iter++;

                if (buf[j] == '\n'){
                    count++;
                }
            }
        }

        if (n < 0){
            printf(1, "tail: failed to read file!\n");
            exit();
        }

        if (count < 10){
            total = count;
        }
        else{
            total = 10;
        }

        start = count - total + 1;
        int k = 0;
        for (j = 0; j < iter; j++){
            if (k >= start){
                printf(1, "%c", data[j]);
            }
            if (data[j] == '\n'){
                k++;
            }
        }
        printf(1, "\n");

        if (i != argc - 1){
            printf(1, "\n");
        }
    }
}