#pragma once

#ifdef ENABLE_EXPERIMENTAL_MACROS

#define CONCAT(x, y) x ## y
#define X(before,after,arg) before arg ## after
#define Y(arg) arg

// Gives the number of args passed to it
#define PP_NARG(...)    PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...)   PP_ARG_N(__VA_ARGS__)

#define PP_ARG_N( \
        _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,  \
        _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
        _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
        _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
        _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
        _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
        _61,_62,_63,N,...) N

#define PP_RSEQ_N() \
        63,62,61,60,                   \
        59,58,57,56,55,54,53,52,51,50, \
        49,48,47,46,45,44,43,42,41,40, \
        39,38,37,36,35,34,33,32,31,30, \
        29,28,27,26,25,24,23,22,21,20, \
        19,18,17,16,15,14,13,12,11,10, \
        9,8,7,6,5,4,3,2,1,0


/* need extra level to force extra eval */
#define Paste(a,b) a ## b
#define XPASTE(a,b) Paste(a,b)


/* APPLYXn variadic X-Macro by M Joshua Ryan      */
/* Free for all uses. Don't be a jerk.            */
/* I got bored after typing 15 of these.          */
/* You could keep going upto 64 (PPNARG's limit). */
#define PASTEX1 (a) a
#define PASTEX2 (a) a a
#define PASTEX3 (a) a a a
#define PASTEX4 (a) a a a a
#define PASTEX5 (a) a a a a a
#define PASTEX6 (a) a a a a a a
#define PASTEX7 (a) a a a a a a a
#define PASTEX8 (a) a a a a a a a a
#define PASTEX9 (a) a a a a a a a a a

#define USE_1 (a) a
#define USE_2 (a) a, a,
#define USE_3 (a) a, a, a,
#define USE_4 (a) a, a, a, a,
#define USE_5 (a) a, a, a, a, a,
#define USE_6 (a) a, a, a, a, a, a,
#define USE_7 (a) a, a, a, a, a, a, a,
#define USE_8 (a) a, a, a, a, a, a, a, a,
#define USE_9 (a) a, a, a, a, a, a, a, a, a


#define APPLYX1 (before,after,a) X(before,after,a)
#define APPLYX2 (before,after,a,b) X(before,after,a) X(before,after,b)
#define APPLYX3 (before,after,a,b,c) X(before,after,a) X(before,after,b) X(before,after,c)
#define APPLYX4 (before,after,a,b,c,d) X(before,after,a) X(before,after,b) X(before,after,c) X(before,after,d)
#define APPLYX5 (before,after,a,b,c,d,e) X(before,after,a) X(before,after,b) X(before,after,c) X(before,after,d) X(before,after,e)
#define APPLYX6 (before,after,a,b,c,d,e,f) X(before,after,a) X(before,after,b) X(before,after,c) X(before,after,d) X(before,after,e) X(before,after,f)
#define APPLYX7 (before,after,a,b,c,d,e,f,g) X(before,after,a) X(before,after,b) X(before,after,c) X(before,after,d) X(before,after,e) X(before,after,f) X(before,after,g)
#define APPLYX8 (before,after,a,b,c,d,e,f,g,h) X(before,after,a) X(before,after,b) X(before,after,c) X(before,after,d) X(before,after,e) X(before,after,f) X(before,after,g) X(before,after,h)
#define APPLYX9 (before,after,a,b,c,d,e,f,g,h,i) X(before,after,a) X(before,after,b) X(before,after,c) X(before,after,d) X(before,after,e) X(before,after,f) X(before,after,g) X(before,after,h) X(before,after,i)

//#define APPLYY1 (a)                     Y(a)
//#define APPLYY2 (a,b)                   Y(a) Y(b)
//#define APPLYY3 (a,b,c)                 Y(a) Y(b) Y(c)
//#define APPLYY4 (a,b,c,d)               Y(a) Y(b) Y(c) Y(d)
//#define APPLYY5 (a,b,c,d,e)             Y(a) Y(b) Y(c) Y(d) Y(e)
//#define APPLYY6 (a,b,c,d,e,f)           Y(a) Y(b) Y(c) Y(d) Y(e) Y(f)
//#define APPLYY7 (a,b,c,d,e,f,g)         Y(a) Y(b) Y(c) Y(d) Y(e) Y(f) Y(g)
//#define APPLYY8 (a,b,c,d,e,f,g,h)       Y(a) Y(b) Y(c) Y(d) Y(e) Y(f) Y(g) Y(h)
//#define APPLYY9 (a,b,c,d,e,f,g,h,i)     Y(a) Y(b) Y(c) Y(d) Y(e) Y(f) Y(g) Y(h) Y(i)

//#define CONCAT1 (a)                     Y(a)
//#define CONCAT2 (a,b)                   Y(a) Y(b)
//#define CONCAT3 (a,b,c)                 Y(a) Y(b) Y(c)
//#define CONCAT4 (a,b,c,d)               Y(a) Y(b) Y(c) Y(d)
//#define CONCAT5 (a,b,c,d,e)             Y(a) Y(b) Y(c) Y(d) Y(e)
//#define CONCAT6 (a,b,c,d,e,f)           Y(a) Y(b) Y(c) Y(d) Y(e) Y(f)
//#define CONCAT7 (a,b,c,d,e,f,g)         Y(a) Y(b) Y(c) Y(d) Y(e) Y(f) Y(g)
//#define CONCAT8 (a,b,c,d,e,f,g,h)       Y(a) Y(b) Y(c) Y(d) Y(e) Y(f) Y(g) Y(h)
//#define CONCAT9 (a,b,c,d,e,f,g,h,i)     Y(a) Y(b) Y(c) Y(d) Y(e) Y(f) Y(g) Y(h) Y(i)

#define APPLYX_s(M, ...) M(__VA_ARGS__)
#define APPLYX_(M, before, after, ...) M(before, after, __VA_ARGS__)
#define APPLYY_(M, ...) M(__VA_ARGS__)

#define APPLYXn_s(...) APPLYX_s(XPASTE(APPLYX, PP_NARG(__VA_ARGS__)), __VA_ARGS__)
#define APPLYXn(before, after, ...) APPLYX_(XPASTE(APPLYX, PP_NARG(__VA_ARGS__)), before, after, __VA_ARGS__)

#define XUSE(elem, n) USE_ ## n (elem)
#define USE_N(element, times) XUSE(element, times)
// #define NAMESPACES(...) APPLYXn(namespace, {, __VA_ARGS__)
// #define CLOSEXn(times) APPLYX_s(XPASTE(PASTEX, times), })

// #define DUC_CONCAT(x, y) x ## y
// #define DUC_CONCAT(x, ...) x ## __VA_ARGS__
// #define CONCATXN

//#define DUC_CONCAT(...) APPLYY_(XPASTE(APPLYY, PP_NARG(__VA_ARGS__)), __VA_ARGS__)

#endif // ENABLE_EXPERIMENTAL_MACROS
