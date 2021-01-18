#define FWDDECL_INTERFACE(name) \
    typedef struct ##name_Vtbl_s ##name_Vtbl; \
    typedef struct ##name_Fns_s ##name_Fns; \
    typedef struct ##name_s ##name

#define DEFINE_INTERFACE(name) \
    typedef struct ##name_Vtbl_s ##name_Vtbl; \
    typedef struct ##name_Fns_s ##name_Fns; \
    typedef struct ##name_s ##name; \
    struct ##name_fns

#define ENDDEFINE_INTERFACE(name) \
    ; \
    struct ##name_Vtbl_s; \
    struct ##name_s { \
        ##name_Vtbl const * const _vtbl; \
    }; \
    struct ##name_Vtbl { \
        ##name_Vtbl const * const token; \
        size_t adj; \
        ##name_Fns fns; \
    }; \
    #define ##name_new(self, vtbl) \
        { uint8_t *s = (uint8_t *)(self); \
        ##name_Vtbl const **p = (##name_Vtbl const **)(s + offsetof(##name, _vtbl)); \
        *p = (vtbl); }

#define ENDDEFINE_INTERFACE  };
//    void ##name_new(##name *const self, ##name_Vtbl const *const vtbl)

#define DECLARE_INTERFACE(name) struct ##name_Vtbl ##name_;

#define DEF_
