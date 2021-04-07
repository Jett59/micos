STEPS:=drivers/drivers.o
STEPS+=memory/memops.o memory/pointers.o
STEPS+=init/main.o init/exceptions.o init/pic.o
STEPS+=io/io.o
STEPS+=paging/paging.o
STEPS+=drivers/keyboard/keyboard_handler.o drivers/keyboard/init.o drivers/keyboard/main.o
STEPS+=interrupts/registry.o
STEPS+=drivers/timer/receiver.o drivers/timer/initialiser.o

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
