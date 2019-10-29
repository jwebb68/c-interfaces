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

Obviously in C I'm not going to get the obj.method syntax unless I put func
pointers into a struct that exists in ram, which I don't want.
So, method calls would devolve into simple thunkers/wrappers to encapsulate how
it's implemented.
Also, want to return a result/error code to check on, which forces use of
out-values, unless a Result struct is used..
(poss nicer, but more typing/mantenance of a separate struct and not idiomatic C)

 {
    // object o = object::new();
    Object o = Object_new();

    // interface1 i1 = (interface1)o.query_interface(interface1::id)
    Interface1 *iface1;
    Result res;
    res = Object_query_interface(&o, &Interface1_IID, (void **)&iface1);
    if (Result_is_error(res)) {
     ... do error handling here..
    }

    // v = i1.get_value()
    Type v;
    res = Interace1_get_value(iface1, &v);
    if (Result_is_error(res)) {
     ... do error handling here..
    }
 }


Issues
------
The issue is the redirection through the vtbl for each interface
The object inst lives in ram.
The vtbl pointer therefore is in ram since it is in the object struct and so can be corrupted.
which would cause bad stuff to happen.
This is mitigated by using a guard in the vtbl, if the guard does not match expected - fail.
maybe this should be panic..
But even then, malicious actors could match the vbtl structure and fool this.

adding an interface is a very labourious affair,
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
Even using a Result struct would still leave you with a void *, requiring casting.
(Oh for templates/generics and link-time optimisation (code deduping)).
