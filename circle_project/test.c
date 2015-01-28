/* Test program  Neal O'Hara  1/27/15 */

/*
#include <stdio.h>

void main()
{
	printf ("Howdy, neighbor! This is my first C program.\n");
        //return 0;
	
}
*/

#include<stdio.h> 
//#include<home/ngohara/Dropbox/763_ECE/ifs/Linux64/hdr/ifs.h>
#include "test.h"
#include "../Linux64/hdr/ifs.h"
#include "../Linux64/hdr/ifserr.h" /*optional*/

main() {
	IFSIMG img1,img2; /*Declare pointers to headers */
	int len[3]; /*len is an array of dimensions, used by ifscreate*/
	int threshold;/*threshold is an int here */ 
	int row,col;/*counters */
	int v; 
	
	img1=ifspin("infile.ifs");/*read in file by this name */
	len[0]=2;/*image to be created is two dimensional */
	len[1]=128;/*image has 128 columns */
	len[2]=128;/*image has 128 rows */
	img2=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;/*image is unsigned 8bit */
	threshold=55;/*set some value to threshold */
	for(row=0;row< 128;row++) 
		for(col=0;col< 128;col++)
		{
			v=ifsigp(img1,row,col);/*read a pixel as an int*/
			if(v<threshold)
				ifsipp(img2,row, col ,255); 
			else 
				ifsipp(img2, row, col, 0);
		} 
	ifspot(img2,"img2.ifs"); /*write image 2 to disk */
}

