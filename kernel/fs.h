#pragma once

/*
 *	These might later be removed because it is not sure if they will eventually be
 *	used.
 */
// typedef unsigned int (*read_type_t)(struct filenode_t *, unsigned int, unsigned int, unsigned char *);
// typedef unsigned int (*write_type_t)(struct filenode_t *, unsigned int, unsigned int, unsigned char *);
// typedef void (*open_type_t)(struct filenode_t *, unsigned int);
// typedef void (*close_type_t)(struct filenode_t *, char *name);

/*
 *	This type & enum represents the different types of files that exist
 *	here.
 */
typedef enum {
	ft_file,
	ft_directory,
	ft_character_device,
	ft_socket,
	ft_mountpoint,
	ft_pipe,
	ft_block_device
} filetype_t;

/*
 *	The first value here represents a 128 character/byte string that
 *	stores the name of the file.
 *
 *	The second one represents the type of file that the current file is.
 *
 *	The third value represents the size of the file's contents. Set to
 *	-1 if it isn't supposed to store anything.
 *
 *	The fourth one represents permissions of the file. Set to -1 if you
 *	don't want to set up permissions for that file.
 *
 *	The fifth one is a pointer to the parent file. This kernel will allow
 *	you to place files inside other files, although it is recommended to
 *	just put files inside directories.
 *
 *	The sixth one represents a callback function.
 */
typedef struct {
	char name[128];
	filetype_t type;
	int size;
	int permissions;
	void *parent;
} filenode_t;

int fs_initialize();
