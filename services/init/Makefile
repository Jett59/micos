LDFLAGS:=-T linker.ld

STEPS:=init.o

build/init: $(STEPS)
	mkdir -p build
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(ASFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
	rm -rf build
