STEPS=$(subst .S,.o,$(wildcard **/*.S))

LDFLAGS+=-T linker.ld

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
