/* config.h.  Generated by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Default audio sink */
#define DEFAULT_AUDIOSINK "autoaudiosink"

/* Default audio source */
#define DEFAULT_AUDIOSRC "alsasrc"

/* Default video sink */
#define DEFAULT_VIDEOSINK "autovideosink"

/* Default video source */
#define DEFAULT_VIDEOSRC "v4lsrc"

/* Default visualizer */
#define DEFAULT_VISUALIZER "goom"

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#undef ENABLE_NLS

/* gettext package name */
#define GETTEXT_PACKAGE "gst-plugins-good-0.10"

/* PREFIX - specifically added for Windows for easier moving */
#define PREFIX "C:\\gstreamer"

/* Defined if gcov is enabled to force a rebuild due to config.h changing */
/* #undef GST_GCOV_ENABLED */

/* Default errorlevel to use */
#define GST_LEVEL_DEFAULT GST_LEVEL_ERROR

/* GStreamer license */
#define GST_LICENSE "LGPL"

/* package name in plugins */
#define GST_PACKAGE_NAME "GStreamer Good Plug-ins source release"

/* package origin */
#define GST_PACKAGE_ORIGIN "Unknown package origin"

/* support for features: aasink */
#define HAVE_AALIB 

/* support for features: skeldec cmmlenc cmmldec */
#define HAVE_ANNODEX 

/* support for features: cairo */
#define HAVE_CAIRO 

/* support for features: cdio */
#define HAVE_CDIO 

/* Define if the host CPU is an Alpha */
/* #undef HAVE_CPU_ALPHA */

/* Define if the host CPU is an ARM */
/* #undef HAVE_CPU_ARM */

/* Define if the host CPU is a HPPA */
/* #undef HAVE_CPU_HPPA */

/* Define if the host CPU is an x86 */
#define HAVE_CPU_I386 1

/* Define if the host CPU is a IA64 */
/* #undef HAVE_CPU_IA64 */

/* Define if the host CPU is a M68K */
/* #undef HAVE_CPU_M68K */

/* Define if the host CPU is a MIPS */
/* #undef HAVE_CPU_MIPS */

/* Define if the host CPU is a PowerPC */
/* #undef HAVE_CPU_PPC */

/* Define if the host CPU is a S390 */
/* #undef HAVE_CPU_S390 */

/* Define if the host CPU is a SPARC */
/* #undef HAVE_CPU_SPARC */

/* Define if the host CPU is a x86_64 */
/* #undef HAVE_CPU_X86_64 */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#undef HAVE_DCGETTEXT

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef HAVE_DLFCN_H

/* support for features: dv1394src */
#define HAVE_DV1394 

/* support for features: esdsink */
#define HAVE_ESD 

/* support for features: */
#define HAVE_EXTERNAL 

/* FIONREAD ioctl found in sys/filio.h */
/* #undef HAVE_FIONREAD_IN_SYS_FILIO */

/* FIONREAD ioctl found in sys/ioclt.h */
#define HAVE_FIONREAD_IN_SYS_IOCTL 1

/* support for features: flacenc flacdec */
#define HAVE_FLAC 

/* support for features: */
#define HAVE_GCONF 

/* support for features: */
#define HAVE_GCONFTOOL 

/* support for features: gdkpixbufsrc */
#define HAVE_GDK_PIXBUF 

/* Define to 1 if you have the `getpagesize' function. */
#undef HAVE_GETPAGESIZE

/* Define if the GNU gettext() function is already present or preinstalled. */
#undef HAVE_GETTEXT

/* support for features: */
#define HAVE_HAL 

/* Define if you have the iconv() function. */
/* #undef HAVE_ICONV */

/* Define to 1 if you have the <inttypes.h> header file. */
#undef HAVE_INTTYPES_H

/* support for features: jpegenc jpegdec */
#define HAVE_JPEG 

/* support for features: ladspa */
#define HAVE_LADSPA 

/* support for features: libcaca */
#define HAVE_LIBCACA 

/* support for features: dvdec */
#define HAVE_LIBDV 

/* support for features: pngenc */
#define HAVE_LIBPNG 

/* Define if you have C99's lrint function. */
#define HAVE_LRINT 1

/* Define if you have C99's lrintf function. */
#define HAVE_LRINTF 1

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H

/* Define to 1 if you have a working `mmap' system call. */
#undef HAVE_MMAP

/* Define to 1 if you have the <netinet/in.h> header file. */
#undef HAVE_NETINET_IN_H

/* support for features: osssrc osssink */
#define HAVE_OSS 

/* Define if OSS includes are in /machine/ */
/* #undef HAVE_OSS_INCLUDE_IN_MACHINE */

/* Define if OSS includes are in / */
/* #undef HAVE_OSS_INCLUDE_IN_ROOT */

/* Define if OSS includes are in /sys/ */
#define HAVE_OSS_INCLUDE_IN_SYS 

/* Define if RDTSC is available */
#undef HAVE_RDTSC

/* support for features: shout2send */
#define HAVE_SHOUT2 

/* support for features: speex */
#define HAVE_SPEEX 

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* support for features: sunaudiosink */
/* #undef HAVE_SUNAUDIO */

/* Define to 1 if you have the <sys/socket.h> header file. */
#undef HAVE_SYS_SOCKET_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* support for features: taglib */
#define HAVE_TAGLIB 

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* Define if valgrind should be used */
#undef HAVE_VALGRIND

/* Define to 1 if you have the <winsock2.h> header file. */
#define HAVE_WINSOCK2_H 1

/* support for features: ximagesrc */
#define HAVE_X 

/* support for features: */
#define HAVE_XSHM 

/* support for features: */
#define HAVE_ZLIB 

/* gettext locale dir */
#define LOCALEDIR PREFIX "\\share\\locale"

/* Name of package */
#define PACKAGE "gst-plugins-good"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://bugzilla.gnome.org/enter_bug.cgi?product=GStreamer"

/* Define to the full name of this package. */
#define PACKAGE_NAME "GStreamer Good Plug-ins"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "GStreamer Good Plug-ins 0.10.7"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "gst-plugins-good"

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.10.7"

/* Define the plugin directory */
#ifdef _DEBUG
#  define PLUGINDIR PREFIX "\\debug\\lib\\gstreamer-0.10"
#else
#  define PLUGINDIR PREFIX "\\lib\\gstreamer-0.10"
#endif

/* defined if speex 1.0.x API detected */
#define SPEEX_1_0 1

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* Version number of package */
#define VERSION "0.10.7"

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef WORDS_BIGENDIAN */

/* Define to 1 if the X Window System is missing or not being used. */
/* #undef X_DISPLAY_MISSING */

/* Define socklen_t as it seems to be not defined in default VS setup */
#ifndef socklen_t
typedef int socklen_t;
#endif