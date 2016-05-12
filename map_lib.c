// map_lib
// A simple associative-array library for C
//
// License: MIT / X11
// Copyright (c) 2009, 2012 by James K. Lawless
// jimbo@radiks.net http://www.radiks.net/~jimbo
// http://www.mailsend-online.com
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "map_lib.h"

struct map_t *map_create() {
   struct map_t *m;
   m=(struct map_t *)malloc(sizeof(struct map_t));
   m->name=NULL;
   m->value=NULL;
   m->nxt=NULL;
}


void map_set(struct map_t *m,char *name,char *value) {
   struct map_t *map;

   if(m->name==NULL) {
      m->name=(char *)malloc(strlen(name)+1);
      strcpy(m->name,name);
      m->value=(char *)malloc(strlen(value)+1);
      strcpy(m->value,value);
      m->nxt=NULL;
      return;
   }
   for(map=m;;map=map->nxt) {
      if(!strcasecmp(name,map->name)) {
         if(map->value!=NULL) {
            free(map->value);
            map->value=(char *)malloc(strlen(value)+1);
            strcpy(map->value,value);
            return;
         }
      }
      if(map->nxt==NULL) {
         map->nxt=(struct map_t *)malloc(sizeof(struct map_t));
         map=map->nxt;
         map->name=(char *)malloc(strlen(name)+1);
         strcpy(map->name,name);
         map->value=(char *)malloc(strlen(value)+1);
         strcpy(map->value,value);
         map->nxt=NULL;
         return;
      }      
   }
}

char *map_get(struct map_t *m,char *name) {
   struct map_t *map;
   for(map=m;map!=NULL;map=map->nxt) {
      if(!strcasecmp(name,map->name)) {
         return map->value;
      }
   }
   return "";
}
 

void *map_get_ptr(struct map_t *m,char *name) {
   struct map_t *map;
   for(map=m;map!=NULL;map=map->nxt) {
      if(!strcasecmp(name,map->name)) {
         return map->value;
      }
   }
   return NULL;
}

void map_set_ptr(struct map_t *m,char *name, void *value) {
   struct map_t *map;

   if(m->name==NULL) {
      m->name=(char *)malloc(strlen(name)+1);
      strcpy(m->name,name);
      m->value=value;
      m->nxt=NULL;
      return;
   }
   for(map=m;;map=map->nxt) {
      if(!strcasecmp(name,map->name)) {
         map->value=value;
            return;
      }
      if(map->nxt==NULL) {
         map->nxt=(struct map_t *)malloc(sizeof(struct map_t));
         map=map->nxt;
         map->name=(char *)malloc(strlen(name)+1);
         strcpy(map->name,name);
         map->value=value;
         map->nxt=NULL;
         return;
      }      
   }   
}

void map_free_strings(struct map_t *m) {
   struct map_t *map=m;
   for(map=m;map!=NULL;map=map->nxt) {
      if(map->name!=NULL) {
         free(map->name);
      }
      if(map->value!=NULL) {
         free(map->value);
      }      
   }
}

