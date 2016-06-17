/* See LICENSE for license details. */

/*

Module: lnch_tree.c

Description:

    Enumerate all child windows of root.

*/

/* Operating system */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Module */
#include "lnch_tree.h"

static
void
lnch_tree_process_window(
    struct lnch_ctxt const * const p_ctxt,
    lnch_tree_callback * const p_enum_callback,
    void * const p_callback_data,
    Window const i_window_id)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_tree_callback_args o_callback_args;

    o_callback_args.p_ctxt = p_ctxt;

    o_callback_args.p_callback_data = p_callback_data;

    o_callback_args.i_window_id = i_window_id;

    if (XGetWindowAttributes(
            p_display->dpy,
            i_window_id,
            &o_callback_args.o_window_attr))
    {
        if (o_callback_args.o_window_attr.map_state == IsViewable)
        {
            (*p_enum_callback)(
                &o_callback_args);
        }
    }
}

struct lnch_tree_window_list
{
    Window const * a_window_id;

    unsigned int i_window_count;

};

static
void
lnch_tree_process_window_list(
    struct lnch_ctxt const * const p_ctxt,
    lnch_tree_callback * const p_enum_callback,
    void * const p_callback_data,
    struct lnch_tree_window_list const * const p_window_list)
{
    unsigned int i_window_index;

    for (i_window_index = 0; i_window_index < p_window_list->i_window_count; i_window_index++)
    {
        Window const i_window_id = p_window_list->a_window_id[i_window_index];

        lnch_tree_process_window(
            p_ctxt,
            p_enum_callback,
            p_callback_data,
            i_window_id);
    }
}

static
char
lnch_tree_init_window_list(
    struct lnch_ctxt const * const p_ctxt,
    struct lnch_tree_window_list * const p_window_list)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    Window i_dummy_window_1;

    Window i_dummy_window_2;

    p_window_list->a_window_id = NULL;

    p_window_list->i_window_count = 0u;

    return (char)(0 != XQueryTree(
            p_display->dpy,
            p_display->root,
            &i_dummy_window_1,
            &i_dummy_window_2,
            (Window * *)(&p_window_list->a_window_id),
            &p_window_list->i_window_count));
}

static
void
lnch_tree_cleanup_window_list(
    struct lnch_tree_window_list * const p_window_list)
{
    if (p_window_list->a_window_id)
    {
        XFree((void *)(p_window_list->a_window_id));

        p_window_list->a_window_id = NULL;
    }

    p_window_list->i_window_count = 0u;
}

void lnch_tree_enum(
    struct lnch_ctxt const * const p_ctxt,
    lnch_tree_callback * const p_enum_callback,
    void * const p_callback_data)
{
    struct lnch_tree_window_list o_window_list;

    if (lnch_tree_init_window_list(p_ctxt, &o_window_list))
    {
        if (o_window_list.a_window_id && o_window_list.i_window_count)
        {
            lnch_tree_process_window_list(
                p_ctxt,
                p_enum_callback,
                p_callback_data,
                &o_window_list);
        }

        lnch_tree_cleanup_window_list(&o_window_list);
    }
} /* lnch_tree_enum */

/* end-of-file: lnch_tree.c */
