/*  XMMS2 - X Music Multiplexer System
 *  Copyright (C) 2003, 2004 Peter Alm, Tobias Rundstr�m, Anders Gustafsson
 *
 *  PLUGINS ARE NOT CONSIDERED TO BE DERIVED WORK !!!
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 */

#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h> 

#include <ruby.h>
#include <stdbool.h>

#include "rb_xmmsclient.h"

static VALUE c_add_to_glib_mainloop (VALUE self)
{
	RbXmmsClient *xmms = NULL;

	Data_Get_Struct (self, RbXmmsClient, xmms);

	xmmsc_setup_with_gmain (xmms->real);

	return self;
}

void Init_xmmsclient_glib (void)
{
	VALUE c;
	ID id;

	rb_require ("xmmsclient");
	rb_require ("glib");

	id = rb_intern ("XmmsClient");
	c = rb_const_get (rb_const_get (rb_cModule, id), id);

	rb_define_method (c, "add_to_glib_mainloop",
	                  c_add_to_glib_mainloop, 0);
}
