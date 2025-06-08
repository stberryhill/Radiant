
#ifndef RADIANT_API_H
#define RADIANT_API_H

#ifdef RADIANT_STATIC_DEFINE
#  define RADIANT_API
#  define RADIANT_NO_EXPORT
#else
#  ifndef RADIANT_API
#    ifdef Radiant_EXPORTS
        /* We are building this library */
#      define RADIANT_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define RADIANT_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef RADIANT_NO_EXPORT
#    define RADIANT_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef RADIANT_DEPRECATED
#  define RADIANT_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef RADIANT_DEPRECATED_EXPORT
#  define RADIANT_DEPRECATED_EXPORT RADIANT_API RADIANT_DEPRECATED
#endif

#ifndef RADIANT_DEPRECATED_NO_EXPORT
#  define RADIANT_DEPRECATED_NO_EXPORT RADIANT_NO_EXPORT RADIANT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RADIANT_NO_DEPRECATED
#    define RADIANT_NO_DEPRECATED
#  endif
#endif

#endif /* RADIANT_API_H */
