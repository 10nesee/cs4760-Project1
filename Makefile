# Makefile

# Compile oss and user

# Use C compiler and enable warnings/debugging information
CC = gcc 
CFLAGS = -Wall -g

# Build oss and user
all: oss user


# Compile into executable
oss: oss.o
	$(CC) $(CFLAGS) -o oss oss.o

user: user.o
	$(CC) $(CFLAGS) -o user user.o

oss.o: oss.c
	$(CC) $(CFLAGS) -c oss.c

user.o: user.c
	$(CC) $(CFLAGS) -c user.c

# delete executable
clean:
	rm -f oss user *.o
