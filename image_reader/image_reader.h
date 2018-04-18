#ifndef _IMAGE_READER_H_
#define _IMAGE_READER_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

#define TEST_FILE_LOCATION "/home/king/prac/test_file_loc/"

typedef struct _raw_buf_t {
  
  void *buf;
  uint32_t length;
  
  // enable this , app should free this buffer, else ,image_reader will do
  uint8_t need_free_by_app; 
  
} raw_buf_t;

typedef struct _image_reader_buf_t {
  
  int width;
  int height;
  void *buf; // oringin_buf , mipi raw data
  raw_buf_t normal_buf; // after convert , BGBGBGBG
  int type;
  uint32_t length;
  
} image_reader_buf_t;

int image_reader_interface(int fd,image_reader_buf_t *frame);
int alloc_buffer(image_reader_buf_t *frame);
int config_buffer(image_reader_buf_t *frame);

#endif
