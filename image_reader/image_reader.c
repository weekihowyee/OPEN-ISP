#include "image_reader.h"

#define ORIGIN_DUMP 1
#define POST_DUMP 1

static int dump_raw(void *buf , uint32_t length , uint8_t id)
{
	int fd;
	char name[128];
	
	snprintf(name, sizeof(name), TEST_FILE_LOCATION"test_%d.raw",id);
	fd = open(name,O_RDWR | O_CREAT, 0777);
	
	write(fd,buf,length);
	
	sync();
	
	close(fd);
	
	return 0;
}

static int yuv_420_reader(int fd,image_reader_buf_t *frame)
{
	
	return 0;
	
}

static int convert_to_normal_buf(image_reader_buf_t *frame)
{
	// P3(1:0) P2(1:0) P1(1:0) P0(1:0) P3(9:2) P2(9:2) P1(9:2) P0(9:2)
	int i,j=0,k;
	uint16_t common_byte;
	uint8_t *buf_t;
	uint16_t *normal_buf_t;
	buf_t = (uint8_t *)(frame->buf);
	normal_buf_t = (uint16_t *)(frame->normal_buf.buf);
	for(i = 0;i<frame->length;i+=5)
	{
		common_byte = buf_t[i];
		normal_buf_t[j++] = (buf_t[i+4]<<2)+(0x03&common_byte); //P0
		normal_buf_t[j++] = (buf_t[i+3]<<2)+(0x0C&common_byte); //P1
		normal_buf_t[j++] = (buf_t[i+2]<<2)+(0x30&common_byte); //P2
		normal_buf_t[j++] = (buf_t[i+1]<<2)+(0xC0&common_byte); //P3
	}
	
	if(POST_DUMP)
	{
		dump_raw(frame->normal_buf.buf,frame->normal_buf.length,1);
	}
	
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
		dump_raw(frame->buf,frame->length,0);
	}
	
	convert_to_normal_buf(frame);
	
	return 0;
	
}

int config_buffer(image_reader_buf_t *frame)
{
	
	// rely on width && height to calc num of byte
	// P3(1:0) P2(1:0) P1(1:0) P0(1:0) P3(9:2) P2(9:2) P1(9:2) P0(9:2)
	// 4 pixels occupy 5 bytes, no padding needed
	if(frame->type == 0) // mipi 10 raw
	{
	    frame->length = ((frame->width * frame->height)/4) * 5;
		frame->normal_buf.length = frame->width * frame->height; // normal buffer
	}
	
	printf("config_buffer length %ld\n",frame->length);
	return 0;
}

int alloc_buffer(image_reader_buf_t *frame)
{
	
	frame->buf = malloc(frame->length);
	if(frame->normal_buf.length)
	{
		frame->normal_buf.buf = malloc(frame->normal_buf.length);
		if(frame->normal_buf.buf == NULL)
		{
			printf("alloc_buffer failed\n");
			return -1;
		}
	}
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
