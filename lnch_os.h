/* See LICENSE for license details. */

/*

Module: lnch_os.h

Description:

    Include operating-system header files.

*/

/* Reverse include guard */
#if defined(INC_LNCH_OS_H)
#error include lnch_os.h once
#endif /* #if defined(INC_LNCH_OS_H) */

#define INC_LNCH_OS_H

/* Include of stdio.h to get sprintf() function. */
#include <stdio.h>

/* Include of stdlib.h to get exit() function. */
#include <stdlib.h>

/* Include of string.h to get memset() function. */
#include <string.h>

/* Include of unistd.h to get execlp() function. */
#include <unistd.h>

/* Include of signal.h to get signal() function. */
#include <signal.h>

/* Include of sys.wait.h to define WNOHANG macro */
#include <sys/wait.h>

/* Include of poll.h to define poll() function */
#include <poll.h>

/* Include of Xlib.h for all X11 definitions, too many to list here */
#include <X11/Xlib.h>

/* Include of Xresource.h for XGetDefault */
#include <X11/Xresource.h>

/* Include of time.h to get clock_gettime() function. */
#include <sys/time.h>

typedef void lnch_avoid_empty_translation_unit;

/* end-of-file: lnch_os.h */
