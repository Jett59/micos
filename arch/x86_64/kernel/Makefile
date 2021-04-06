STEPS:=drivers/drivers.o
STEPS+=memory/memops.o memory/pointers.o
STEPS+=init/main.o init/exceptions.o init/pic.o
STEPS+=io/io.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
