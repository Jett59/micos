STEPS=head.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) -relocatable $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(ASFLAGS) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
