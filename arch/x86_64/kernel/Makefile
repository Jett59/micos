STEPS:=drivers/drivers.o
STEPS+=memory/memops.o memory/pointers.o
STEPS+=init/main.o init/exceptions.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

%.o: %.c
	echo "$(CC) $@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
