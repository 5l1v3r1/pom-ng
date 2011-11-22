/*
 *  This file is part of pom-ng.
 *  Copyright (C) 2010 Guy Martin <gmsoft@tuxicoman.be>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */



#ifndef __INPUT_CLIENT_H__
#define __INPUT_CLIENT_H__

#include "core.h"
#include "proto.h"
#include "registry.h"

#include <pom-ng/input.h>
#include <pom-ng/input_client.h>

#define INPUT_CLIENT_REGISTRY "input"


struct input_client_param {

	int id;
	struct ptype *value;
	struct input_client_entry *input;

	struct input_client_param *next;

};

struct input_client_reader_thread {
	struct input_client_entry *input;
	pthread_t thread;
	int run; // Indicate if the thread should continue to run or not
	struct packet *pkt;
};

struct input_client_registered_list {
	struct mod_reg *mod;
	char *input_name;
	struct input_client_registered_list *prev, *next;
};

int input_client_init();
int input_client_cleanup(int emergency_cleanup);

int input_client_register_input(struct input_reg_info *reg_info, struct mod_reg *mod);
int input_client_unregister_input(char *name);

void *input_client_reader_thread_func(void *input);
int input_client_get_packet(struct input_client_entry *input, struct packet *p);
int input_client_release_packet(struct input_client_entry *i, struct input_packet *pkt);

int input_client_cmd_mod_load(char *mod_name);
int input_client_cmd_mod_unload(char *mod_name);
int input_client_start_stop_handler(void *priv, struct ptype *run);
int input_client_cmd_add(char *type, char *name);
int input_client_cmd_remove(struct registry_instance *ri);

int input_client_registry_param_apply(void *param, struct ptype *value);

#endif
