# map_lib
An associative-array library written in C.

Please see the blog post at: https://lawlessguy.wordpress.com/2016/02/11/a-simple-associative-array-library-in-c/

Have fun. I hope you find this little library useful.

# Error checks and some code revamping - July 2021
A couple of issues had been brought to my attention.  One pertained to the lack of NULL checks.  Another pointed out that I should really update the function signatures so that they properly reflected the access types of the char pointers being passed into the functions.

I revamped the primary data structure, *struct map_t*, so that no longer served as a node in a link list.  A new data structure, *struct map_link_t*, was created as a replacement.  *struct map_t* now acts as an anchor point for the list.  It also houses error code and error line information for errors that occur in the function calls. I didn't want to write error messages to stderr directly or anything like that, so the approach is to call a function and then to check the *error_code* value upon return.  If the error_code entry is zero, the function should have succeeded.  Please refer to the test program map_stuff.c to see how the error checks have been instrumented into the calling code.

I also added the functoin *map_destroy()* which will remove all of the strings in the linked list, the links, and the anchoring map_t structure.

I added a Windows batch file *map_comp.bat* as I no longer have a working Mac to use to compile that version of the library.

# I restored some old code - October 2018
Some time ago, I overlaid the original sources for the library and I had gotten rid of the git repo that held them. The files that had been hosted here for a while were a work-in-progress that ... well ... didn't work.

I was able to pull the original sources from the Wayback Machine tonight.  I had to make a few mods ... adapting the Windows-specific stuff to something that is more Mac-centric.






