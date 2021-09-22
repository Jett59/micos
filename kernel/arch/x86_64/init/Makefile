STEPS=entry.o init.o gdt.o paging.o err.o long.o multiboot.o finale.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
