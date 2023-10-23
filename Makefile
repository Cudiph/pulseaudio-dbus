CFLAGS = $(shell pkg-config --cflags --libs glib-2.0 gio-2.0 libpulse-mainloop-glib) -O3

generated := pdbus_gen
objs := $(filter-out main.o, $(patsubst %.c,%.o,$(wildcard *.c)))

.PHONY: clean codegen dev-setup install uninstall
	
pulsedbus: $(objs)
	$(CC) main.c $(objs) $(CFLAGS) -o pulsedbus

codegen:
	gdbus-codegen --interface-prefix dev.cudiph. --c-namespace PD --c-generate-object-manager --generate-c-code $(generated) dev.cudiph.pulsedbus.xml

configure: codegen
	echo $(CFLAGS) | tr " " "\n" > compile_flags.txt

clean:
	rm -f pulsedbus $(objs)

install:
	mv pulsedbus ~/.local/bin/

uninstall:
	rm -f pulsedbus ~/.local/bin/pulsedbus
