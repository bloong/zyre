/*  =========================================================================
    zyre Node.js binding header file

    Copyright (c) the Contributors as noted in the AUTHORS file.

    This file is part of Zyre, an open-source framework for proximity-based
    peer-to-peer applications -- See http://zyre.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
    =========================================================================
*/

#ifndef ZYRE_BINDING_H_INCLUDED
#define ZYRE_BINDING_H_INCLUDED

#define ZYRE_BUILD_DRAFT_API

#include "../../../czmq/bindings/nodejs/binding.h"
#include "zyre.h"
#include "nan.h"

using namespace v8;
using namespace Nan;

class Zyre: public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT (Init);
        explicit Zyre (const char *name);
        explicit Zyre (zyre_t *self);
        zyre_t *self;
    private:
        ~Zyre ();
    static Nan::Persistent <Function> &constructor ();

    static NAN_METHOD (New);
    static NAN_METHOD (destroy);
    static NAN_METHOD (defined);
    static NAN_METHOD (_uuid);
    static NAN_METHOD (_name);
    static NAN_METHOD (_set_name);
    static NAN_METHOD (_set_header);
    static NAN_METHOD (_set_verbose);
    static NAN_METHOD (_set_port);
    static NAN_METHOD (_set_evasive_timeout);
    static NAN_METHOD (_set_expired_timeout);
    static NAN_METHOD (_set_interval);
    static NAN_METHOD (_set_interface);
    static NAN_METHOD (_set_endpoint);
    static NAN_METHOD (_set_zcert);
    static NAN_METHOD (_gossip_bind);
    static NAN_METHOD (_gossip_connect);
    static NAN_METHOD (_gossip_connect_curve);
    static NAN_METHOD (_start);
    static NAN_METHOD (_stop);
    static NAN_METHOD (_join);
    static NAN_METHOD (_leave);
    static NAN_METHOD (_recv);
    static NAN_METHOD (_whisper);
    static NAN_METHOD (_shout);
    static NAN_METHOD (_whispers);
    static NAN_METHOD (_shouts);
    static NAN_METHOD (_peers);
    static NAN_METHOD (_peers_by_group);
    static NAN_METHOD (_own_groups);
    static NAN_METHOD (_peer_groups);
    static NAN_METHOD (_peer_address);
    static NAN_METHOD (_peer_header_value);
    static NAN_METHOD (_require_peer);
    static NAN_METHOD (_socket);
    static NAN_METHOD (_print);
    static NAN_METHOD (_version);
    static NAN_METHOD (_test);
};

class ZyreEvent: public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT (Init);
        explicit ZyreEvent (zyre_t *node);
        explicit ZyreEvent (zyre_event_t *self);
        zyre_event_t *self;
    private:
        ~ZyreEvent ();
    static Nan::Persistent <Function> &constructor ();

    static NAN_METHOD (New);
    static NAN_METHOD (destroy);
    static NAN_METHOD (defined);
    static NAN_METHOD (_type);
    static NAN_METHOD (_peer_uuid);
    static NAN_METHOD (_peer_name);
    static NAN_METHOD (_peer_addr);
    static NAN_METHOD (_headers);
    static NAN_METHOD (_header);
    static NAN_METHOD (_group);
    static NAN_METHOD (_msg);
    static NAN_METHOD (_get_msg);
    static NAN_METHOD (_print);
    static NAN_METHOD (_test);
};

#endif
