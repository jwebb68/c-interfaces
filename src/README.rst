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

note, no object inheritance, use composition + interfaces instead(?)

Issues
------
The issue is the redirection through the vtbl for each interface
The object inst lives in ram.
The vtbl pointer therefore is in ram since it is in the object struct and so can be corrupted.
which would cause bad stuff to happen.
This is mitigated by using a guard in the vtbl, if the guard does not match expected - fail.
maybe this should be panic..

adding an interface is a very labourous affair,
needing a fair amount of copy/paste (mainly due to type perservation of interface)
however, some of this can be mitigated with helper funcs.

adding a method to an interface is also painful.
for each method added, it requires:
- 3+1 additions in the interface defn
- 3 additions to each class implementing
- most are cut/paste due to type preservation.
- some possible use of helper funcs.

The interface ptrs from query_interface are returned via void **, which is nasty.
as such, the interface ptrs lose const-ness.
typeness is still needed to call functions, so you're forced to preserve that aspect of it.
