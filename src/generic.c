/*
 * Copyright (C) 2015 Andrea Zagli <azagli@libero.it>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include <stdlib.h>
#include <math.h>

#include "generic.h"

/**
 * zak_utils_round:
 * @value:
 * @n_decimals:
 *
 */
gdouble
zak_utils_round (gdouble value, guint n_decimals)
{
	gfloat elev;
	gint i;
	gfloat ret;

	elev = pow (10.0, (gfloat)n_decimals);

	ret = (value * elev) + 0.5;
	i = (gint)ret;

	ret = (gfloat)i / elev;

	return ret;
}

/**
 * zak_utils_gstring_initial_capital:
 * @gstring:
 *
 */
void
zak_utils_gstring_initial_capital (GString *gstring)
{
	const gchar *cutf8;

	GString *tmp;
	gboolean first;
	gunichar c;

	g_return_if_fail (gstring != NULL);
	g_return_if_fail (gstring->str != NULL);
	g_return_if_fail (g_utf8_validate (gstring->str, -1, NULL));

	tmp = g_string_new ("");
	first = TRUE;

	cutf8 = gstring->str;
	while (*cutf8)
		{
			c = g_utf8_get_char (cutf8);
			if (!g_unichar_isalpha (c))
				{
					first = TRUE;
					g_string_append_unichar (tmp, c);
				}
			else if (first)
				{
					first = FALSE;
					g_string_append_unichar (tmp, g_unichar_toupper (c));
				}
			else
				{
					g_string_append_unichar (tmp, g_unichar_tolower (c));
				}
			cutf8 = g_utf8_next_char (cutf8);
		}

	g_string_assign (gstring, tmp->str);
	g_string_free (tmp, TRUE);
}

/**
 * zak_utils_compare_version:
 * @ver1:
 * @ver2:
 * @delimiters:
 * @part:
 *
 */
int
zak_utils_compare_version (const gchar *ver1, const gchar *ver2, const gchar *delimiters, guint *part)
{
	gchar **_ver1;
	gchar **_ver2;

	gchar *_delimiters;

	guint i;
	guint l;

	if (ver1 == NULL)
		{
			return -1;
		}
	if (ver2 == NULL)
		{
			return 1;
		}

	if (delimiters == NULL)
		{
			_delimiters = g_strdup (".");
		}
	else
		{
			_delimiters = g_strstrip (g_strdup (delimiters));
			if (g_strcmp0 (_delimiters, "") == 0)
				{
					g_free (_delimiters);
					_delimiters = g_strdup (".");
				}
		}

	_ver1 = g_strsplit (g_strstrip (g_strdup (ver1)), _delimiters, -1);
	_ver2 = g_strsplit (g_strstrip (g_strdup (ver2)), _delimiters, -1);

	l = MIN (g_strv_length (_ver1), g_strv_length (_ver2));
	for (i = 0; i < l; i++)
		{
			if (strtol (_ver1[i], NULL, 10) < strtol (_ver2[i], NULL, 10))
				{
					if (part != NULL)
						{
							*part = i;
						}
					return -1;
				}
			else if (strtol (_ver1[i], NULL, 10) > strtol (_ver2[i], NULL, 10))
				{
					if (part != NULL)
						{
							*part = i;
						}
					return 1;
				}
		}

	if (g_strv_length (_ver1) < g_strv_length (_ver2))
		{
			*part = g_strv_length (_ver1) + 1;
			return -1;
		}
	else if (g_strv_length (_ver1) > g_strv_length (_ver2))
		{
			*part = g_strv_length (_ver2) + 1;
			return 1;
		}

	*part = 0;
	return 0;
}

/**
 * zak_utils_gvalue_new_int:
 * @i:
 *
 */
GValue
*zak_utils_gvalue_new_int (int i)
{
	GValue *gval;

	gval = g_new0 (GValue, 1);
	g_value_init (gval, G_TYPE_INT);
	g_value_set_int (gval, i);

	return gval;
}

/**
 * zak_utils_gvalue_new_string:
 * @str:
 *
 */
GValue
*zak_utils_gvalue_new_string (const gchar *str)
{
	GValue *gval;

	gval = g_new0 (GValue, 1);
	g_value_init (gval, G_TYPE_STRING);
	g_value_set_string (gval, str);

	return gval;
}

/**
 * zak_utils_gvalue_new_boolean:
 * @b:
 *
 */
GValue
*zak_utils_gvalue_new_boolean (gboolean b)
{
	GValue *gval;

	gval = g_new0 (GValue, 1);
	g_value_init (gval, G_TYPE_BOOLEAN);
	g_value_set_boolean (gval, b);

	return gval;
}

/**
 * zak_utils_gvalue_new_float:
 * @f:
 *
 */
GValue
*zak_utils_gvalue_new_float (gfloat f)
{
	GValue *gval;

	gval = g_new0 (GValue, 1);
	g_value_init (gval, G_TYPE_FLOAT);
	g_value_set_float (gval, f);

	return gval;
}