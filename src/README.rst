Introduction
=============
an experiment/research into implementing interfaces in C
and possible reasons to not do it like this.

what I want::

    interface interface1 {
        get_value();
        set_value(value);
        //
        query-interface(interfaceid);
    }

    interface interface1 {
        get_value();
        set_value(value);
        get_objects();
        set_objects(value);
        //
        query-interface(interfaceid);
    }

    object implements interface1, interface2 {

    }


    {
    object o = object::new();
    interface1 i1 = (interface1)o.query_interface(interface1::id)
    v = i1.get_value()
    }

Issues
------
The issue is the redirection through the vtbl for each interface
The object inst lives in ram.
The vtbl pointer therefore is in ram since it is in the object struct and so can be corrupted.
which would cause bad stuff to happen.
