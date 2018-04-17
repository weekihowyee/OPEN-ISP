runner: test.o image_reader.o
	gcc -o runner test.o image_reader.o
main.o: test.c image_reader.h
	gcc -c test.c
image_reader.o: image_reader.c image_reader.h
	gcc -c image_reader.c
clean:
	rm runner *.o
