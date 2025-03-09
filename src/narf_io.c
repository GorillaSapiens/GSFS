#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>

#include "narf_io.h"

// This is an example implementation using mmap'd files.

#define FILENAME "example.narf"
#define SECTOR_SIZE 512
#define BYTES (1024*1024*1024) // 1 Gig
#define SECTORS (BYTES / SECTOR_SIZE)

static uint8_t *image;
static int fd;

bool narf_io_open(void) {
   if (access(FILENAME, F_OK) == 0) {
      fd = open(FILENAME, O_RDWR, 0);
      if (fd == -1) {
         perror("open example.narf");
         exit(-1);
      }
   }
   else {
      fd = open(FILENAME, O_RDWR | O_CREAT, 0766);
      if (fd == -1) {
         perror("create example.narf");
         exit(-1);
      }
   }
   image = mmap(NULL, BYTES, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if (image == NULL) {
      perror("mmap");
      exit(-1);
   }

   return true;
}

bool narf_io_close(void) {
   sync();
   if (munmap(image, BYTES) == -1) {
      perror("munmap");
      exit(-1);
   }
   close(fd);
   return true;
}

uint32_t narf_io_sectors(void) {
   return SECTORS;
}

bool narf_io_write(uint32_t sector, uint8_t *data) {
   bool ret = true;
   if (NULL == memcpy(image + sector * SECTOR_SIZE, data, SECTOR_SIZE)) {
      ret = false;
   }
   return ret;
}

bool narf_io_read(uint32_t sector, uint8_t *data) {
   bool ret = true;
   if (NULL == memcpy(data, image + sector * SECTOR_SIZE, SECTOR_SIZE)) {
      ret = false;
   }
   return ret;
}

// vim:set ai softtabstop=3 shiftwidth=3 tabstop=3 expandtab: ff=unix
