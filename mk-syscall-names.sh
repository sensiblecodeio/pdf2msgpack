#!/bin/bash

echo "static const char *syscall_names[] = {" > src/syscall-names.h ;\
echo "#include <sys/syscall.h>" | cpp -dM | grep '^#define __NR_' | \
    LC_ALL=C sed -r -n -e 's/^\#define[ \t]+__NR_([a-z0-9_]+)[ \t]+([0-9]+)(.*)/ [\2] = "\1",/p' | sort -t '[' -k 2 -n >> src/syscall-names.h ;\
echo "};" >> src/syscall-names.h
