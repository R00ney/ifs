
#include<stdio.h> 
#include "../Linux64/hdr/ifs.h"
//#include <ifs.h>
#include <math.h>

int apply_hx(IFSIMG img, int x, int y);
int apply_hy(IFSIMG img, int x, int y);


int main(void) {
	IFSIMG img1, img2, img3; /*Declare pointers to headers */
	IFSIMG in1, in2, in3; /*input images*/
	IFSIMG th1, th2, th3; /*threshold images*/
	
	int len[3]; /*len is an array of dimensions, used by ifscreate*/
	int row,col;/*counters */
	int m = 64;/*image has 64 columns */ 
	int n = 64;/*image has 64 rows */

	int temp1, temp2, temp3;
	
	int threshold = 150; /*threshold for edges in images */
	
	len[0]=2; /*image to be created is two dimensional */
	len[1]=n; 
	len[2]=m; 
	
	img1=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;/*image is unsigned 8bit */
	img2=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;
	img3=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;

	th1=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;/*image is unsigned 8bit */
	th2=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;
	th3=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;
	
	in1=ifspin("SYNTH1.ifs");/*read in file by this name */	
	in2=ifspin("BLUR1.");
	in3=ifspin("BLUR1.V1");

	
	/* apply kernels simultanteously, since all images should be same size */
	for(row=0;row< m;row++) 
		for(col=0;col< n;col++)
		{
			/*SYNTH.ifs image*/
			/* calculate x and y sobels*/
			temp1 = apply_hx(in1, row, col);
			temp2 = apply_hy(in1, row, col);
			/* calculate magnitude*/
			temp3 = (int) sqrt(temp1*temp1 + temp2*temp2);
			/*save to image */
			ifsipp(img1, row, col, temp3);
			
			/*apply threshold*/
			if(temp3 >= threshold)
				ifsipp(th1, row, col, 1);
			else
				ifsipp(th1, row, col, 0);
			
			/*BLUR1. image*/
			/* calculate x and y sobels*/
			temp1 = apply_hx(in2, row, col);
			temp2 = apply_hy(in2, row, col);
			/* calculate magnitude*/
			temp3 = (int) sqrt(temp1*temp1 + temp2*temp2);
			/*save to image */
			ifsipp(img2, row, col, temp3);
			
			/*apply threshold*/
			if(temp3 >= threshold)
				ifsipp(th2, row, col, 1);
			else
				ifsipp(th2, row, col, 0);
			
			
			/* BLUR1.V1 image */
			/* calculate x and y sobels*/
			temp1 = apply_hx(in3, row, col);
			temp2 = apply_hy(in3, row, col);
			/* calculate magnitude*/
			temp3 = (int) sqrt(temp1*temp1 + temp2*temp2);
			/*save to image */
			ifsipp(img3, row, col, temp3);
			
			/*apply threshold*/
			if(temp3 >= threshold)
				ifsipp(th3, row, col, 1);
			else
				ifsipp(th3, row, col, 0);
			
		} 

	ifspot(img1,"SYNTH_edges.ifs"); /*write  synth's edge image to disk */
	ifspot(img2,"BLUR1_edges.ifs"); /*write  BLUR1's edge image to disk */
	ifspot(img3,"BLUR1V1_edges.ifs"); /*write  BLUR1V1's edge image to disk */
	
	ifspot(th1,"SYNTH_thresh.ifs"); /*write  synth's thresh image to disk */
	ifspot(th2,"BLUR1_thresh.ifs"); /*write  BLUR1's thresh image to disk */
	ifspot(th3,"BLUR1V1_thresh.ifs"); /*write  BLUR1V1's thresh image to disk */
	
	return 1;
}


/* kernel wraps around image boundries */
int apply_hx(IFSIMG img, int x, int y)
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
			/*handel edge wrap*/
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
			/*apply kernel of 1/8*[[-1 0 1][-2 0 2][-1 0 1]] */
			total= total + i*temp;
			if( (j==0))
				total = total + i*temp; /*for 2 times */

		}
	total = (int)total/8;
	return total;		
}

/* kernel wraps around image boundries */
int apply_hy(IFSIMG img, int x, int y)
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
			/*handel edge wrap*/
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
			/*apply kernel of 1/8*[[-1 -2 -1][0 0 0][1 2 1]] */
			total= total + j*temp;
			if( (i==0))
				total = total + j*temp; /*for 2 times */

		}
	total = (int)total/8;
	return total;		
}
