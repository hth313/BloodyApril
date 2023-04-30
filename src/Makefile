VPATH = src
DEPDIR := .deps

# Common source files
ASM_SRCS = assets.s
C_SRCS = main.c ai.c airplane.c altitude.c combat.c dogfight.c input.c pilot.c \
	ui.c unit.c

FOENIX_C_SRCS = foenix.c

MODEL = --code-model=large --data-model=small

LNFLAGS = --copy-initialize vram  --copy-initialize palette1 \
	--rtattr printf=reduced \
	 --stack-size=2000 --target=Foenix


# Object files
OBJS = $(ASM_SRCS:%.s=obj/%.o) $(C_SRCS:%.c=obj/%.o)
OBJS_DEBUG = $(ASM_SRCS:%.s=obj/%-debug.o) $(C_SRCS:%.c=obj/%-debug.o)

obj/%.o: %.s
	as68k --core=68000 $(MODEL) --target=Foenix --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%.o: %.c $(DEPDIR)/%.d | $(DEPDIR)
	@cc68k --core=68000 $(MODEL) --target=Foenix --always-inline --debug --dependencies -MQ$@ >$(DEPDIR)/$*.d $<
	cc68k --core=68000 $(MODEL) --target=Foenix --always-inline --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-debug.o: %.s
	as68k --core=68000 $(MODEL) --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-debug.o: %.c $(DEPDIR)/%-debug.d | $(DEPDIR)
	@cc68k --core=68000 $(MODEL) --target=Foenix --always-inline -Imodule/Calypsi-m68k-Foenix/include --debug --dependencies -MQ$@ >$(DEPDIR)/$*-debug.d $<
	cc68k --core=68000 $(MODEL) --target=Foenix --always-inline -Imodule/Calypsi-m68k-Foenix/include --debug --list-file=$(@:%.o=%.lst) -o $@ $<

bloody-april.elf: $(OBJS_DEBUG)
	ln68k --debug -o $@ $^ a2560u+.scm --list-file=bloody-april-debug.lst --semi-hosted --rtattr cstartup=Foenix_user --rtattr stubs=foenix $(LNFLAGS)

bloody-april.pgz:  $(OBJS)
	ln68k -o $@ $^ a2560k.scm  --output-format=pgz --list-file=bloody-april-Foenix.lst --rtattr cstartup=Foenix_user $(LNFLAGS)

bloody-april.s28:  $(OBJS)
	ln68k -o $@ $^ a2560k.scm --output-format=s28 --list-file=bloody-april-Foenix.lst --rtattr cstartup=Foenix_morfe $(LNFLAGS)


clean:
	-rm $(DEPFILES)
	-rm $(OBJS) $(OBJS:%.o=%.lst) $(OBJS_DEBUG) $(OBJS_DEBUG:%.o=%.lst)
	-rm bloody-april.elf bloody-april.pgz bloody-april-debug.lst

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(C_SRCS:%.c=$(DEPDIR)/%.d) $(C_SRCS:%.c=$(DEPDIR)/%-debug.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))
