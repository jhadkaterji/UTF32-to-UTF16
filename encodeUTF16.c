//Jhad Katerji
//CS520 Lab2
//9/05/2018

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    
    //Variable Declarations
int endian;
int bomCheck1;
int bomCheck2;
int bomCheck3;
int bomCheck4;
int primeRead1;
int primeRead2;
int primeRead3;
int primeRead4;
    int val;
    int leftside;
    int val2;


FILE * checkFile;
FILE * outFile;
    
    //Check to make sure there are the right amount of arguments
if (argc != 3){
  printf("INCORRECT ARGUMENTS");
  exit (-1);
}
    
    
    //We are opening the file, and checking to see if it can be read.
checkFile = fopen (argv[1], "r");
outFile = fopen (argv[2], "w");
    
//Check the BOM, decide if it's little Endian or big Endian or neither.
bomCheck1 = getc(checkFile);
bomCheck2 = getc(checkFile);
bomCheck3 = getc(checkFile);
bomCheck4 = getc(checkFile);

    
    if (bomCheck1 == 0x00 && bomCheck2 == 0x00 && bomCheck3 == 0xfe && bomCheck4 == 0xff){
    endian = 1;
    //printf("Big Endian");
    }
    
    else if (bomCheck1 == 0xff && bomCheck2 == 0xfe && bomCheck3 == 0x00 && bomCheck4 == 0x00 ){
    endian = 0;
    //printf("Little Endian");
    }
    
    else{
    printf("File is NOT VALID");
    exit (-1);
	}
    
    

    
    
        ////////////IF ITS BIG ENDIAN AND OUTSIDE PLANE 0/////////////
if (endian ==1){
    
    primeRead1 = getc(checkFile);
while (primeRead1 != EOF){
//    printf ("%d\n", primeRead1);
    primeRead2 = getc(checkFile);
//    printf("%d\n", primeRead2);
    primeRead3 = getc(checkFile);
    primeRead4 = getc(checkFile);
    val = ( (primeRead1 <<8) | (primeRead2) );
    val = ( (val<<8|(primeRead3)));
    val = ( (val<<8|(primeRead4)));
    val = val-0x10000;
//    printf ("%d\n", val);
    leftside = (val & 0xFFC00);
    leftside = (val>>10);
//    printf ("%d\n", leftside);
    val2 = (val & 0x3FF);
    
leftside = (leftside+0xd800);
val2=(val2+0xdc00);
//    printf ("%d\n", leftside);
//    printf("%d\n", val2);
    
if ((val2 >= 0xdc00 && val2 <= 0xdfff)&& (leftside>=0xd800 && leftside<=0xdbff) )
{
putc (bomCheck3, outFile);
putc (bomCheck4, outFile);
putc (leftside>>8, outFile);
putc (leftside, outFile);
putc(val2>>8, outFile);
putc (val2, outFile);
    fclose (outFile);
}
    
    else{
putc (bomCheck3, outFile);
putc (bomCheck4, outFile);
//printf("%d\n", primeRead3);
//printf("%d\n", primeRead4);
putc (primeRead3, outFile);
putc (primeRead4, outFile); 
        fclose (outFile);
        
    }
    
primeRead1 = getc(checkFile);   
}    
}
    
    

    
    
    
    
    

    
/////////////IF ENDIAN = 0///////////////////
    if (endian ==0){
    
    primeRead1 = getc(checkFile);
while (primeRead1 != EOF){
    
    primeRead2 = getc(checkFile);
    
    primeRead3 = getc(checkFile);
    primeRead4 = getc(checkFile);
    val = ( (primeRead4 <<8) | (primeRead3) );
    val = ( (val<<8|(primeRead2)));
    val = ( (val<<8|(primeRead1)));
    val = val-0x10000;
//    printf ("%d\n", val);
    leftside = (val & 0xFFC00);
    leftside = (val>>10);
//    printf ("%d\n", leftside);
    val2 = (val & 0x3FF);
leftside = leftside+0xd800;
val2=val2+0xdc00;
//    printf("%d\n", leftside);
//    printf("%d\n", val2);
    
if ((leftside>=0xd800 && leftside<=0xdbff) && (val2 >= 0xdc00 && val2 <= 0xdfff))
{
putc (bomCheck1, outFile);
putc (bomCheck2, outFile);
putc (leftside, outFile);
putc (leftside>>8, outFile);
putc (val2, outFile);
putc(val2>>8, outFile);
    fclose (outFile);

}
    else{
        
    putc (bomCheck1, outFile);
    putc (bomCheck2, outFile);
//        printf("%d\n", primeRead1);
//        printf("%d\n", primeRead2);
    putc (primeRead1, outFile);
    putc (primeRead2, outFile);   
fclose (outFile);
        
    }
       
primeRead1 = getc(checkFile);   
}    
}
    
    
    
  
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
       
    
}