#include <stdio.h>
#include "map_lib.h"

void display_both(struct map_t *m,char *key);

int main(int argc,char **argv) {
   struct map_t *test;

   test=map_create();
   if(test==NULL) {
      fprintf(stderr,"Cannot create map_t struct\n");
	  return 1;
   }
   map_set(test,"One","Won");
   if(test->error_code) {
      fprintf(stderr,"Error %d in line %d of map_lib.c\n",test->error_code, test->error_line);
	  return 1;
   }
   map_set(test,"Two","Too");
   if(test->error_code) {
      fprintf(stderr,"Error %d in line %d of map_lib.c\n",test->error_code, test->error_line);
	  return 1;
   }
   map_set(test,"Four","Fore");
   if(test->error_code) {
      fprintf(stderr,"Error %d in line %d of map_lib.c\n",test->error_code, test->error_line);
	  return 1;
   }

      // display them out of order
   display_both(test,"Two");
   display_both(test,"Four");
   display_both(test,"One");

   printf("\n");

      // reset an existing entry
   map_set(test,"Two","To");
   if(test->error_code) {
      fprintf(stderr,"Error %d in line %d of map_lib.c\n",test->error_code, test->error_line);
	  return 1;
   }

   display_both(test,"Two");
   display_both(test,"Four");
   display_both(test,"One");

   printf("\n");

   display_both(test,"Eight");

   map_set(test,"Eight","Ate");

   printf("\n");

   display_both(test,"Eight");
   printf("---\n");

   // test some null checking
   map_set(test,NULL,"nothing");
   if(test->error_code) {
      fprintf(stderr,"Error %d in line %d of map_lib.c\n",test->error_code, test->error_line);
   }
   map_set(test,"nothing",NULL);
   if(test->error_code) {
      fprintf(stderr,"Error %d in line %d of map_lib.c\n",test->error_code, test->error_line);
   }   
}

void display_both(struct map_t *m,char *first) {
   printf("%s %s\n",first,map_get(m,first));
}

