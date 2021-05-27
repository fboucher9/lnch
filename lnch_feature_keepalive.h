/* See LICENSE for license details. */

/*

Module: lnch_feature_keepalive.h

Description:

    Keepalive of X connection.

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_KEEPALIVE_H)
#error include lnch_feature_keepalive.h once
#endif /* #if defined(INC_LNCH_FEATURE_KEEPALIVE_H) */

#define INC_LNCH_FEATURE_KEEPALIVE_H

/* Verify configuration */
#if !defined(LNCH_FEATURE_KEEPALIVE)
#error keepalive feature not enabled
#endif /* #if !defined(LNCH_FEATURE_KEEPALIVE) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

/* All-in-one feature entry point */
void lnch_feature_keepalive_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent const * const pev);

/* end-of-file: lnch_feature_keepalive.h */
