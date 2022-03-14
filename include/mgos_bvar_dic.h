/*
 * Copyright (c) 2021 DIY365
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MGOS_BVAR_DIC_H_
#define MGOS_BVAR_DIC_H_

#include <stdlib.h>
#include <stdbool.h>
#include "mgos_bvar.h"

#ifdef MGOS_HAVE_MJS
#include "mjs.h"
#endif /* MGOS_HAVE_MJS */ 

#ifdef __cplusplus
extern "C" {
#endif

#define MGOS_BVAR_TYPE_DIC 1

typedef void *mgos_bvar_enum_t;
typedef void *mgos_bvarc_enum_t;

mgos_bvar_t mgos_bvar_new_dic();

bool mgos_bvar_is_dic(mgos_bvarc_t var);

/* Removes all keys without disposing them (see mgos_bvar_clear() if you want to remove and dispose) */
void mgos_bvar_remove_keys(mgos_bvar_t var);
/* Removes the key without disposing it (see mgos_bvar_delete_key() if you want to remove and dispose) */
mgos_bvar_t mgos_bvar_remove_key(mgos_bvar_t var, const char *key);
/* Removes and disposes the key (see mgos_bvar_remove_key() if you do not want to dispose) */
void mgos_bvar_delete_key(mgos_bvar_t var, const char *key);

bool mgos_bvar_has_key(mgos_bvarc_t dic, const char *key_name);

mgos_bvar_enum_t mgos_bvar_get_keys(mgos_bvar_t dic);
mgos_bvarc_enum_t mgos_bvarc_get_keys(mgos_bvarc_t dic);

mgos_bvarc_t mgos_bvarc_get_key(mgos_bvarc_t dic, const char *key_name);
bool mgos_bvarc_try_get_key(mgos_bvarc_t dic, const char *key_name, mgos_bvarc_t *key_value);
bool mgos_bvarc_get_next_key(mgos_bvarc_enum_t *key_enum, mgos_bvarc_t *key_value, const char **key_name);

mgos_bvar_t mgos_bvar_get_key(mgos_bvar_t dic, const char *key_name);
bool mgos_bvar_try_get_key(mgos_bvar_t dic, const char *key_name, mgos_bvar_t *key_value);
bool mgos_bvar_get_next_key(mgos_bvar_enum_t *key_enum, mgos_bvar_t *key_value, const char **key_name);

bool mgos_bvar_add_key(mgos_bvar_t dic, const char *key_name, mgos_bvar_t key_value);

mgos_bvar_t mgos_bvar_set_key(mgos_bvar_t dic, const char *key_name);
mgos_bvar_t mgos_bvar_set_key_integer(mgos_bvar_t dic, const char *key_name, long key_value);
mgos_bvar_t mgos_bvar_set_key_bool(mgos_bvar_t dic, const char *key_name, bool key_value);
mgos_bvar_t mgos_bvar_set_key_decimal(mgos_bvar_t dic, const char *key_name, double key_value);
mgos_bvar_t mgos_bvar_set_key_str(mgos_bvar_t dic, const char *key_name, const char *key_value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_BVAR_DIC_H_ */
