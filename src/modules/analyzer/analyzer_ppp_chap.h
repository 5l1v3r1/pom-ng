/*
 *  This file is part of pom-ng.
 *  Copyright (C) 2013 Guy Martin <gmsoft@tuxicoman.be>
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

#ifndef __ANALYZER_PPP_CHAP_H__
#define __ANALYZER_PPP_CHAP_H__

#include <pom-ng/event.h>

#define ANALYZER_PPP_CHAP_MSCHAPV2_DATA_COUNT 8

#define ANALYZER_PPP_CHAP_CHALLENGE	0x1
#define ANALYZER_PPP_CHAP_RESPONSE	0x2
#define ANALYZER_PPP_CHAP_RESULT	0x4
#define ANALYZER_PPP_CHAP_DONE		0x7

struct analyzer_ppp_chap_priv {


	struct event_reg *evt_challenge_response;
	struct event_reg *evt_success_failure;

	struct event_reg *evt_mschapv2;

};


enum analyzer_ppp_chap_auth_type {
	analyzer_ppp_chap_auth_unknown = 0,
	analyzer_ppp_chap_auth_mschapv2,
	analyzer_ppp_chap_auth_md5,
};

struct analyzer_ppp_chap_ce_priv {


	struct event *evt_challenge;
	struct event *evt_response;
	struct event *evt_result;

	struct event *evt;

};


enum {
	analyzer_ppp_chap_common_src = 0,
	analyzer_ppp_chap_common_dst,
	analyzer_ppp_chap_common_identifier,
	analyzer_ppp_chap_common_username,
	analyzer_ppp_chap_common_success
};

enum {
	analyzer_ppp_chap_mschapv2_auth_challenge = analyzer_ppp_chap_common_success + 1,
	analyzer_ppp_chap_mschapv2_response,
	analyzer_ppp_chap_mschapv2_peer_challenge
};

int analyzer_ppp_chap_mod_register(struct mod_reg *mod);
int analyzer_ppp_chap_mod_unregister();
int analyzer_ppp_chap_init(struct analyzer *analyzer);
int analyzer_ppp_chap_cleanup(struct analyzer *analyzer);
int analyzer_ppp_chap_event_listeners_notify(void *obj, struct event_reg *evt_reg, int has_listeners);
int analyzer_ppp_chap_event_process_begin(struct event *evt, void *obj, struct proto_process_stack *stack, unsigned int stack_index);
int analyzer_ppp_chap_finalize(struct analyzer_ppp_chap_priv *apriv, struct analyzer_ppp_chap_ce_priv *cpriv);
int analyzer_ppp_chap_ce_priv_cleanup(void *obj, void *priv);

#endif
