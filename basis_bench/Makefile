IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -O3

ODIR=obj
LDIR =

BINDIR=./bin
LIBS=

#==============================================================================
# Helper Functions
#==============================================================================
objify = $(patsubst %,$(ODIR)/%,$(1))
depify = $(patsubst %,$(IDIR)/%,$(1))

#==============================================================================
# Targets
#==============================================================================
_IPC_OBJ = ipc.o 
IPC_OBJ = $(call objify,$(_IPC_OBJ))
ipc: $(BINDIR)/ipc

$(BINDIR)/ipc: $(IPC_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

_BRANCH_OBJ = branch_miss.o 
BRANCH_OBJ = $(call objify,$(_BRANCH_OBJ))
branch: $(BINDIR)/branch

$(BINDIR)/branch: $(BRANCH_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
