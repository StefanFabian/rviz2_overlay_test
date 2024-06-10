#ifndef OVERLAY_TEST__VISIBILITY_CONTROL_H_
#define OVERLAY_TEST__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define OVERLAY_TEST_EXPORT __attribute__ ((dllexport))
    #define OVERLAY_TEST_IMPORT __attribute__ ((dllimport))
  #else
    #define OVERLAY_TEST_EXPORT __declspec(dllexport)
    #define OVERLAY_TEST_IMPORT __declspec(dllimport)
  #endif
  #ifdef OVERLAY_TEST_BUILDING_LIBRARY
    #define OVERLAY_TEST_PUBLIC OVERLAY_TEST_EXPORT
  #else
    #define OVERLAY_TEST_PUBLIC OVERLAY_TEST_IMPORT
  #endif
  #define OVERLAY_TEST_PUBLIC_TYPE OVERLAY_TEST_PUBLIC
  #define OVERLAY_TEST_LOCAL
#else
  #define OVERLAY_TEST_EXPORT __attribute__ ((visibility("default")))
  #define OVERLAY_TEST_IMPORT
  #if __GNUC__ >= 4
    #define OVERLAY_TEST_PUBLIC __attribute__ ((visibility("default")))
    #define OVERLAY_TEST_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define OVERLAY_TEST_PUBLIC
    #define OVERLAY_TEST_LOCAL
  #endif
  #define OVERLAY_TEST_PUBLIC_TYPE
#endif

#endif  // OVERLAY_TEST__VISIBILITY_CONTROL_H_
