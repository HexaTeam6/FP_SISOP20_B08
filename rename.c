#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

char *buf;

char* strcat(char *s, char *t) {
  char *os = s;

  s += strlen(s);
  while((*t)) {
    *s++ = *t++;
  }

  *s = 0;

  return os;
}

int
main(int argc, char *argv[]) 
{
    if(argc == 3){
        
        int i = 0, size = 0, slash = 0;
        char com[2], bef[100], aft[100];
        while(argv[1][i] != '\0'){
            if(argv[1][i] == '/'){
                slash++;
            }
            size++;
            i++;
        }
        // printf(1, "rename: slash %d\n", slash);
        if(slash < 3){
            printf(1, "rename: argument 1 wrong input.\n");
            exit();
        }

        if(argv[1][0] == '\'' && argv[1][size-1] == '\'' && argv[1][2] == '/'){
            com[0] = argv[1][1];
            if(com[0] != 's' && com[0] != 'y'){
                printf(1, "rename: wrong command %s\n", argv[1]);
                exit();
            }
            int i = 3, iter = 0;
            while(argv[1][i] != '/'){
                bef[iter] = argv[1][i];
                iter++;
                i++;
            }
            i++;
            iter = 0;
            while(argv[1][i] != '/'){
                aft[iter] = argv[1][i];
                iter++;
                i++;
            }
            // printf(1, "rename: before %s\n", bef);
            // printf(1, "rename: after %s\n", aft);
        }
        else{
            printf(1, "rename: failed %s\n", argv[1]);
            exit();
        }

        char ext[1000];
        if(argv[2][0] == '*' && argv[2][1] == '.'){
            int i = 1, iter = 0;
            while(argv[2][i] != '\0'){
                ext[iter] = argv[2][i];
                iter++;
                i++;
            }
            printf(1, "rename: ext %s\n", ext);
            if(strcmp(aft,".") == 0){
                printf(1, "rename: no ext %s\n", ext);
                exit();
            }
        }

        int opt = 0;
        if(strcmp(bef, ext) == 0 && strcmp(aft,"\0") != 0 && com[0] == 's'){
            if(aft[0] == '.' && aft[1] != '\0'){
                printf(1, "rename: option 1 change ext\n");
                opt = 1;
            }
            else{
                printf(1, "rename: option 1 no ext\n");
                exit();
            }
        }
        else if(strcmp(bef,"\0") != 0 && strcmp(aft,"\0") != 0 && com[0] == 's'){
            printf(1, "rename: option 2 change name pattern\n");
            opt = 2;
        }
        else if(strcmp(bef,"\0") != 0 && strcmp(aft,"\0") == 0 && com[0] == 's'){
            printf(1, "rename: option 3 nothing\n");
            opt = 3;
        }
        else if(strcmp(bef,"\0") != 0 && strcmp(aft,"\0") != 0 && com[0] == 'y'){
            if(strcmp(bef, "a-z") == 0 && strcmp(aft, "A-Z") == 0){
                printf(1, "rename: option 4 uppercase\n");
                opt = 4;
            }
            else if(strcmp(bef, "A-Z") == 0 && strcmp(aft, "a-z") == 0){
                printf(1, "rename: option 4 lowercase\n");
                opt = 5;
            }
            else{
                printf(1, "rename: 'y' no option\n");
                exit();
            }
        }
        else{
            printf(1, "rename: no option\n");
            exit();
        }
        // printf(1, "rename: option number %d\n", opt);

        int fd;
        struct dirent de;
        char *path = ".";
        if((fd = open(path, 0)) < 0){
            printf(2, "ls: cannot open %s\n", path);
            exit();
        }
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0){
                continue;
            }    
            // printf(1, "rename: de name %s\n", de.name);

            if(opt == 1){
                int i = 0, count = 0, min = strlen(ext), bc = strlen(ext) - 1;
                char temp[100];
                strcpy(temp, de.name);
                // printf(1, "rename: temp %s\n", temp);
                if(strlen(temp) <= strlen(ext)){
                    continue;
                }
                else
                {
                    for(i = strlen(temp) - 1; i >= strlen(temp) - min; i--){
                        if(temp[i] == ext[bc]){
                            count++;
                        }
                        bc--;
                    }
                    if(count == min){
                        printf(1, "rename: file detected %s\n", de.name);

                        char filename[1000];

                        int j;
                        for(j = 0; j < (strlen(de.name) - strlen(ext)); j++){
                            filename[j] = temp[j];
                        }
                        strcat(filename, aft);
                        printf(1, "rename: new filename %s\n", filename);

                        struct stat st;
                        
                        int fd, fd1;
                        if((fd = open(de.name, O_RDWR)) < 0) {
                            printf(1, "rename: cannot open %s\n", argv[1]);
                            exit();
                        }
                        if(fstat(fd, &st) < 0){
                            printf(2, "rename: cannot stat\n");
                        }
                        int size = st.size;

                        buf = (char*) malloc(size * sizeof(char));

                        int n;
                        if((n = read(fd, buf, size)) < 0){
                            printf(1, "rename: cannot read %s\n", filename);
                            exit();
                        }

                        unlink(de.name);

                        if((fd1 = open(filename, O_CREATE | O_RDWR)) < 0) {
                            printf(1, "rename: cannot open %s\n", filename);
                            exit();
                        }

                        int c;
                        if((c = write(fd1, buf, size)) < 0) {
                            printf(1, "rename: cannot write %s\n", filename);
                            exit();
                        }

                        memset(filename, '\0', sizeof(filename));
                    }
                }
            }
            else if(opt == 2){
                printf(1, "rename: feature has not been fully enabled.\n");
            }
            else if(opt == 3){
                printf(1, "rename: feature has not been fully enabled.\n");
            }
            else if(opt == 4){
                int i = 0, count = 0, min = strlen(ext), bc = strlen(ext) - 1;
                char temp[100];
                strcpy(temp, de.name);
                // printf(1, "rename: temp %s\n", temp);
                if(strlen(temp) <= strlen(ext)){
                    continue;
                }
                else
                {
                    for(i = strlen(temp) - 1; i >= strlen(temp) - min; i--){
                        if(temp[i] == ext[bc]){
                            count++;
                        }
                        bc--;
                    }
                    if(count == min){
                        printf(1, "rename: file detected %s\n", de.name);

                        char filename[1000];
                        strcpy(filename, de.name);

                        int j;
                        for(j = 0; j < (strlen(de.name) - strlen(ext)); j++){
                            if(filename[j] >= 97 && filename[j] <= 122){
                                filename[j] = filename[j] - 32;
                            }
                        }
                        printf(1, "rename: new filename %s\n", filename);

                        struct stat st;
                        
                        int fd, fd1;
                        if((fd = open(de.name, O_RDWR)) < 0) {
                            printf(1, "rename: cannot open %s\n", argv[1]);
                            exit();
                        }
                        if(fstat(fd, &st) < 0){
                            printf(2, "rename: cannot stat\n");
                        }
                        int size = st.size;

                        buf = (char*) malloc(size * sizeof(char));

                        int n;
                        if((n = read(fd, buf, size)) < 0){
                            printf(1, "rename: cannot read %s\n", filename);
                            exit();
                        }

                        unlink(de.name);

                        if((fd1 = open(filename, O_CREATE | O_RDWR)) < 0) {
                            printf(1, "rename: cannot open %s\n", filename);
                            exit();
                        }

                        int c;
                        if((c = write(fd1, buf, size)) < 0) {
                            printf(1, "rename: cannot write %s\n", filename);
                            exit();
                        }

                        memset(filename, '\0', sizeof(filename));
                    }
                }
            }
            else if(opt == 5){
                int i = 0, count = 0, min = strlen(ext), bc = strlen(ext) - 1;
                char temp[100];
                strcpy(temp, de.name);
                // printf(1, "rename: temp %s\n", temp);
                if(strlen(temp) <= strlen(ext)){
                    continue;
                }
                else
                {
                    for(i = strlen(temp) - 1; i >= strlen(temp) - min; i--){
                        if(temp[i] == ext[bc]){
                            count++;
                        }
                        bc--;
                    }
                    if(count == min){
                        printf(1, "rename: file detected %s\n", de.name);

                        char filename[1000];
                        strcpy(filename, de.name);

                        int j;
                        for(j = 0; j < (strlen(de.name) - strlen(ext)); j++){
                            if(filename[j] >= 65 && filename[j] <= 90){
                                filename[j] = filename[j] + 32;
                            }
                        }
                        printf(1, "rename: new filename %s\n", filename);

                        struct stat st;
                        
                        int fd, fd1;
                        if((fd = open(de.name, O_RDWR)) < 0) {
                            printf(1, "rename: cannot open %s\n", argv[1]);
                            exit();
                        }
                        if(fstat(fd, &st) < 0){
                            printf(2, "rename: cannot stat\n");
                        }
                        int size = st.size;

                        buf = (char*) malloc(size * sizeof(char));

                        int n;
                        if((n = read(fd, buf, size)) < 0){
                            printf(1, "rename: cannot read %s\n", filename);
                            exit();
                        }

                        unlink(de.name);

                        if((fd1 = open(filename, O_CREATE | O_RDWR)) < 0) {
                            printf(1, "rename: cannot open %s\n", filename);
                            exit();
                        }

                        int c;
                        if((c = write(fd1, buf, size)) < 0) {
                            printf(1, "rename: cannot write %s\n", filename);
                            exit();
                        }

                        memset(filename, '\0', sizeof(filename));
                    }
                }
            }
            else{
                printf(1, "rename: no option\n");
                exit();
            }
        }
    }
    else{
        printf(1, "rename: need 3 arguments!\n");
        exit();
    }
    exit();
}
