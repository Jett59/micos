STEPS=head/Micos.build init/Micos.build

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%/Micos.build: %
	$(MAKE) -s -C "$^" Micos.build BASEDIR="$(BASEDIR)/$^" ARCH="$(ARCH)" LD="$(LD)" AS="$(AS)" CC="$(CC)" AFLAGS="$(AFLAGS)" LDFLAGS="$(LDFLAGS)" CFLAGS="$(CFLAGS)"

clean: $(subst Micos.build,clean,$(STEPS))
	rm $(STEPS)

%/clean: %
	echo "clean $(BASEDIR)/$^"
	$(MAKE) -s -C $^ clean BASEDIR="$(BASEDIR)/$^"
