IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -O3

ODIR=obj
LDIR =

SRCDIR=./src

BINDIR=./bin
LIBS=

SUITE_SRC := $(wildcard $(SRCDIR)/*.c)

SUITE_BIN := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%, $(SUITE_SRC))

#==============================================================================
# Targets
#==============================================================================
$(BINDIR)/%: $(SRCDIR)/%.c
	$(CC) -o $@ $< $(CFLAGS)

suite : $(SUITE_BIN)

print-%  : ; @echo $* = $($*)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BINDIR)/*
