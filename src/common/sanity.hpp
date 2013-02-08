/// return wrappers for unexpected NULL pointers
#ifndef SANITY_HPP
#define SANITY_HPP

# ifndef __cplusplus
#  error "Please compile in C++ mode"
# endif // __cplusplus

# if __GNUC__ < 4
#  error "Your compiler is absolutely ancient. You have no chance ..."
# endif // __GNUC__ < 4

/// Convert type assumptions to use the standard types here
# include <cstdint>
/// size_t, NULL
# include <cstddef>

# if __GNUC__ == 4
// clang identifies as GCC 4.2, but is mostly okay.
// Until a bug-free release of it happens, though, I won't recommend it.
// (patched) clang 3.1 would be the requirement
#  if __GNUC_MINOR__ < 6 && !defined(__clang__)
#   error "Please upgrade to at least GCC 4.6"
#  endif // __GNUC_MINOR__ < 6 && !defined(__clang__)
// temporary workaround for library issues
// since __GLIBCXX__ is hard to use
#  if __GNUC_MINOR__ == 6
#   define WORKAROUND_GCC46_COMPILER
#  endif // __GNUC_MINOR__ == 6
#  ifdef __GLIBCXX__
// versions of libstdc++ from gcc
// 4.6.0, 4.6.1, 4.6.2, 4.6.3
#   if __GLIBCXX__ == 20110325  \
    || __GLIBCXX__ == 20110627  \
    || __GLIBCXX__ == 20111026  \
    || __GLIBCXX__ == 20120301  \
    || __GLIBCXX__ == 20121127  // prerelease in Debian wheezy
#    define WORKAROUND_GCC46_LIBRARY
#   endif // __GLIBCXX__ == ...
#  endif // defined __GLIBCXX__
#  if defined(WORKAROUND_GCC46_COMPILER) \
    && !defined(WORKAROUND_GCC46_LIBRARY)
#   error "Unknown gcc 4.6.x release"
#  endif // compiler and not library
# endif // __GNUC__ == 4

# ifndef __i386__
// Known platform dependencies:
// endianness for the [RW]FIFO.* macros
// possibly, some signal-handling
#  error "Unsupported platform"
# endif // not __i386__

# ifdef __x86_64__
// I'm working on it - I know there are some pointer-size assumptions.
#  error "Sorry, this code is believed not to be 64-bit safe"
#  error "please compile with -m32"
# endif // __x86_64__

#endif // SANITY_HPP