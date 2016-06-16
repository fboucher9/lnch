/* See LICENSE for license details. */

/*

Module: lnch_feature_xerror.h

Description:

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_XERROR_H)
#error include lnch_feature_xerror.h once
#endif /* #if defined(INC_LNCH_FEATURE_XERROR_H) */

#define INC_LNCH_FEATURE_XERROR_H

/* This file should only be included when feature is enabled. */
#if !defined(LNCH_FEATURE_XERROR)
#error xerror feature not enabled
#endif /* #if !defined(LNCH_FEATURE_XERROR) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

void
lnch_feature_xerror_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev);

/* end-of-file: lnch_feature_xerror.h */
