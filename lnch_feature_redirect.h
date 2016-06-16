/* See LICENSE for license details. */

/*

Module: lnch_feature_redirect.h

Description:

    Redirection of X substructure events to fix input focus and also
    to modify attributes of new windows.

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_REDIRECT_H)
#error include lnch_feature_redirect.h once
#endif /* #if defined(INC_LNCH_FEATURE_REDIRECT_H) */

#define INC_LNCH_FEATURE_REDIRECT_H

/* Verify that feature is enabled. */
#if !defined(LNCH_FEATURE_REDIRECT)
#error redirect feature not enabled.
#endif /* #if !defined(LNCH_FEATURE_REDIRECT) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

void
lnch_feature_redirect_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * p_event);

/* end-of-file: lnch_feature_redirect.h */
