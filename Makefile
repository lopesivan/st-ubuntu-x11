# st - simple terminal
# See LICENSE file for copyright and license details.
.POSIX:

include config.mk

SRC = st.c x.c boxdraw.c hb.c
OBJ = $(SRC:.c=.o)

all: options st

options:
	@echo "st build options:"
	@echo "CFLAGS  = $(STCFLAGS)"
	@echo "LDFLAGS = $(STLDFLAGS)"
	@echo "CC      = $(CC)"

.c.o:
	$(CC) $(STCFLAGS) -c $< -o $@

st.o: st.c config.h config.mk st.h win.h
x.o: x.c arg.h config.h st.h win.h hb.h
hb.o: hb.c st.h
boxdraw.o: boxdraw.c config.h st.h boxdraw_data.h

st: $(OBJ)
	$(CC) -o $@ $(OBJ) $(STLDFLAGS)

clean:
	rm -f st $(OBJ) st-$(VERSION).tar.gz

dist: clean
	mkdir -p st-$(VERSION)
	cp -R config.mk Makefile\
		config $(SRC) \
		st-$(VERSION)
	tar -cf - st-$(VERSION) | gzip > st-$(VERSION).tar.gz
	rm -rf st-$(VERSION)

install: st
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 st $(DESTDIR)$(PREFIX)/bin/st
	@echo "st instalado em $(DESTDIR)$(PREFIX)/bin/st"

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/st

.PHONY: all options clean dist install uninstall
