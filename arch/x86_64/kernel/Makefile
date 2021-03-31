STEPS+=$(subst .S,.o,$(shell find memory -name '*.S'))
STEPS+=$(subst .S,.o,$(shell find drivers -name '*.S'))

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
