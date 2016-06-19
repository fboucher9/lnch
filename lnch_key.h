/* See LICENSE for license details. */

/*

Module: lnch_key.h

Description:

    Register of hotkey for all features.

*/

/* Reverse include guard */
#if defined(INC_LNCH_KEY_H)
#error include lnch_key.h once
#endif /* #if defined(INC_LNCH_KEY_H) */

#define INC_LNCH_KEY_H

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

unsigned int
lnch_key_grab(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id,
    char const * const p_key_string);

/* end-of-file: lnch_key.h */
