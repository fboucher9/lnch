/* See LICENSE for license details. */

/*

Module: lnch_cfg.h

Description:

    Compile-time configuration options.

*/

/* Reverse include guard */
#if defined(INC_LNCH_CFG_H)
#error include lnch_cfg.h
#endif /* #if defined(INC_LNCH_CFG_H) */

#define INC_LNCH_CFG_H

/* Enable move and resize via mouse */
#define LNCH_FEATURE_MOVESIZE

/* Enable extra code that does launch of children */
#define LNCH_FEATURE_CHILD

/* Enable hotkeys used to position client windows */
#define LNCH_FEATURE_GRID

/* Enable code that adds 1 pixel border to each client window */
#define LNCH_FEATURE_BORDER

/* Enable hotkeys used to change focus of client window */
#define LNCH_FEATURE_FOCUS

/* Enable substructure redirection to fix bug with Firefox */
#define LNCH_FEATURE_REDIRECT

/* Enable code that handles X errors */
#define LNCH_FEATURE_XERROR

/* Enable snap to grid using mouse button #2 */
#define LNCH_FEATURE_BUTTON2

/* Enable keepalive of X connection */
#define LNCH_FEATURE_KEEPALIVE

/* end-of-file: lnch_cfg.h */
