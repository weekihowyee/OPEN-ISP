#include "image_reader.h"

#define ORIGIN_DUMP 1
#define POST_DUMP 1

static int yuv_420_reader(int fd,image_reader_buf_t *frame)
{
	
	return 0;
	
}

static int dump_raw_origin(image_reader_buf_t *frame)
{
	
	
	
	return 0;
}

static int mipi_10_raw_reader(int fd,image_reader_buf_t *frame)
{
	uint32_t rc;
	printf("E mipi_10_raw_reader \n");
	
	if(fd < 0)
	{
		printf("open raw failed !\n");
		return -1;
	}
	rc = read(fd,frame->buf,frame->length);
	
	if(rc <= 0)
		printf("read failed \n");
	
	if(ORIGIN_DUMP)
	{
		
	}
	
	return 0;
	
}

int config_buffer(image_reader_buf_t *frame)
{
	
	// rely on width && height to calc num of byte
	// P3(1:0) P2(1:0) P1(1:0) P0(1:0) P3(9:2) P2(9:2) P1(9:2) P0(9:2)
	// 4 pixels occupy 5 bytes, no padding needed
	if(frame->type == 0) // mipi 10 raw
	  frame->length = ((frame->width * frame->height)/4) * 5;
	printf("config_buffer length %ld\n",frame->length);
	return 0;
}

int alloc_buffer(image_reader_buf_t *frame)
{
	
	frame->buf = malloc(frame->length);
	if(frame->buf == NULL)
	{
		printf("alloc_buffer failed\n");
		return -1;
	}
		
	return 0;
}

int image_reader_interface(int fd,image_reader_buf_t *frame)
{
	
	switch(frame->type)
	{
		case 0:
		
		  mipi_10_raw_reader(fd,frame);
		
		break;
		
		case 1:
		
		  yuv_420_reader(fd,frame);
		
		break;
	}
	
}
