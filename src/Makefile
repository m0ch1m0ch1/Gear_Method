COMPILER = gcc -O3
CFLAGS   = -MMD -MP -Wall
LDFLAGS  =
LIBS     = -lm
INCLUDE  = -I../inc
TARGET   = ../bin/gear
OBJDIR   = ../obj
SOURCES  = $(wildcard *.c)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))
DEPENDS  = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
		$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
		@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
		$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
		rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
