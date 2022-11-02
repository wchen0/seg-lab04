objects = input_generator.o stdin_format_parser.o
head = input_generator.h

test : $(objects)
	g++ -o test $(objects)
input_generator.o : $(head)
stdin_format_parser.o : $(head)

.PHONY : clean
clean :
	rm test $(objects)
