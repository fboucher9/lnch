# See LICENSE for license details

# lnch - /LuNCH/ - l(au)nch(er) for b(reak)f(a)st terminal

LNCH_CC = $(CC)

LNCH_CFLAGS = $(CFLAGS) -ansi -pedantic -Wall -Wextra -Os

LNCH_LDFLAGS = $(LDFLAGS) -s -lX11

LNCH_SRCS = \
    lnch_main.c \
    lnch_display.c \
    lnch_body.c \
    lnch_os.c \
    lnch_tree.c \
    lnch_feature_xerror.c \
    lnch_feature_grid.c \
    lnch_feature_focus.c \
    lnch_feature_border.c \
    lnch_feature_redirect.c

.PHONY : all

all : lnch

lnch: $(LNCH_SRCS)
	$(LNCH_CC) -o $@ $(LNCH_CFLAGS) $(LNCH_SRCS) $(LNCH_LDFLAGS)
