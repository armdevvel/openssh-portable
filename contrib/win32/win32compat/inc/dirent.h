// direntry functions in Windows platform like Ubix/Linux
// opendir(), readdir(), closedir().
// 	NT_DIR * nt_opendir(char *name) ;
// 	struct nt_dirent *nt_readdir(NT_DIR *dirp);
// 	int nt_closedir(NT_DIR *dirp) ;

#ifndef __DIRENT_H__
#define __DIRENT_H__

#include <direct.h>
#include <io.h>
#include <fcntl.h>

#define MAX_PATH 260

struct dirent {
	int            d_ino;       /* Inode number */
	char           d_name[MAX_PATH]; /* Null-terminated filename */
};

typedef struct DIR_ DIR;

DIR * opendir(const char*);
int closedir(DIR*);
struct dirent *readdir(void*);

#endif