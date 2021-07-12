STEPS=font.o renderer/psf.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.s
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
