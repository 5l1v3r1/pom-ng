/*
 *  This file is part of pom-ng.
 *  Copyright (C) 2010-2014 Guy Martin <gmsoft@tuxicoman.be>
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



#ifndef __POM_NG_REGISTRY_H__
#define __POM_NG_REGISTRY_H__

#include <pom-ng/ptype.h>

#define REGISTRY_PARAM_FLAG_CLEANUP_VAL			0x01
#define REGISTRY_PARAM_FLAG_IMMUTABLE			0x02
#define REGISTRY_PARAM_FLAG_NOT_LOCKED_WHILE_RUNNING	0x04
#define REGISTRY_PARAM_FLAG_PAUSE_PROCESSING		0x08
#define REGISTRY_PARAM_FLAG_INFO_SUGGESTION		0x10

struct registry_instance;
struct registry_param;

enum registry_perf_type {
	registry_perf_type_counter,
	registry_perf_type_gauge,
	registry_perf_type_timeticks

};

struct registry_param* registry_new_param(char *name, char *default_value, struct ptype *value, char *description, int flags);
int registry_cleanup_param(struct registry_param *p);
int registry_param_set_callbacks(struct registry_param *p, void *priv, int (*pre_check) (void *priv, struct registry_param *p, char *value), int (*post_check) (void *priv, struct registry_param *p, struct ptype *value));
int registry_instance_add_function(struct registry_instance *i, char *name, int (*handler) (struct registry_instance *), char *description);
int registry_set_param(struct registry_instance *i, char *param, char* value);

struct registry_perf *registry_instance_add_perf(struct registry_instance *i, const char *name, enum registry_perf_type type, const char *description, const char *unit);
void registry_perf_set_update_hook(struct registry_perf *p, int (*update_hook) (uint64_t *cur_val, void *priv), void *hook_priv);
void registry_perf_inc(struct registry_perf *p, uint64_t val);
void registry_perf_dec(struct registry_perf *p, uint64_t val);
void registry_perf_timeticks_stop(struct registry_perf *p);
void registry_perf_timeticks_restart(struct registry_perf *p);
uint64_t registry_perf_getval(struct registry_perf *p);
void registry_perf_reset(struct registry_perf *p);

int registry_param_info_set_min_max(struct registry_param *p, uint32_t min, uint32_t max);
int registry_param_info_add_value(struct registry_param *p, char *value);

struct registry_instance *registry_create_instance(char *cls, char *type, char *name);
#endif
