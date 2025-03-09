#include <stdio.h>
#include <string.h>

#include "narf_io.h"
#include "narf_fs.h"

#define ASSIGN =

void loop(void) {
   char buffer[1024];
   bool result;

   printf("#>");
   while(gets(buffer)) {

      if (!strncmp(buffer, "exit", 4)) {
         break;
      }
      else if (!strncmp(buffer, "mkfs", 4)) {
         printf("narf_mkfs()=%d\n", result ASSIGN narf_mkfs());
      }
      else if (!strncmp(buffer, "init", 4)) {
         printf("narf_init()=%d\n", result ASSIGN narf_init());
      }
      else if (!strncmp(buffer, "rebalance", 9)) {
         narf_rebalance();
      }
      else if (!strncmp(buffer, "debug", 5)) {
         narf_debug();
      }
      else if (!strncmp(buffer, "sync", 4)) {
         printf("narf_sync()=%d\n", result ASSIGN narf_sync());
      }
      else if (!strncmp(buffer, "alloc", 5)) {
         char key[256];
         int size;
         sscanf(buffer, "alloc %s %d", key, &size);
         printf("narf_alloc(%s,%d)=%d\n", key, size, result ASSIGN narf_alloc(key, size));
      }
      else if (!strncmp(buffer, "free", 4)) {
         char key[256];
         sscanf(buffer, "free %s", key);
         printf("narf_free(%s)=%d\n", key, result ASSIGN narf_free(key));
      }
      else {
         printf("huh?\n");
      }

      printf("#>");
   }
}

int main(int argc, char **argv) {
   bool result;

   printf("NARF example\n");

   printf("narf_io_open()=%d\n", result ASSIGN narf_io_open());

   if (result) {
      printf("narf_io_sectors()=%08X\n", narf_io_sectors());

      loop();

      printf("narf_io_close()=%d\n", result ASSIGN narf_io_close());
   }
}

// vim:set ai softtabstop=3 shiftwidth=3 tabstop=3 expandtab: ff=unix
