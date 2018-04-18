runner: test.o image_reader.o
	gcc -o runner test.o image_reader.o -g
main.o: test.c image_reader.h
	gcc -c -g test.c
image_reader.o: image_reader.c image_reader.h
	gcc -c -g image_reader.c
clean:
	rm runner *.o
