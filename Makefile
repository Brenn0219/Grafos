CC = gcc
CFLAGS = -Wall -o
CPPFLAGS = -Iinclude

SRCDIR = src
DATADIR = data
INCLUDEDIR = include

TARGET = run
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $@ $(OBJECTS)

%.o: $(SRCDIR)/%.c
	$(CC) -c $(CPPFLAGS) -o $@ $<

copy_data:
	cp $(DATADIR)/graph-test-100.txt ./graph-test-50000.txt

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean copy_data