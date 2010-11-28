/*
 * Copyright (C) 2006 Martin Willi
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

#include "eap.h"

ENUM(eap_code_names, EAP_REQUEST, EAP_FAILURE,
	"EAP_REQUEST",
	"EAP_RESPONSE",
	"EAP_SUCCESS",
	"EAP_FAILURE",
);

ENUM(eap_code_short_names, EAP_REQUEST, EAP_FAILURE,
	"REQ",
	"RES",
	"SUCC",
	"FAIL",
);

ENUM_BEGIN(eap_type_names, EAP_IDENTITY, EAP_GTC,
	"EAP_IDENTITY",
	"EAP_NOTIFICATION",
	"EAP_NAK",
	"EAP_MD5",
	"EAP_OTP",
	"EAP_GTC");
ENUM_NEXT(eap_type_names, EAP_TLS, EAP_TLS, EAP_GTC,
	"EAP_TLS");
ENUM_NEXT(eap_type_names, EAP_SIM, EAP_SIM, EAP_TLS,
	"EAP_SIM");
ENUM_NEXT(eap_type_names, EAP_TTLS, EAP_TTLS, EAP_SIM,
	"EAP_TTLS");
ENUM_NEXT(eap_type_names, EAP_AKA, EAP_AKA, EAP_TTLS,
	"EAP_AKA");
ENUM_NEXT(eap_type_names, EAP_MSCHAPV2, EAP_MSCHAPV2, EAP_AKA,
	"EAP_MSCHAPV2");
ENUM_NEXT(eap_type_names, EAP_TNC, EAP_TNC, EAP_MSCHAPV2,
	"EAP_TNC");
ENUM_NEXT(eap_type_names, EAP_RADIUS, EAP_EXPERIMENTAL, EAP_TNC,
	"EAP_RADIUS",
	"EAP_EXPANDED",
	"EAP_EXPERIMENTAL");
ENUM_END(eap_type_names, EAP_EXPERIMENTAL);

ENUM_BEGIN(eap_type_short_names, EAP_IDENTITY, EAP_GTC,
	"ID",
	"NTF",
	"NAK",
	"MD5",
	"OTP",
	"GTC");
ENUM_NEXT(eap_type_short_names, EAP_TLS, EAP_TLS, EAP_GTC,
	"TLS");
ENUM_NEXT(eap_type_short_names, EAP_SIM, EAP_SIM, EAP_TLS,
	"SIM");
ENUM_NEXT(eap_type_short_names, EAP_TTLS, EAP_TTLS, EAP_SIM,
	"TTLS");
ENUM_NEXT(eap_type_short_names, EAP_AKA, EAP_AKA, EAP_TTLS,
	"AKA");
ENUM_NEXT(eap_type_short_names, EAP_MSCHAPV2, EAP_MSCHAPV2, EAP_AKA,
	"MSCHAPV2");
ENUM_NEXT(eap_type_short_names, EAP_TNC, EAP_TNC, EAP_MSCHAPV2,
	"TNC");
ENUM_NEXT(eap_type_short_names, EAP_RADIUS, EAP_EXPERIMENTAL, EAP_TNC,
	"RAD",
	"EXP",
	"XP");
ENUM_END(eap_type_short_names, EAP_EXPERIMENTAL);

ENUM(auth_rule_names, AUTH_RULE_IDENTITY, AUTH_HELPER_SUBJECT_HASH_URL,
	"RULE_IDENTITY",
	"RULE_AUTH_CLASS",
	"RULE_EAP_IDENTITY",
	"RULE_EAP_TYPE",
	"RULE_EAP_VENDOR",
	"RULE_CA_CERT",
	"RULE_IM_CERT",
	"RULE_SUBJECT_CERT",
	"RULE_CRL_VALIDATION",
	"RULE_OCSP_VALIDATION",
	"RULE_GROUP",
	"HELPER_IM_CERT",
	"HELPER_SUBJECT_CERT",
	"HELPER_IM_HASH_URL",
	"HELPER_SUBJECT_HASH_URL",
);

/*
 * See header
 */
eap_type_t eap_type_from_string(char *name)
{
	int i;
	static struct {
		char *name;
		eap_type_t type;
	} types[] = {
		{"identity",	EAP_IDENTITY},
		{"md5",			EAP_MD5},
		{"otp",			EAP_OTP},
		{"gtc",			EAP_GTC},
		{"tls",			EAP_TLS},
		{"ttls",		EAP_TTLS},
		{"sim",			EAP_SIM},
		{"aka",			EAP_AKA},
		{"mschapv2",	EAP_MSCHAPV2},
		{"tnc",			EAP_TNC},
		{"radius",		EAP_RADIUS},
	};

	for (i = 0; i < countof(types); i++)
	{
		if (strcaseeq(name, types[i].name))
		{
			return types[i].type;
		}
	}
	return 0;
}
