STEPS:=kernel.o main.o
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
	rm -f $(STEPS)
