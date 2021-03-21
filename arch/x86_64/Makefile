STEPS=$(subst .S,.o,$(wildcard **/*.S)) $(subst .c,.O,$(wildcard **/*.c))

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.O: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
