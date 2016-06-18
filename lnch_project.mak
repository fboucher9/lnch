# See LICENSE for license details

# lnch - /LuNCH/ - l(au)nch(er) for b(reak)f(a)st terminal

LNCH_CFLAGS = $(CFLAGS) -ansi -pedantic -Wall -Wextra -Os -I$(LNCH_DST_PATH)

LNCH_LDFLAGS = $(LDFLAGS) -s -lX11

LNCH_SRCS = \
    $(LNCH_DST_PATH)/_obj_lnch_main.o \
    $(LNCH_DST_PATH)/_obj_lnch_display.o \
    $(LNCH_DST_PATH)/_obj_lnch_body.o \
    $(LNCH_DST_PATH)/_obj_lnch_os.o \
    $(LNCH_DST_PATH)/_obj_lnch_tree.o \
    $(LNCH_DST_PATH)/_obj_lnch_key.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_xerror.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_grid.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_focus.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_border.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_child.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_redirect.o

LNCH_HDRS = \
    $(LNCH_SRC_PATH)/lnch_body.h \
    $(LNCH_SRC_PATH)/lnch_cfg.h \
    $(LNCH_SRC_PATH)/lnch_ctxt.h \
    $(LNCH_SRC_PATH)/lnch_display.h \
    $(LNCH_SRC_PATH)/lnch_feature_border.h \
    $(LNCH_SRC_PATH)/lnch_feature_child.h \
    $(LNCH_SRC_PATH)/lnch_feature_focus.h \
    $(LNCH_SRC_PATH)/lnch_feature_grid.h \
    $(LNCH_SRC_PATH)/lnch_feature_redirect.h \
    $(LNCH_SRC_PATH)/lnch_feature_xerror.h \
    $(LNCH_SRC_PATH)/lnch_key.h \
    $(LNCH_SRC_PATH)/lnch_main.h \
    $(LNCH_SRC_PATH)/lnch_mods.h \
    $(LNCH_SRC_PATH)/lnch_os.h \
    $(LNCH_SRC_PATH)/lnch_tree.h

.PHONY : all

# Default target
all : $(LNCH_DST_PATH)/lnch

$(LNCH_DST_PATH)/lnch: $(LNCH_SRCS)
	@echo linking $@
	@echo -o $@ $(LNCH_CFLAGS) $(LNCH_SRCS) $(LNCH_LDFLAGS) > $(LNCH_DST_PATH)/_obj_lnch.cmd
	@$(LNCH_CC) @$(LNCH_DST_PATH)/_obj_lnch.cmd

# Extra dependencies of target
$(LNCH_DST_PATH)/lnch : $(LNCH_HDRS)

# Build each object file
$(LNCH_DST_PATH)/_obj_%.o : $(LNCH_SRC_PATH)/%.c
	@echo compiling $@
	@echo -c -o $@ $(LNCH_CFLAGS) -MT $@ -MMD -MP -MF $@.d $< > $@.cmd
	@$(LNCH_CC) @$@.cmd

# Build the precompiled header
$(LNCH_DST_PATH)/lnch_os.h.gch : $(LNCH_SRC_PATH)/lnch_os.h
	@echo generating $@
	@$(LNCH_CC) -c -o $@ $(LNCH_CFLAGS) $(LNCH_SRC_PATH)/lnch_os.h

# Indicate that all object files have dependency on precompiled header
$(LNCH_SRCS) : $(LNCH_DST_PATH)/lnch_os.h.gch

-include $(LNCH_DST_PATH)/_obj_*.o.d
