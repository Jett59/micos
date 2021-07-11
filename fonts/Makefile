STEPS=font.o

Micos.build: $(STEPS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.s
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(ASFLAGS) -c $^ -o $@

clean:
	rm $(STEPS)
