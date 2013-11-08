/*  =========================================================================
    zyre - API wrapping one Zyre node

    -------------------------------------------------------------------------
    Copyright (c) 1991-2013 iMatix Corporation <www.imatix.com>
    Copyright other contributors as noted in the AUTHORS file.

    This file is part of Zyre, an open-source framework for proximity-based
    peer-to-peer applications -- See http://zyre.org.

    This is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or (at
    your option) any later version.

    This software is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program. If not, see
    <http://www.gnu.org/licenses/>.
    =========================================================================
*/

/*
@header
    The zyre class implements a socket-like interface to one node.
@discuss
@end
*/

#include "zyre_classes.h"

//  ---------------------------------------------------------------------
//  Structure of our class

struct _zyre_t {
    void *pipe;                 //  Pipe through to node
};


//  ---------------------------------------------------------------------
//  Constructor

zyre_t *
zyre_new (zctx_t *ctx)
{
    zyre_t *self = (zyre_t *) zmalloc (sizeof (zyre_t));
    assert (self);

    //  Start node engine and wait for it to be ready
    assert (ctx);
    self->pipe = zthread_fork (ctx, zyre_node_engine, NULL);
    if (self->pipe) {
        char *status = zstr_recv (self->pipe);
        if (strneq (status, "OK"))
            zyre_destroy (&self);
        zstr_free (&status);
    }
    else {
        free (self);
        self = NULL;
    }
    return self;
}


//  ---------------------------------------------------------------------
//  Destructor

void
zyre_destroy (zyre_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zyre_t *self = *self_p;
        free (self);
        *self_p = NULL;
    }
}

//  ---------------------------------------------------------------------
//  Receive next message from node
//  Returns zmsg_t object, or NULL if interrupted

zmsg_t *
zyre_recv (zyre_t *self)
{
    assert (self);
    zmsg_t *msg = zmsg_recv (self->pipe);
    return msg;
}


//  ---------------------------------------------------------------------
//  Join a group

int
zyre_join (zyre_t *self, const char *group)
{
    assert (self);
    zstr_sendm (self->pipe, "JOIN");
    zstr_send  (self->pipe, group);
    return 0;
}


//  ---------------------------------------------------------------------
//  Leave a group

int
zyre_leave (zyre_t *self, const char *group)
{
    assert (self);
    zstr_sendm (self->pipe, "LEAVE");
    zstr_send  (self->pipe, group);
    return 0;
}


//  ---------------------------------------------------------------------
//  Send message to single peer; peer ID is first frame in message
//  Destroys message after sending

int
zyre_whisper (zyre_t *self, zmsg_t **msg_p)
{
    assert (self);
    zstr_sendm (self->pipe, "WHISPER");
    zmsg_send (msg_p, self->pipe);
    return 0;
}


//  ---------------------------------------------------------------------
//  Send message to a group of peers

int
zyre_shout (zyre_t *self, zmsg_t **msg_p)
{
    assert (self);
    zstr_sendm (self->pipe, "SHOUT");
    zmsg_send (msg_p, self->pipe);
    return 0;
}


//  ---------------------------------------------------------------------
//  Return node handle, for polling

void *
zyre_socket (zyre_t *self)
{
    assert (self);    
    return self->pipe;
}


//  ---------------------------------------------------------------------
//  Set node property value

void
zyre_set (zyre_t *self, char *name, char *format, ...)
{
    assert (self);
    va_list argptr;
    va_start (argptr, format);
    char *string = zsys_vprintf (format, argptr);
    va_end (argptr);

    zstr_sendm (self->pipe, "SET");
    zstr_sendm (self->pipe, name);
    zstr_send  (self->pipe, string);
    free (string);
}


//  --------------------------------------------------------------------------
//  Self test of this class

void
zyre_test (bool verbose)
{
    printf (" * zyre: ");

    //  @selftest
    zctx_t *ctx = zctx_new ();
    zyre_t *zyre = zyre_new (ctx);
    zyre_destroy (&zyre);
    zctx_destroy (&ctx);
    //  @end
    printf ("OK\n");
}
