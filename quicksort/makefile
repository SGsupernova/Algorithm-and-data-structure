#---------------------------------------------------------------

SOURCES = my_sort.cpp my_sort_main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
MYPROGRAM = quicksort

CC = g++

#---------------------------------------------------------------

all: $(SOURCES) $(MYPROGRAM)

$(MYPROGRAM) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clean :
	rm -f *.o $(MYPROGRAM)
