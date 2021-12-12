STEPS:=vfs/vfs.o vfs/directory.o
STEPS+=initramfs/initramfs.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
