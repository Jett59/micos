STEPS:=kernel.o main.o
STEPS+=drivers/keyboard/keyboard_handler.o drivers/keyboard/keycode.o
STEPS+=drivers/pci/pci_init.o drivers/pci/pci_probe.o drivers/pci/pci_table.o
STEPS+=drivers/console/console.o
STEPS+=stdio/conout.o
STEPS+=error/error_screen.o
STEPS+=task/registry.o
STEPS+=strings/strops.o
STEPS+=memory/memops.o
STEPS+=stack/protector.o
STEPS+=syscall/syscall_handler.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
