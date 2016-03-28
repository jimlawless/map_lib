// map_lib
// A simple associative-array library for C
//
// License: MIT / X11
// Copyright (c) 2009, 2015 by James K. Lawless
// jimbo@radiks.net http://jiml.us
// See: http://www.mailsend-online.com/license2015.php

#ifndef MAP_LIB_H
#define MAP_LIB_H

typedef enum {
   MAP_OF_STRINGS=0,
   MAP_OF_INTS,
   MAP_OF_STRUCTS
} map_type ;

struct map_t {
   struct map_t *nxt;
   char *name;
   map_type tag;
   union {
      char *value;
      int intValue;
      void *structValue;
   } v;
} ;


struct map_t *map_create();
void map_free(struct map_t *map);
void map_set(struct map_t *m,char *name,char *value);
char *map_get(struct map_t *m,char *name);

struct map_t *map_int_create();
void map_int_set(struct map_t *m,char *name, int intValue);
int map_int_get(struct map_t *m,char *name);

struct map_t *map_struct_create();
void map_struct_set(struct map_t *m,char *name, void *structValue);
void *map_struct_get(struct map_t *m,char *name);


#endif
 
