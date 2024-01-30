VPATH = .:scenario:a2560
DEPDIR := .deps

# Common source files
ASM_SRCS = assets.s
C_SRCS = ai.c actor.c actor_visual.c aerodrome.c ai.c airplane.c altitude.c \
        combat.c coordinate.c detection.c dogfight.c \
        flight.c inlines.c input.c list.c map.c memory.c movement.c \
        pilot.c playstate.c random.c scenario.c squadron.c \
        ui.c weather.c \
        scenario_dogfight.c

FOENIX_SRCS = foenix_u_main.c foenix_ui.c graphics.c $(C_SRCS)
MEGA65_SRCS = $(C_SRCS)
CX16_SRCS = cx16_main.c cx16_ui.c $(C_SRCS)

MODEL_A2560 = --code-model=large --data-model=small
MODEL_C256 = --code-model=large --data-model=medium
MODEL_MEGA65 = --code-model=banked
MODEL_CX16 = --code-model=banked

LNFLAGS_FOENIX_U = --copy-initialize vram  --copy-initialize palette1 \
	 --stack-size=2000 --target=Foenix
LNFLAGS_MEGA65 = --stack-size=2000 --target=mega65
LNFLAGS_CX16 = --stack-size=2000 --target=cx16

CFLAGS = -Wno-invalid-source-encoding --always-inline

# Object files
OBJS_A2560_DEBUG = $(ASM_SRCS:%.s=obj/%-a2560-debug.o) $(FOENIX_SRCS:%.c=obj/%-a2560-debug.o)
OBJS_C256_DEBUG = $(ASM_SRCS:%.s=obj/%-c256-debug.o) $(FOENIX_SRCS:%.c=obj/%-c256-debug.o)
OBJS_MEGA65_DEBUG = $(ASM_SRCS:%.s=obj/%-mega65-debug.o) $(MEGA65_SRCS:%.c=obj/%-mega65-debug.o)
OBJS_CX16_DEBUG = $(ASM_SRCS:%.s=obj/%-cx16-debug.o) $(CX16_SRCS:%.c=obj/%-cx16-debug.o)

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

obj/%-mega65-debug.o: %.s
	as6502 --core=45gs02 --target=mega65 $(MODEL_MEGA65) --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-mega65-debug.o: %.c $(DEPDIR)/%-debug.d | $(DEPDIR)
	@cc6502 --core=45gs02 $(MODEL_MEGA65) --target=mega65 $(CFLAGS)  --debug --dependencies -MQ$@ >$(DEPDIR)/$*-debug.d $<
	cc6502 --core=45gs02 $(MODEL_MEGA65) --target=mega65 $(CFLAGS)  --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-cx16-debug.o: %.s
	as6502 --core=65c02 --target=cx16 $(MODEL_CX16) --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-cx16-debug.o: %.c $(DEPDIR)/%-debug.d | $(DEPDIR)
	@cc6502 --core=65c02 $(MODEL_CX16) --target=cx16 $(CFLAGS)  --debug --dependencies -MQ$@ >$(DEPDIR)/$*-debug.d $<
	cc6502 --core=65c02 $(MODEL_CX16) --target=cx16 $(CFLAGS)  --debug --list-file=$(@:%.o=%.lst) -o $@ $<


bloody-april-a2560.elf: $(OBJS_A2560_DEBUG)
	ln68k --debug -o $@ $^ a2560u+.scm --list-file=bloody-april-a2560-debug.lst --semi-hosted --rtattr cstartup=Foenix_user --rtattr stubs=foenix $(LNFLAGS_FOENIX_U)

bloody-april-a2560.pgz:  $(OBJS)
	ln68k -o $@ $^ a2560k.scm  --output-format=pgz --list-file=bloody-april-a2560-Foenix.lst --rtattr cstartup=Foenix_user $(LNFLAGS_FOENIX_U)

bloody-april-a2560.s28:  $(OBJS)
	ln68k -o $@ $^ a2560k.scm --output-format=s28 --list-file=bloody-april-a2560-Foenix.lst --rtattr cstartup=Foenix_morfe $(LNFLAGS_FOENIX_U)

bloody-april-c256.elf: $(OBJS_C256_DEBUG)
	ln65816 --debug -o $@ $^ c256-u+-plain.scm --list-file=bloody-april-c256-debug.lst --semi-hosted --rtattr cstartup=Foenix_user --rtattr stubs=foenix $(LNFLAGS_FOENIX_U) --initialize-large-data --rtattr exit=simplified

bloody-april-mega65.elf: $(OBJS_MEGA65_DEBUG)
	ln6502 --debug -o $@ $^ mega65-plain.scm --list-file=bloody-april-mega65-debug.lst --semi-hosted --rtattr cstartup=mega65  $(LNFLAGS_MEGA65) --rtattr exit=simplified

bloody-april-cx16.elf: $(OBJS_CX16_DEBUG)
	ln6502 --debug -o $@ $^ cx16-banked.scm --list-file=bloody-april-cx16-debug.lst --semi-hosted --rtattr cstartup=cx16  $(LNFLAGS_CX16) --rtattr exit=simplified --no-copy-initialize=vram

clean:
	-rm $(DEPFILES)
	-rm $(OBJS) $(OBJS:%.o=%.lst) $(OBJS_A2560_DEBUG) $(OBJS_A2560_DEBUG:%.o=%.lst)
	-rm $(OBJS) $(OBJS:%.o=%.lst) $(OBJS_C256_DEBUG) $(OBJS_C256_DEBUG:%.o=%.lst)
	-rm $(OBJS) $(OBJS:%.o=%.lst) $(OBJS_CX16_DEBUG) $(OBJS_CX16_DEBUG:%.o=%.lst)
	-rm $(OBJS) $(OBJS:%.o=%.lst) $(OBJS_MEGA65_DEBUG) $(OBJS_MEGA65_DEBUG:%.o=%.lst)
	-rm bloody-april.elf bloody-april.pgz bloody-april-debug.lst
	-rm bloody-april-cx16.elf bloody-april-mega65.elf bloody-april-c256.elf bloody-april-a2560.elf

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(C_SRCS:%.c=$(DEPDIR)/%.d) $(C_SRCS:%.c=$(DEPDIR)/%-debug.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))
