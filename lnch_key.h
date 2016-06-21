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

/*

Structure: lnch_key_descriptor

Description:

    Information about a hotkey.

*/
struct lnch_key_descriptor
{
    unsigned int i_key_code;

    unsigned int i_mod_mask;

}; /* struct lnch_key_descriptor */

/* Interface: */

void
lnch_key_parse(
    struct lnch_ctxt const * const p_ctxt,
    char const * const p_key_string,
    struct lnch_key_descriptor * const p_desc);

unsigned int
lnch_key_grab(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id,
    char const * const p_key_string);

/* end-of-file: lnch_key.h */
