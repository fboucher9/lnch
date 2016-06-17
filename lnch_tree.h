/* See LICENSE for license details. */

/*

Module: lnch_tree.h

Description:

    Enumerate all child windows of root.

*/

/* Reverse include guard */
#if defined(INC_LNCH_TREE_H)
#error include lnch_tree.h once
#endif /* #if defined(INC_LNCH_TREE_H) */

#define INC_LNCH_TREE_H

/* Predefine context handle */
struct lnch_ctxt;

/* Define a structure for window information */
struct lnch_tree_callback_args
{
    struct lnch_ctxt const * p_ctxt;

    void * p_callback_data;

    Window i_window_id;

    XWindowAttributes o_window_attr;

}; /* struct lnch_tree_descriptor */

/* Define a callback function type */
typedef void (lnch_tree_callback)(
    struct lnch_tree_callback_args const * const p_desc);

/* Interface: */

void lnch_tree_enum(
    struct lnch_ctxt const * const p_ctxt,
    lnch_tree_callback * const p_enum_callback,
    void * const p_callback_data);

/* end-of-file: lnch_tree.h */
