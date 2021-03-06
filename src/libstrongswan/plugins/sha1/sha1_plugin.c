/*
 * Copyright (C) 2008 Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include "sha1_plugin.h"

#include <library.h>
#include "sha1_hasher.h"
#include "sha1_prf.h"

typedef struct private_sha1_plugin_t private_sha1_plugin_t;

/**
 * private data of sha1_plugin
 */
struct private_sha1_plugin_t {

	/**
	 * public functions
	 */
	sha1_plugin_t public;
};

METHOD(plugin_t, get_name, char*,
	private_sha1_plugin_t *this)
{
	return "sha1";
}

METHOD(plugin_t, destroy, void,
	private_sha1_plugin_t *this)
{
	lib->crypto->remove_hasher(lib->crypto,
							   (hasher_constructor_t)sha1_hasher_create);
	lib->crypto->remove_prf(lib->crypto,
							   (prf_constructor_t)sha1_prf_create);
	free(this);
}

/*
 * see header file
 */
plugin_t *sha1_plugin_create()
{
	private_sha1_plugin_t *this;

	INIT(this,
		.public = {
			.plugin = {
				.get_name = _get_name,
				.reload = (void*)return_false,
				.destroy = _destroy,
			},
		},
	);

	lib->crypto->add_hasher(lib->crypto, HASH_SHA1, get_name(this),
							(hasher_constructor_t)sha1_hasher_create);
	lib->crypto->add_prf(lib->crypto, PRF_KEYED_SHA1, get_name(this),
							(prf_constructor_t)sha1_prf_create);

	return &this->public.plugin;
}

