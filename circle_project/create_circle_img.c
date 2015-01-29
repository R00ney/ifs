
#include<stdio.h> 
#include "../Linux64/hdr/ifs.h"

int in_circle(int r, int x, int y);

main() {
	IFSIMG img1; /*Declare pointers to headers */
	int len[3]; /*len is an array of dimensions, used by ifscreate*/
	int row,col;/*counters */
	int m = 64;/*image has 64 columns */ 
	int n = 64;/*image has 64 rows */
	int b = 10; /*black border offset */
	int radius = 22;
	
	len[0]=2; /*image to be created is two dimensional */
	len[1]=n; 
	len[2]=m; 
	
	img1=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;/*image is unsigned 8bit */
	
	/*Black background */
	for(row=0;row< m;row++) 
		for(col=0;col< n;col++)
		{
			ifsipp(img1, row, col, 10);
		} 
	
	/*Up Left Quad = 100 */
	for(row=b;row< m/2;row++) 
		for(col=b;col< n/2;col++)
		{
			if(in_circle(radius, row, col))
				ifsipp(img1, row, col, 100);
		} 

	/*Up Right Quad = 150 */
	for(row=b;row< m/2;row++) 
		for(col=n/2;col<n-b;col++)
		{
			if(in_circle(radius, row, col))
				ifsipp(img1, row, col, 150);
		} 

	/*Down Left Quad = 50 */
	for(row=m/2;row< m-b;row++) 
		for(col=b;col< n/2;col++)
		{
			if(in_circle(radius, row, col))
				ifsipp(img1, row, col, 50);
		} 

	/*Down Right Quad = 20 */	
	for(row=m/2;row< m-b;row++) 
		for(col=n/2;col< n-b;col++)
		{
			if(in_circle(radius, row, col))
				ifsipp(img1, row, col, 20);
		} 

		
	ifspot(img1,"SYNTH1.ifs"); /*write image 2 to disk */
}

/* 1 if point inside circle, 0 if not 
* assumes center at 32 32,  
*/
int in_circle(int r, int x, int y)
{
	return (((x - 32)*(x - 32) + (y-32)*(y-32)) < r*r);
}
