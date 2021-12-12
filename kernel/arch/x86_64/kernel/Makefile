STEPS:=drivers/drivers.o
STEPS+=memory/memops.o memory/pointers.o
STEPS+=init/main.o init/exceptions.o init/pic.o
STEPS+=io/io.o
STEPS+=paging/paging.o paging/cache.o paging/mapping.o paging/frames.o
STEPS+=paging/malloc/alloc.o paging/malloc/blocks.o paging/malloc/free.o
STEPS+=drivers/keyboard/keyboard_handler.o drivers/keyboard/init.o drivers/keyboard/main.o
STEPS+=interrupts/registry.o
STEPS+=drivers/pit/receiver.o drivers/pit/initialiser.o
STEPS+=drivers/pci/configuration_space.o
STEPS+=drivers/serial/query.o drivers/serial/configuration.o drivers/serial/out.o
STEPS+=multiboot/mbi.o
STEPS+=error/kill.o
STEPS+=task/state.o task/tss.o
STEPS+=thread/thread.o
STEPS+=drivers/rtc/timer/handler.o drivers/rtc/timer/init.o
STEPS+=syscall/syscall_entry.o syscall/syscall_setup.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
