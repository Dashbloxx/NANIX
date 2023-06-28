#pragma once

enum {
	fs_file,
	fs_directory,
	fs_chardevice,
	fs_blockdevice,
	fs_pipe,
	fs_symlink,
	fs_mountpoint
};

typedef struct {
	char filename[128];
	int permissions;
	int type;
	fs_node_t *parent;
} fs_node_t;
