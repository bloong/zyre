/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
package org.zeromq.zyre;

public class ZyreEvent implements AutoCloseable {
    static {
        try {
            System.loadLibrary ("zyrejni");
        }
        catch (Exception e) {
            System.exit (-1);
        }
    }
    long self;

    /*
    Constructor: receive an event from the zyre node, wraps zyre_recv.
    The event may be a control message (ENTER, EXIT, JOIN, LEAVE) or  
    data (WHISPER, SHOUT).                                            
    */
    native static long __init (long self);
    public ZyreEvent (long self) {
        /*  TODO: if __init fails, self is null...  */
        self = __init (self);
    }
    /*
    Destructor; destroys an event instance
    */
    native static void __destroy (long self);
    @Override
    public void close () {
        __destroy (self);
        self = 0;
    }
    /*
    Returns event type, which is a zyre_event_type_t
    */
    native static int __type (long self);
    public int type (long self) {
        return ZyreEvent.__type (self);
    }
    /*
    Return the sending peer's id as a string
    */
    native static String __sender (long self);
    public String sender (long self) {
        return ZyreEvent.__sender (self);
    }
    /*
    Return the sending peer's public name as a string
    */
    native static String __name (long self);
    public String name (long self) {
        return ZyreEvent.__name (self);
    }
    /*
    Return the sending peer's ipaddress as a string
    */
    native static String __address (long self);
    public String address (long self) {
        return ZyreEvent.__address (self);
    }
    /*
    Returns the event headers, or NULL if there are none
    */
    native static long __headers (long self);
    public long headers (long self) {
        return ZyreEvent.__headers (self);
    }
    /*
    Returns value of a header from the message headers   
    obtained by ENTER. Return NULL if no value was found.
    */
    native static String __header (long self, String name);
    public String header (long self, String name) {
        return ZyreEvent.__header (self, name);
    }
    /*
    Returns the group name that a SHOUT event was sent to
    */
    native static String __group (long self);
    public String group (long self) {
        return ZyreEvent.__group (self);
    }
    /*
    Returns the incoming message payload (currently one frame)
    */
    native static long __msg (long self);
    public long msg (long self) {
        return ZyreEvent.__msg (self);
    }
    /*
    Self test of this class
    */
    native static void __test (boolean verbose);
    public void test (boolean verbose) {
        ZyreEvent.__test (verbose);
    }
}