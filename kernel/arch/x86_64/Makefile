STEPS=head/Micos.build init/Micos.build kernel/Micos.build

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) -relocatable $^ -o $@
	rm $(STEPS)

%/Micos.build: %
	"$(MAKE)" -s -C "$^" Micos.build BASEDIR="$(BASEDIR)/$^"

clean: $(subst Micos.build,clean,$(STEPS))

%/clean: %
	echo "clean $(BASEDIR)/$^"
	"$(MAKE)" -s -C $^ clean BASEDIR="$(BASEDIR)/$^"
