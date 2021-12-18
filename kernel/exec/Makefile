STEPS:=exec.o elf.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) -relocatable $^ -o $@

%.o: %.c
	echo "$(CC) $(BASEDIR)/$@"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
