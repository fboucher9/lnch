/* See LICENSE for license details. */

/*

Module: lnch_feature_timestamp.c

Description:

    Log start and stop time into a file.

*/

/* Operating system */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_TIMESTAMP)

/* Timestamp feature */
#include "lnch_feature_timestamp.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Options */
#include "lnch_opts.h"

static char g_file_name[256u];

/*

Function: lnch_feature_timestamp_report

Description:

    Append a line to timestamp file.

*/
static
void
lnch_feature_timestamp_report(
    char const * p_message)
{
    FILE * p_file_handle = 0;

    p_file_handle = fopen(g_file_name, "a");

    if (p_file_handle)
    {
        struct tm * p_local_time_info = 0;

        struct timeval o_now;

        gettimeofday(&o_now, 0);

        p_local_time_info = localtime(&o_now.tv_sec);

        if (p_local_time_info)
        {
            static char const * const weekday_names[7u] =
            {
                "Sunday",       /* 0 */
                "Monday",       /* 1 */
                "Tuesday",      /* 2 */
                "Wednesday",    /* 3 */
                "Thursday",     /* 4 */
                "Friday",       /* 5 */
                "Saturday"      /* 6 */
            };

            fprintf(p_file_handle,
                "%-10s: %02d/%02d/%04d - %02d:%02d:%02d - %s\n",
                weekday_names[p_local_time_info->tm_wday],
                p_local_time_info->tm_mday,
                p_local_time_info->tm_mon + 1,
                p_local_time_info->tm_year + 1900,
                p_local_time_info->tm_hour,
                p_local_time_info->tm_min,
                p_local_time_info->tm_sec,
                p_message);
        }

        fclose(p_file_handle);
    }

} /* lnch_feature_timestamp_report() */

static
int
lnch_feature_timestamp_callback(
    Display * dpy)
{
    (void)dpy;

    if (g_file_name[0])
    {
        lnch_feature_timestamp_report("Leave");
    }

    return 0;
} /* lnch_feature_timestamp_callback() */

/*

Function: lnch_feature_timestamp_event

Description:

.

*/
void
lnch_feature_timestamp_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent const * const pev)
{
    (void)p_ctxt;

    if (!pev)
    {
        struct lnch_opts const * const p_opts = p_ctxt->p_opts;

        if (p_opts->p_log_file)
        {
            strcpy(g_file_name, p_opts->p_log_file);
        }
        else
        {
            g_file_name[0] = '\000';
        }

        /* register the error callback */
        /* hook of sigterm? */
        XSetIOErrorHandler(&lnch_feature_timestamp_callback);

        /* do log of start time */
        if (g_file_name[0])
        {
            lnch_feature_timestamp_report("Enter");
        }
    }

} /* lnch_feature_timestamp_event() */

#else /* #if defined(LNCH_FEATURE_TIMESTAMP */

struct not_empty;

#endif /* #if defined(LNCH_FEATURE_TIMESTAMP) */

/* end-of-file: lnch_feature_timestamp.c */
