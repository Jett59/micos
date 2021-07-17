STEPS:=kernel.o main.o
STEPS+=drivers/keyboard/keyboard_handler.o drivers/keyboard/keycode.o
STEPS+=drivers/timer/handler.o
STEPS+=drivers/pci/pci_init.o drivers/pci/pci_probe.o drivers/pci/pci_table.o drivers/pci/pci_log.o
STEPS+=drivers/console/console.o
STEPS+=stdio/conout.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
