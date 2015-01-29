

#include<stdio.h> 
#include "../Linux64/hdr/ifs.h"

int blur(IFSIMG img, int x, int y);

main() {
	IFSIMG img1, img2; /*Declare pointers to headers */
	int len[3]; /*len is an array of dimensions, used by ifscreate*/
	int row,col;/*counters */
	int m = 64;/*image has 64 columns */ 
	int n = 64;/*image has 64 rows */

	int temp;
	
	len[0]=2; /*image to be created is two dimensional */
	len[1]=n; 
	len[2]=m; 
	
	img1=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;/*image is unsigned 8bit */
	img2=ifspin("SYNTH1.ifs");/*read in file by this name */	
	

	/* blur */
	for(row=0;row< m;row++) 
		for(col=0;col< n;col++)
		{
			temp = blur(img2, row, col);
			ifsipp(img1, row, col, temp);
		} 

	ifspot(img1,"BLUR1."); /*write  blur image to disk */
}


/* blur wraps around image boundries */
int blur(IFSIMG img, int x, int y)
{
	int m = 64;/*image has 64 columns */ 
	int n = 64;/*image has 64 rows */
	//int pix[3][3]; /* nine pixels */
	int temp = 0;
	int total = 0;
	int ic, jc;
	int i, j; /*count*/
	
	for(i=-1;i<2;i++)
		for(j=-1;j<2;j++)
		{
			if((x+i) < 0)
				ic = m-1;
			else if((x+i) > (m-1))
				ic = 0;
			else
				ic = x+i;
			
			if((y+j) < 0)
				jc = n-1;
			else if((y+j) > (n-1))
				jc = 0;
			else
				jc = y+j;
			
			temp=  ifsigp(img,ic,jc);
			/*apply kernel of 1/10*[[1 1 1][1 2 1][1 1 1]] */
			total= total+temp;
			
			if( (i==0)&&(j==0))
				total = total + temp;
			
				if( (x<2)&&(y<2))
					printf("%d %d  %d   %d\n",ic, jc, temp, total);
		}
	total = (int)total/10;
	
	//if( (x<5)&&(y<5))
	//	printf("%d\n",total);
	return total;		
}

