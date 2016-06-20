/* See LICENSE for license details. */

/*

Module: lnch_feature_child.c

Description:

    Launch of child process via hotkey.

*/

/* Include operating-system header files */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

/* Verify configuration */
#if defined(LNCH_FEATURE_CHILD)

/* Module */
#include "lnch_feature_child.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Key */
#include "lnch_key.h"

/* Options */
#include "lnch_opts.h"

/* Define a list of strings that need to be translated into key codes */
static unsigned int kc_x = 0u;

/* Two in one function, install a SIGCHLD handler and process a SIGCHLD signal.
This function is required because we create child processes via the fork and
execlp functions.  The SIGCHLD handler will do cleanup of zombie processes.  */
static void lnch_feature_child_sigchld(int unused)
{
    /* Unused parameter */
    (void)(unused);

    /* Register a signal handler called for each terminated child process */
    if (signal(SIGCHLD, lnch_feature_child_sigchld) == SIG_ERR) exit(1);

    /* Wait for child process to be completely terminated */
    while (0 < waitpid(-1, NULL, WNOHANG));

} /* lnch_feature_child_sigchld() */

/*

Function: lnch_feature_child_close_x

Description:

    Close the X connection socket, it must be reopened by child process.  All
    other file descriptors may be inherited such as stdin, stdout and stderr.

*/
static
void
lnch_feature_child_close_x(
    struct lnch_ctxt const * const p_ctxt)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if (p_display->dpy)
    {
        close(ConnectionNumber(p_display->dpy));
    }
} /* lnch_feature_child_close_x() */

/*

Function: lnch_feature_child_exec

Description:

    Call execlp() for the configured child process name.  This must be called
    from after a fork() or else you will lose your window manager.

*/
static
void
lnch_feature_child_exec(
    struct lnch_ctxt const * const p_ctxt)
{
    /* Release X connection */
    lnch_feature_child_close_x(p_ctxt);

    /* Create a new process group */
    setsid();

    {
        struct lnch_opts const * const p_opts = p_ctxt->p_opts;

        execvp((char *)(p_opts->p_exec_child[0]), (char * *)(p_opts->p_exec_child));
    }

    /* If launch of child fails, exit the fork */
    exit(EXIT_FAILURE);

} /* lnch_feature_child_exec() */

/*

Function: lnch_feature_child_key_spawn

Description:

    The hotkey for spawn of child process has been triggered.  Spawn the
    child process by doing a fork() and execlp() sequence.

*/
static
void
lnch_feature_child_key_spawn(
    struct lnch_ctxt const * const p_ctxt)
{
    if (!fork())
    {
        lnch_feature_child_exec(p_ctxt);
    }
} /* lnch_feature_child_key_spawn() */

/*

Function: lnch_feature_child_key_press

Description:

    Handle the KeyPress X event.  Detect which hotkey was pressed and dispatch
    to correspond function.

*/
static
void
lnch_feature_child_key_press(
    struct lnch_ctxt const * const p_ctxt,
    XEvent const * const pev)
{
    if (kc_x == pev->xkey.keycode)
    {
        lnch_feature_child_key_spawn(p_ctxt);
    }
} /* lnch_feature_child_key_press() */

/*

Function: lnch_feature_child_dispatch

Description:

    Dispatch of X events.  Detect type of X event and dispatch to correspond
    function.

*/
static
void
lnch_feature_child_dispatch(
    struct lnch_ctxt const * const p_ctxt,
    XEvent const * const pev)
{
    /* Detect that a keyboard shortcut has been pressed */
    if (KeyPress == pev->type)
    {
        lnch_feature_child_key_press(p_ctxt, pev);
    }
} /* lnch_feature_child_dispatch() */

/*

Function: lnch_feature_child_init

Description:

    Do initialization of feature.

*/
static
void
lnch_feature_child_init(
    struct lnch_ctxt const * const p_ctxt)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_opts const * const p_opts = p_ctxt->p_opts;

    lnch_feature_child_sigchld(0);

    /* Grab keys for root window */
    kc_x = lnch_key_grab(p_ctxt, p_display->root, p_opts->p_key_child);

} /* lnch_feature_child_init() */

/*

Function: lnch_feature_child_event

Description:

    All-in-one entry point for feature.

*/
void
lnch_feature_child_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent const * const pev)
{
    if (pev)
    {
        lnch_feature_child_dispatch(p_ctxt, pev);
    }
    else
    {
        lnch_feature_child_init(p_ctxt);
    }
} /* lnch_feature_child_event() */

#endif /* #if defined(LNCH_FEATURE_CHILD) */

/* end-of-file: lnch_feature_child.c */
