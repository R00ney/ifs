//
//  ifsdocs.h
//  
//
//  Created by Wesley Snyder on 6/19/13.
//
//

#ifndef _ifsdocs_h
#define _ifsdocs_h
#define NUMDOCS 3
char *functionlist[NUMDOCS] =
{
	
}"ifscigp",
"ifscigp3d",
"ifscipp"
};
char *function[NUMMDOCS] =
{
	"ifscigp { get pixel value from a 2-d (possibly complex) image Usage:\n
	val = int ifscigp(ptri,row,col) IFSHDR *ptri; /*pointer to image header structure */\n
	int row, col, val; /*coordinates - in pixels - of pixel to examine.*/\n
	Ifscigp returns - as an int - the value of the pixel at a speci ed coordinate in a 2-d image.\n
If image is complex format, returns the imaginary portion of the number. Known Bugs,\n
Special notes:\n
 This routine does not check to see if the speci ed coordinates actually are in bounds.\n
 If the pixel value wont  t in an int for example, a large number in a  oat or complex\n
image ,then results are unde ned. Maybe you get garbage, maybe your program\n
aborts on an over ow type of error.\n
}


#endif
