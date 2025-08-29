VPATH = .:scenario
DEPDIR := .deps

# A2560U source file
A2560U_SRCS = foenix_u_main.c foenix_ui.c foenix_graphics.c

# Common source files
C_SRCS = ai.c actor.c actor_visual.c aerodrome.c ai.c airplane.c altitude.c \
        combat.c coordinate.c detection.c dogfight.c \
        flight.c inlines.c input.c list.c map.c memory.c movement.c \
        pilot.c playstate.c random.c scenario.c squadron.c \
        ui.c weather.c scenario_dogfight.c scenario_explore_map.c \
	$(A2560U_SRCS)

ASM_SRCS = foenix_assets.s

AFLAGS = --target=a2560u --debug --code-model=large --data-model=small
CFLAGS = $(AFLAGS) -Wno-invalid-source-encoding --always-inline -I. -Iscenario

LNFLAGS = --stack-size=2000 --target=a2560u

# Object files
OBJS = $(ASM_SRCS:%.s=obj/%.o) $(C_SRCS:%.c=obj/%.o)

obj/%.o: %.s
	as68k $(AFLAGS) --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%.o: %.c $(DEPDIR)/%.d | $(DEPDIR)
	@cc68k $(INCLUDE) $(CFLAGS)  --dependencies -MQ$@ >$(DEPDIR)/$*.d $<
	cc68k $(INCLUDE) $(CFLAGS) --list-file=$(@:%.o=%.lst) -o $@ $<

BloodyApril.elf:  $(OBJS)
	ln68k -o $@ $^ --list-file=bloody-april.lst $(LNFLAGS)

clean:
	-rm $(DEPFILES)
	-rm $(OBJS) $(OBJS:%.o=%.lst)
	-rm bloody-april.elf bloody-april-debug.lst

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(C_SRCS:%.c=$(DEPDIR)/%.d) $(C_SRCS:%.c=$(DEPDIR)/%-debug.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))
