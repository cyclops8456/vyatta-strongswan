/*
 * Copyright (C) 2010 Martin Willi
 * Copyright (C) 2010 revosec AG
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

#include "gcm_plugin.h"

#include <library.h>

#include "gcm_aead.h"

typedef struct private_gcm_plugin_t private_gcm_plugin_t;

/**
 * private data of gcm_plugin
 */
struct private_gcm_plugin_t {

	/**
	 * public functions
	 */
	gcm_plugin_t public;
};

METHOD(plugin_t, get_name, char*,
	private_gcm_plugin_t *this)
{
	return "gcm";
}

METHOD(plugin_t, destroy, void,
	private_gcm_plugin_t *this)
{
	lib->crypto->remove_aead(lib->crypto,
					(aead_constructor_t)gcm_aead_create);

	free(this);
}

/*
 * see header file
 */
plugin_t *gcm_plugin_create()
{
	private_gcm_plugin_t *this;
	crypter_t *crypter;

	INIT(this,
		.public = {
			.plugin = {
				.get_name = _get_name,
				.reload = (void*)return_false,
				.destroy = _destroy,
			},
		},
	);

	crypter = lib->crypto->create_crypter(lib->crypto, ENCR_AES_CBC, 0);
	if (crypter)
	{
		crypter->destroy(crypter);
		lib->crypto->add_aead(lib->crypto, ENCR_AES_GCM_ICV8, get_name(this),
						(aead_constructor_t)gcm_aead_create);
		lib->crypto->add_aead(lib->crypto, ENCR_AES_GCM_ICV12, get_name(this),
						(aead_constructor_t)gcm_aead_create);
		lib->crypto->add_aead(lib->crypto, ENCR_AES_GCM_ICV16, get_name(this),
						(aead_constructor_t)gcm_aead_create);
	}

	return &this->public.plugin;
}
