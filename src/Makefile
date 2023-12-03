VPATH = .:scenario:a2560
DEPDIR := .deps

# Common source files
ASM_SRCS = assets.s
C_SRCS = main.c ai.c actor.c actor_visual.c aerodrome.c ai.c airplane.c altitude.c \
        combat.c coordinate.c detection.c dogfight.c \
        flight.c foenix.c inlines.c input.c list.c map.c memory.c movement.c \
        pilot.c playstate.c random.c scenario.c squadron.c \
        ui.c weather.c \
        scenario_dogfight.c \
	foenix.c graphics.c

MODEL_A2560 = --code-model=large --data-model=small
MODEL_C256 = --code-model=large --data-model=medium

LNFLAGS = --copy-initialize vram  --copy-initialize palette1 \
	 --stack-size=2000 --target=Foenix

CFLAGS = -Wno-invalid-source-encoding --always-inline

# Object files
OBJS = $(ASM_SRCS:%.s=obj/%.o) $(C_SRCS:%.c=obj/%.o)
OBJS_A2560_DEBUG = $(ASM_SRCS:%.s=obj/%-a2560-debug.o) $(C_SRCS:%.c=obj/%-a2560-debug.o)
OBJS_C256_DEBUG = $(ASM_SRCS:%.s=obj/%-c256-debug.o) $(C_SRCS:%.c=obj/%-c256-debug.o)

obj/%.o: %.s
	as68k --core=68000 $(MODEL_A2560) --target=Foenix --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%.o: %.c $(DEPDIR)/%.d | $(DEPDIR)
	@cc68k --core=68000 $(MODEL_A2560) --target=Foenix --always-inline --debug --dependencies -MQ$@ >$(DEPDIR)/$*.d $<
	cc68k --core=68000 $(MODEL_A2560) --target=Foenix --always-inline --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-a2560-debug.o: %.s
	as68k --core=68000 $(MODEL_A2560) --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-a2560-debug.o: %.c $(DEPDIR)/%-debug.d | $(DEPDIR)
	@cc68k --core=68000 $(MODEL_A2560) --target=Foenix $(CFLAGS) -D__FOENIX_A2560_REGISTER_SIZE__=16 --debug --dependencies -MQ$@ >$(DEPDIR)/$*-debug.d $<
	cc68k --core=68000 $(MODEL_A2560) --target=Foenix $(CFLAGS) -D__FOENIX_A2560_REGISTER_SIZE__=16 --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-c256-debug.o: %.s
	as65816  $(MODEL_C256) --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-c256-debug.o: %.c $(DEPDIR)/%-debug.d | $(DEPDIR)
	@cc65816 --core=65816 $(MODEL_C256) --target=Foenix $(CFLAGS)  --debug --dependencies -MQ$@ >$(DEPDIR)/$*-debug.d $<
	cc65816 --core=65816 $(MODEL_C256) --target=Foenix $(CFLAGS)  --debug --list-file=$(@:%.o=%.lst) -o $@ $<

bloody-april-a2560.elf: $(OBJS_A2560_DEBUG)
	ln68k --debug -o $@ $^ a2560u+.scm --list-file=bloody-april-a2560-debug.lst --semi-hosted --rtattr cstartup=Foenix_user --rtattr stubs=foenix $(LNFLAGS)

bloody-april-a2560.pgz:  $(OBJS)
	ln68k -o $@ $^ a2560k.scm  --output-format=pgz --list-file=bloody-april-a2560-Foenix.lst --rtattr cstartup=Foenix_user $(LNFLAGS)

bloody-april-a2560.s28:  $(OBJS)
	ln68k -o $@ $^ a2560k.scm --output-format=s28 --list-file=bloody-april-a2560-Foenix.lst --rtattr cstartup=Foenix_morfe $(LNFLAGS)

bloody-april-c256.elf: $(OBJS_C256_DEBUG)
	ln65816 --debug -o $@ $^ c256-u+-plain.scm --list-file=bloody-april-c256-debug.lst --semi-hosted --rtattr cstartup=Foenix_user --rtattr stubs=foenix $(LNFLAGS)

clean:
	-rm $(DEPFILES)
	-rm $(OBJS) $(OBJS:%.o=%.lst) $(OBJS_A2560_DEBUG) $(OBJS_A2560_DEBUG:%.o=%.lst)
	-rm $(OBJS) $(OBJS:%.o=%.lst) $(OBJS_C256_DEBUG) $(OBJS_C256_DEBUG:%.o=%.lst)
	-rm bloody-april.elf bloody-april.pgz bloody-april-debug.lst

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(C_SRCS:%.c=$(DEPDIR)/%.d) $(C_SRCS:%.c=$(DEPDIR)/%-debug.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))
