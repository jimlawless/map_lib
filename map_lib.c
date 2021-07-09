// map_lib
// A simple associative-array library for C
//
// License: MIT / X11
// Copyright (c) 2009-2021 by James K. Lawless
// jimbo@radiks.net 
// https://jiml.us
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

// 8 July 2021 
// - Requested fixes (char * needed to be changed to const char *)
// - Changed map_t structure to anchor the link list and to hold additional            
// - information about the map, such as error information.  
// - Added error constants.  I decided to not use an enum.
// - Added map_link_t to refer to the nodes in the linked list
// - Added better checks for NULL after adding the error attributes in map_t
// - Added map_destroy() to clear all nodes, all strings referenced by nodes, and
//   the root map_t structure.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "map_lib.h"

struct map_t *map_create() {
   struct map_t *m;
   m=(struct map_t *)malloc(sizeof(struct map_t));
   if(m==NULL)
	  return NULL;
   m->head=(struct map_link_t *)malloc(sizeof(struct map_link_t));
   if(m->head==NULL) {
	  m->error_code=MAP_ERR_NULL_MALLOC;
      m->error_line=__LINE__;
	  return m;
   }
   m->head->name=NULL;
   m->head->value=NULL;
   m->head->nxt=NULL;
   
   m->error_code=MAP_ERR_OK;
   m->error_line=-1;
   return m;
}

void map_set(struct map_t *m,const char *name,const char *value) {
   struct map_link_t *map;

   if(m==NULL)
	  return;
   m->error_code=0;
   m->error_line=0;

   if((name==NULL)||(value==NULL)) {
      m->error_code=MAP_ERR_NULL_PARM;
      m->error_line=__LINE__;
	  return;
   }	  

   if(m->head->name==NULL) {
      m->head->name=(char *)malloc(strlen(name)+1);
	  if(m->head->name==NULL) {
		 m->error_code=MAP_ERR_NULL_MALLOC;
		 m->error_line=__LINE__;
		 return;
	  }
      strcpy(m->head->name,name);
      m->head->value=(char *)malloc(strlen(value)+1);
	  if(m->head->value==NULL) {
		 m->error_code=MAP_ERR_NULL_MALLOC;
		 m->error_line=__LINE__;
		 return;
	  }
      strcpy(m->head->value,value);
      m->head->nxt=NULL;
      return;
   }
   for(map=m->head;;map=map->nxt) {
      if(!strcasecmp(name,map->name)) {
         if(map->value!=NULL) {
            free(map->value);
            map->value=(char *)malloc(strlen(value)+1);
			if(map->value==NULL) {
		       m->error_code=MAP_ERR_NULL_MALLOC;
		       m->error_line=__LINE__;
		       return;
			}				
            strcpy(map->value,value);
            return;
         }
      }
      if(map->nxt==NULL) {
         map->nxt=(struct map_link_t *)malloc(sizeof(struct map_t));
		 if(map->nxt==NULL) {
            m->error_code=MAP_ERR_NULL_MALLOC;
	        m->error_line=__LINE__;
			return;
	     }		 
         map=map->nxt;
         map->name=(char *)malloc(strlen(name)+1);
		 if(map->name==NULL) {
            m->error_code=MAP_ERR_NULL_MALLOC;
	        m->error_line=__LINE__;
			return;
	     }
         strcpy(map->name,name);
         map->value=(char *)malloc(strlen(value)+1);
		 if(map->value==NULL) {
            m->error_code=MAP_ERR_NULL_MALLOC;
	        m->error_line=__LINE__;
			return;
	     }
         strcpy(map->value,value);
         map->nxt=NULL;
         return;
      }
   }
}

const char *map_get(struct map_t *m,const char *name) {
   struct map_link_t *map;
   for(map=m->head;map!=NULL;map=map->nxt) {
      if(!strcasecmp(name,map->name)) {
         return map->value;
      }
   }
   return "";
}

void map_destroy(struct map_t *m) {
   struct map_link_t *map,*tmp;
   for(map=m->head;map!=NULL;) {
	   if(map->name!=NULL)
	      free(map->name);
	   if(map->value!=NULL)
		   free(map->value);
	   tmp=map;
	   map=map->nxt;
	   free(map);
   }	
}
