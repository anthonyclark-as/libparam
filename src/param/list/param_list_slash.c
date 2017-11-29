/*
 * param_list_slash.c
 *
 *  Created on: Dec 14, 2016
 *      Author: johan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <slash/slash.h>

#include <libparam.h>
#include <param/param.h>
#include <param/param_list.h>
#include "param_list.h"
#include "../param_slash.h"

static int list(struct slash *slash)
{
	if (slash->argc > 1)
		param_list_print(slash->argv[1]);
	else
		param_list_print(NULL);
	return SLASH_SUCCESS;
}
slash_command(list, list, "[str]", "List parameters");

static int list_download(struct slash *slash)
{
	if (slash->argc < 2)
		return SLASH_EUSAGE;

	unsigned int node = atoi(slash->argv[1]);
	unsigned int timeout = 1000;
	if (slash->argc >= 3)
		timeout = atoi(slash->argv[2]);

	param_list_download(node, timeout);

	return SLASH_SUCCESS;
}
slash_command_sub(list, download, list_download, "<node> [timeout]", NULL);

static int list_str(struct slash *slash) {
	int node_filter = -1;
	if (slash->argc >= 2)
		node_filter = atoi(slash->argv[1]);

	param_list_to_string(stdout, node_filter, 0);
	return SLASH_SUCCESS;
}

slash_command_sub(list, str, list_str, "<node_filter>", NULL);

#if defined(PARAM_STORE_VMEM)

static int param_list_store_vmem_save_slash(struct slash *slash)
{
	if (slash->argc != 2)
		return SLASH_EUSAGE;

	int id = atoi(slash->argv[1]);
	param_list_store_vmem_save(vmem_index_to_ptr(id));
	return SLASH_SUCCESS;
}
slash_command_sub(list, save, param_list_store_vmem_save_slash, "<vmem_id>", NULL);

static int param_list_store_vmem_load_slash(struct slash *slash)
{
	if (slash->argc != 2)
		return SLASH_EUSAGE;

	int id = atoi(slash->argv[1]);
	param_list_store_vmem_load(vmem_index_to_ptr(id));

	return SLASH_SUCCESS;
}
slash_command_sub(list, load, param_list_store_vmem_load_slash, "<vmem_id>", NULL);

#elif defined(PARAM_STORE_FILE)

// TODO: Add filename, node_filter and remote_only as input
static int param_list_store_file_save_slash(struct slash *slash)
{
	param_list_store_file_save("param.cfg");
	return SLASH_SUCCESS;
}
slash_command_sub(list, save, param_list_store_file_save_slash, NULL, NULL);

static int param_list_store_file_load_slash(struct slash *slash)
{
	param_list_store_file_load("param.cfg");
	return SLASH_SUCCESS;
}
slash_command_sub(list, load, param_list_store_file_load_slash, NULL, NULL);

#endif
