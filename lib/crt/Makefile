STEPS:=$(ARCH)/crt0.o crtmain.o

build: $(STEPS)

%.o: %.S
	echo $(AS) $(BASEDIR)/$@
	$(AS) $(ASFLAGS) $(CPPFLAGS) -c $^ -o $@

%.o: %.c
	echo $(AS) $(BASEDIR)/$@
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
