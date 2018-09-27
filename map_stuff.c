#include <stdio.h>
#include "map_lib.h"

void display_both(struct map_t *m,char *key);

int main(int argc,char **argv) {
   struct map_t *test;

   test=map_create();
   map_set(test,"One","Won");
   map_set(test,"Two","Too");
   map_set(test,"Four","Fore");

      // display them out of order
   display_both(test,"Two");
   display_both(test,"Four");
   display_both(test,"One");

   printf("\n");

      // reset an existing entry
   map_set(test,"Two","To");

   display_both(test,"Two");
   display_both(test,"Four");
   display_both(test,"One");

   printf("\n");

   display_both(test,"Eight");

   map_set(test,"Eight","Ate");

   printf("\n");

   display_both(test,"Eight");
}

void display_both(struct map_t *m,char *first) {
   printf("%s %s\n",first,map_get(m,first));
}

