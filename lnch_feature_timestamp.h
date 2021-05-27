/* See LICENSE for license details. */

/*

Module: lnch_feature_timestamp.h

Description:

    Log start and stop time into a file.

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_TIMESTAMP_H)
#error include lnch_feature_timestamp.h once
#endif /* #if defined(INC_LNCH_FEATURE_TIMESTAMP_H) */

#define INC_LNCH_FEATURE_TIMESTAMP_H

/* Verify configuration */
#if !defined(LNCH_FEATURE_TIMESTAMP)
#error timestamp feature not enabled
#endif /* #if !defined(LNCH_FEATURE_TIMESTAMP) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

/* All-in-one feature entry point */
void lnch_feature_timestamp_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent const * const pev);

/* end-of-file: lnch_feature_timestamp.h */

