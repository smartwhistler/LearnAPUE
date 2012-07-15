#include "apue.h"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char *, char *, int);

int main(int argc, char *argv[]) {
	if (argc!=2)	err_quit("usage: a.out <dirname>");

#ifdef ARG_MAX
	printf("ARG_MAX defined to be %d.\n", ARG_MAX+0);
#else
	printf("no symble for ARG_MAX\n");
#endif
#ifdef _SC_ARG_MAX
	pr_sysconf("_SC_ARG_MAX is", _SC_ARG_MAX+0);
#else
	printf("no symble for _SC_ARG_MAX\n");
#endif

#ifdef ATEXIT_MAX
	printf("ATEXIT_MAX defined to be %d.\n", ATEXIT_MAX+0);
#else
	printf("no symble for ATEXIT_MAX\n");
#endif
#ifdef _SC_ATEXIT_MAX
	pr_sysconf("_SC_ATEXIT_MAX is", _SC_ATEXIT_MAX+0);
#else
	printf("no symble for _SC_ATEXIT_MAX\n");
#endif

#ifdef CHILD_MAX
	printf("CHILD_MAX defined to be %d.\n", CHILD_MAX+0);
#else
	printf("no symble for CHILD_MAX\n");
#endif
#ifdef _SC_CHILD_MAX
	pr_sysconf("_SC_CHILD_MAX is", _SC_CHILD_MAX+0);
#else
	printf("no symble for _SC_CHILD_MAX\n");
#endif

#ifdef CLK_TCK
	printf("CLK_TCK defined to be %d.\n", CLK_TCK+0);
#else
	printf("no symble for CLK_TCK\n");
#endif
#ifdef _SC_CLK_TCK
	pr_sysconf("_SC_CLK_TCK is", _SC_CLK_TCK+0);
#else
	printf("no symble for _SC_CLK_TCK\n");
#endif

#ifdef FILESIZEBITS
	printf("FILESIZEBITS defined to be %d.\n", FILESIZEBITS+0);
#else
	printf("no symble for FILESIZEBITS\n");
#endif
#ifdef _PC_FILESIZEBITS
	pr_pathconf("_PC_FILESIZEBITS is", argv[1], _PC_FILESIZEBITS+0);
#else
	printf("no symble for _PC_FILESIZEBITS\n");
#endif

#ifdef LINK_MAX
	printf("LINK_MAX defined to be %d.\n", LINK_MAX+0);
#else
	printf("no symble for LINK_MAX\n");
#endif
#ifdef _PC_LINK_MAX
	pr_pathconf("_PC_LINK_MAX is", argv[1], _PC_LINK_MAX+0);
#else
	printf("no symble for _PC_LINK_MAX\n");
#endif

#ifdef MAX_CANON
	printf("MAX_CANON defined to be %d.\n", MAX_CANON+0);
#else
	printf("no symble for MAX_CANON\n");
#endif
#ifdef _PC_MAX_CANON
	pr_pathconf("_PC_MAX_CANON is", argv[1], _PC_MAX_CANON+0);
#else
	printf("no symble for _PC_MAX_CANON\n");
#endif

#ifdef MAX_INPUT
	printf("MAX_INPUT defined to be %d.\n", MAX_INPUT+0);
#else
	printf("no symble for MAX_INPUT\n");
#endif
#ifdef _PC_MAX_INPUT
	pr_pathconf("_PC_MAX_INPUT is", argv[1], _PC_MAX_INPUT+0);
#else
	printf("no symble for _PC_MAX_INPUT\n");
#endif

	exit(0);
}

static void pr_sysconf(char *prt, int name) {
	long val;
	fputs(prt, stdout);
	errno=0;
	if( (val=sysconf(name))<0 ) {
		if(errno!=0) {
			if(errno == EINVAL) fputs(" not supported\n", stdout);
			else err_sys("sysconf errno");
		} else fputs(" no limit\n", stdout);
	} else {
		printf(" %ld\n", val);
	}
}
static void pr_pathconf(char *prt, char *path, int name) {
	long val;
	fputs(prt, stdout);
	errno=0;
	if( (val=pathconf(path, name))<0 ) {
		if(errno!=0) {
			if(errno == EINVAL) fputs(" not supported\n", stdout);
			else err_sys("pathconf errno, path: %s", path);
		} else fputs(" no limit\n", stdout);
	} else {
		printf(" %ld\n", val);
	}
}
