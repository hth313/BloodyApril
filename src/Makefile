VPATH = .:scenario:ACE/src/ace/managers:ACE/src/ace/managers/viewport:ACE/src/ace/utils:amiga
DEPDIR := .deps

ACE_SRCS = audio.c blit.c bob.c copper.c game.c joy.c key.c log.c \
	memory.c mouse.c ptplayer.c rand.c sprite.c state.c \
	system.c timer.c \
	camera.c scrollbuffer.c simplebuffer.c tilebuffer.c \
	bitmap.c bmframe.c chunky.c custom.c dir.c disk_file.c \
	extview.c file.c font.c pak_file.c palette.c sprite.c \
	string.c tag.c

# Common source files
C_SRCS = ai.c actor.c actor_visual_bobs.c aerodrome.c ai.c airplane.c altitude.c \
        combat.c coordinate.c detection.c dogfight.c \
        flight.c inlines.c input.c list.c map.c memory.c movement.c \
        pilot.c playstate.c random.c scenario.c squadron.c \
        ui.c weather.c Amiga_main.c \
        scenario_dogfight.c scenario_explore_map.c \
	bobs.c ui.c \
	$(ACE_SRCS)

# 	main.c ui.c graphics.c

# ASM_SRCS = assets.s syscalls.s


AFLAGS = --target=Amiga --debug --core=68020 --code-model=large --data-model=large
CFLAGS = $(AFLAGS) -Wno-invalid-source-encoding --always-inline -I. -Iscenario --include-system=ACE/include -DAMIGA -DACE_TILEBUFFER_TILE_TYPE=UWORD -DACE_SCROLLBUFFER_POT_BITMAP_HEIGHT -DACE_SCROLLBUFFER_ENABLE_SCROLL_X -DACE_SCROLLBUFFER_ENABLE_SCROLL_Y -DACE_SCROLLBUFFER_X_MARGIN_SIZE=1 -DACE_SCROLLBUFFER_Y_MARGIN_SIZE=1

LNFLAGS = --stack-size=2000 --target=Amiga

# Object files
OBJS = $(ASM_SRCS:%.s=obj/%.o) $(C_SRCS:%.c=obj/%.o)

obj/%.o: %.s
	as68k $(AFLAGS) --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%.o: %.c $(DEPDIR)/%.d | $(DEPDIR)
	@cc68k $(INCLUDE) $(CFLAGS)  --dependencies -MQ$@ >$(DEPDIR)/$*.d $<
	cc68k $(INCLUDE) $(CFLAGS) --list-file=$(@:%.o=%.lst) -o $@ $<

BloodyApril.hunk:  $(OBJS)
	ln68k --cstartup=amiga -o $@ $^ --output-format=hunk --list-file=bloody-april.lst $(LNFLAGS)

clean:
	-rm $(DEPFILES)
	-rm $(OBJS) $(OBJS:%.o=%.lst)
	-rm bloody-april.elf bloody-april.hunk bloody-april-debug.lst

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(C_SRCS:%.c=$(DEPDIR)/%.d) $(C_SRCS:%.c=$(DEPDIR)/%-debug.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))
