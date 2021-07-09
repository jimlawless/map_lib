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

#ifndef MAP_LIB_H
#define MAP_LIB_H

struct map_link_t {
   struct map_link_t *nxt;
   char *name;
   char *value;
} ;


struct map_t {
	struct map_link_t *head;
	int error_code;
	int error_line;
} ;

#define MAP_ERR_OK (0)
#define MAP_ERR_NULL_PARM (1)
#define MAP_ERR_NULL_MALLOC (2)

struct map_t *map_create();
void map_set(struct map_t *m,const char *name,const char *value);
const char *map_get(struct map_t *m,const char *name);
void map_destroy(struct map_t *m);
#endif

