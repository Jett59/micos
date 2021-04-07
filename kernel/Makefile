STEPS:=kernel.o main.o
STEPS+=drivers/vga/vga_console.o
STEPS+=drivers/keyboard/keyboard_handler.o
STEPS+=drivers/timer/handler.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
