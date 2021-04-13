STEPS:=serial/init/main.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
