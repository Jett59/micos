CFLAGS+=-m64

LDFLAGS+= -t linker.ld

STEPS:=kernel.o main.o
STEPS+=drivers/vga/vga_console.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
