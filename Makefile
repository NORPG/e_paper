SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
CFLAGS = -O2 -g -Wall -fmessage-length=0
LIBS =
TARGET = IT8951_USB
.phony = all clean

<<<<<<< HEAD
$(TARGET): $(OBJS)
=======
TARGET = IT8951_USB

$(TARGET):	$(OBJS)
>>>>>>> 291ae6c46cad7a28ca52b69ec8b8a7495cb90baa
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
