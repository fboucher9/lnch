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
    $(LNCH_DST_PATH)/_obj_lnch_opts.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_xerror.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_button2.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_grid.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_focus.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_border.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_child.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_redirect.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_movesize.o \
    $(LNCH_DST_PATH)/_obj_lnch_feature_keepalive.o

.PHONY : all clean

# Default target
all : $(LNCH_DST_PATH)/lnch

$(LNCH_DST_PATH)/lnch: $(LNCH_SRCS)
	@echo linking $@
	@echo -o $@ $(LNCH_CFLAGS) $(LNCH_SRCS) $(LNCH_LDFLAGS) > $(LNCH_DST_PATH)/_obj_lnch.cmd
	@$(LNCH_CC) @$(LNCH_DST_PATH)/_obj_lnch.cmd

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

clean :
	-rm -f $(LNCH_DST_PATH)/lnch
	-rm -f $(LNCH_DST_PATH)/_obj_*.o
	-rm -f $(LNCH_DST_PATH)/_obj_*.d
	-rm -f $(LNCH_DST_PATH)/_obj_*.cmd
	-rm -f $(LNCH_DST_PATH)/*.gch

-include $(LNCH_DST_PATH)/_obj_*.o.d
