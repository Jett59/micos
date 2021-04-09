STEPS:=kernel.o main.o
STEPS+=drivers/vga/vga_console.o
STEPS+=drivers/keyboard/keyboard_handler.o
STEPS+=drivers/timer/handler.o
STEPS+=drivers/pci/pci_init.o drivers/pci/pci_probe.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
