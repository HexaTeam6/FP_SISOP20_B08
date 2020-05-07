#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *buf;

int
main(int argc, char *argv[]) 
{
    int fd, fd1;
    if(argc <= 1 || argc > 2){
        printf(1, "touch: need 1 argument!\n");
        exit();
    }
    else{
        // printf(1, "touch: %s in processing...\n", argv[1]);
        struct stat st;

        char filename[1000];
        strcpy(filename, argv[1]);
        // char filename[] = "nama.txt";
        // printf(1, "touch: saving %s\n", filename);

        if((fd = open(argv[1], O_RDWR)) < 0) {
            printf(1, "touch: cannot open %s\n", argv[1]);
            exit();
        }
        // printf(1, "touch: open %s\n", argv[1]);

        if(fstat(fd, &st) < 0){
            printf(2, "ls: cannot stat\n");
        }
        int size = st.size;
        // printf(1, "touch: size %d\n", size);

        buf = (char*) malloc(size * sizeof(char));

        int n;
        if((n = read(fd, buf, size)) < 0){
            printf(1, "touch: cannot read %s\n", filename);
            exit();
        }

        unlink(argv[1]);

        if((fd1 = open(filename, O_CREATE | O_RDWR)) < 0) {
            printf(1, "touch: cannot open %s\n", filename);
            exit();
        }

        int c;
        if((c = write(fd1, buf, size)) < 0) {
            printf(1, "touch: cannot write %s\n", filename);
            exit();
        }
        // else{
        //     printf(1, "touch: done writing...\n");
        // }
    }
    exit();
}