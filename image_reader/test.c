#include "image_reader.h"

void config_image_buffer(image_reader_buf_t *image_buf)
{
	
	image_buf->width  = 4608;
	image_buf->height = 3456;
	image_buf->type   = 0;

}

int main(int argc,char *argv[])
{
	int fd = 0;
	
	image_reader_buf_t image_buf;
	
	if(argc > 3)
	{
		printf("too many args");
		return -1;
	}
	
	fd = open(argv[1],O_RDWR);
	
	printf("open %s %d\n",argv[1],fd);
	
	config_image_buffer(&image_buf);
	
	config_buffer(&image_buf);
	
	alloc_buffer(&image_buf);
	
	image_reader_interface(fd,&image_buf);
	
	close(fd);
	
}
