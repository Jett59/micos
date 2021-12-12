STEPS:=serial/init/main.o
STEPS+=display/display.o
STEPS+=keyboard/keyboard_handler.o keyboard/keycode.o
STEPS+=pci/pci_init.o pci/pci_probe.o pci/pci_table.o
STEPS+=console/console.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
