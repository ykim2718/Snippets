// yNumRecipe.c : Defines the entry point for the console application.
// Yongshik Kim (copyRight) 2016.3.26

#include <stdio.h>
#include "yNr4.h"

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

int __cdecl main()
{
	int values[] = { 1,2,3,4,-1,-2,-3,-4 };
	demo_Fig_33_on_page_52();
	demo_Fig_35_on_page_54();
	demo_Fig_40_on_page_59();
	foreach (int *v, values) {
		demo_rectangle_9x9(*v);
	}
    getchar();
    return 0;
}

