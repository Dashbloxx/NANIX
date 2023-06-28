#include "kheap.h"
#include "fs.h"
#include "def.h"

filenode_t *root_directory = NULL;

/*
 *	This function will create the root directory for our filesystem.
 *
 *	The root directory has no name, and no parent, since it is the root
 *	directory. We also don't put any permissions on it, and no size at
 *	all, since we consider it a directory.
 */
int fs_initialize() {
	root_directory = (filenode_t *)kmalloc(sizeof(filenode_t));
	root_directory->type = ft_directory;
	root_directory->parent = NULL;
	root_directory->size = -1;
	root_directory->permissions = -1;
}
