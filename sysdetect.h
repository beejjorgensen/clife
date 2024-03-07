#if !defined(__STDC_NO_THREADS__) && __STDC_VERSION__ >= 201112L
#define HAS_THREADS
#endif

#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#define UNIXLIKE
#endif


