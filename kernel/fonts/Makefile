STEPS=font.o renderer/psf.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) -relocatable $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

%.o: %.s
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(ASFLAGS) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
