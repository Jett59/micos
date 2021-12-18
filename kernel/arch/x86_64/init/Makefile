STEPS=entry.o init.o gdt.o paging.o err.o long.o multiboot.o finale.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) -relocatable $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(ASFLAGS) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
