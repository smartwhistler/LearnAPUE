BEGIN {
	printf("#include \"apue.h\"\n");
	printf("#include <errno.h>\n");
	printf("#include <limits.h>\n");
	printf("\n");
	printf("static void pr_sysconf(char *, int);\n")
	printf("static void pr_pathconf(char *, char *, int);\n");
	printf("\n");
	printf("int main(int argc, char *argv[]) {\n");
	printf("\tif (argc!=2)");
	printf("\terr_quit(\"usage: a.out <dirname>\");\n\n");
	FS="\t+"; # 字段分割符
	while (getline <"sysconf.sym" >0) {
		printf("#ifdef %s\n", $1);	# $1为标准规定的最小值
		printf("\tprintf(\"%s defined to be %%d.\\n\", %s+0);\n", $1, $1);
		printf("#else\n");
		printf("\tprintf(\"no symble for %s\\n\");\n", $1);
		printf("#endif\n");
		printf("#ifdef %s\n", $2);
		printf("\tpr_sysconf(\"%s is\", %s+0);\n", $2, $2);
		printf("#else\n");
		printf("\tprintf(\"no symble for %s\\n\");\n", $2);
		printf("#endif\n\n");
	}
	close("sysconf.sym");
	while (getline <"pathconf.sym" >0) {
		printf("#ifdef %s\n", $1);	# $1为标准规定的最小值
		printf("\tprintf(\"%s defined to be %%d.\\n\", %s+0);\n", $1, $1);
		printf("#else\n");
		printf("\tprintf(\"no symble for %s\\n\");\n", $1);
		printf("#endif\n");
		printf("#ifdef %s\n", $2);
		printf("\tpr_pathconf(\"%s is\", argv[1], %s+0);\n", $2, $2);
		printf("#else\n");
		printf("\tprintf(\"no symble for %s\\n\");\n", $2);
		printf("#endif\n\n");
	}
	close("pathconf.sym");
	exit;
}
END{
	printf("\texit(0);\n");
	printf("}\n\n");
	printf("static void pr_sysconf(char *prt, int name) {\n");
	printf("\tlong val;\n");
	printf("\tfputs(prt, stdout);\n");
	printf("\terrno=0;\n");
	printf("\tif( (val=sysconf(name))<0 ) {\n");
	printf("\t\tif(errno!=0) {\n");
	printf("\t\t\tif(errno == EINVAL) fputs(\" not supported\\n\", stdout);\n");
	printf("\t\t\telse err_sys(\"sysconf errno\");\n");
	printf("\t\t} else fputs(\" no limit\\n\", stdout);\n");
	printf("\t} else {\n");
	printf("\t\tprintf(\" %%ld\\n\", val);\n\t}\n");
	printf("}\n");
	
	printf("static void pr_pathconf(char *prt, char *path, int name) {\n");
	printf("\tlong val;\n");
	printf("\tfputs(prt, stdout);\n");
	printf("\terrno=0;\n");
	printf("\tif( (val=pathconf(path, name))<0 ) {\n");
	printf("\t\tif(errno!=0) {\n");
	printf("\t\t\tif(errno == EINVAL) fputs(\" not supported\\n\", stdout);\n");
	printf("\t\t\telse err_sys(\"pathconf errno, path: %%s\", path);\n");
	printf("\t\t} else fputs(\" no limit\\n\", stdout);\n");
	printf("\t} else {\n");
	printf("\t\tprintf(\" %%ld\\n\", val);\n\t}\n");
	printf("}\n");
}
