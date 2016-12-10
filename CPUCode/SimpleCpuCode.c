/**
 * Document: MaxCompiler tutorial (maxcompiler-tutorial.pdf)
 * Chapter: 4      Example: 2      Name: Simple
 * MaxFile name: Simple
 * Summary:
 * 	 Takes a stream and for each value x calculates x^2 + x.
 */
#include <stdint.h>
#include <stdlib.h>
#include <MaxSLiCInterface.h>
#include "Maxfiles.h"

#define ROWS 6
#define COLS 8

uint64_t rows                   = ROWS;
uint64_t cols                   = COLS;
uint64_t threshold              = 150;
uint64_t one                    = 255;
uint64_t zero                   = 0;
int16_t *in_image ; 
int16_t *out_image   ; 
int16_t *exp_image ; 

int16_t static_in_image[ROWS][COLS]  =      

 { {254,254,254,255,255,255,254,255},
   {255,255,17,	7,	21,	21,	254,253},
   {255,255,8,  7,	0,	0,	253,255},
   {254,254,11,	2,	3,	3,	255,253},
   {255,255,7,	10,	0,	0,	255,255},
   {254,254,255,253,255,255,253,255}
 };
                                    
int16_t static_out_image[ROWS][COLS] ;


int16_t static_exp_image[ROWS][COLS] ;
                                         
float *in_eg;
float *in_ep;

int N = -1;

void halftone_calc(int16_t *_in_image, int16_t *_out_image, int _threshold,
            int _one, int _zero, int _rows, int _cols ){
    float c[2][3], sum_p, t;
    int i, j, m, n, xx, yy;                
    float eg[_rows][_cols];
    float ep[_rows][_cols];
     
     
    c[0][0] = 0.0;
    c[0][1] = 0.2;
    c[0][2] = 0.0;
    c[1][0] = 0.6;
    c[1][1] = 0.1;
    c[1][2] = 0.1;
    
    for(i=0; i<_rows; i++){
        for(j=0; j<_cols; j++){
            eg[i][j] = 0.0;
            ep[i][j] = 0.0;
        }
    }
    
    for(m=0; m<_rows; m++){
        for(n=0; n<_cols; n++){
            //printf("[DRIVER] counters[m, n]: %d , %d  threshold : %d  one : %d zero : %d \n",
              //              m, n, _threshold, _one, _zero);
            sum_p = 0.0;
                for(i=0; i<2; i++){
                    for(j=0; j<3; j++){
                        xx = m-i+1;
                        yy = n-j+1;
                        if(xx < 0) xx = 0;
                        if(xx >= _rows) xx = _rows-1;
                        if(yy < 0) yy = 0;
                        if(yy >= _cols) yy = _cols-1;
                        sum_p = sum_p + c[i][j] * eg[xx][yy];
                        //printf("[DRIVER] [m, n]: %d , %d ==> [xx, yy]: %d , %d  sumpval ==> %f \n",
                        //m, n, xx, yy, sum_p);
                    } /* ends loop over j */
                } /* ends loop over i */
            ep[m][n] = sum_p;
            t = _in_image[m*_rows + n] + ep[m][n];
            
            if(t > _threshold){
                eg[m][n] = t - _threshold*2;
                _out_image[m*_rows + n] = _one;
            } /* ends if t > threshold */
            else{ /* t <= threshold */
                eg[m][n] = t;
                _out_image[m*_rows + n] = _zero;
            } /* ends else t <= threshold */
        } /* ends loop over n columns */
    } 
                
}


int check(int16_t *dataOut, int16_t *expected, int size)
{
	int status = 0;
	for(int i=0; i < size; i++)
	{
		if(dataOut[i] != expected[i]) {
			/*fprintf(stderr, "Output data @ %d = %hd (expected %hd)\n",
				i, dataOut[i], expected[i]);*/
			status = 1;
		}else {
		   /*fprintf(stderr, "Test OK for Output data @ %d = %hd (expected %hd)\n",
				i, dataOut[i], expected[i]); */
		}
	}
	return status;
}

#define BLK   "\x1B[31m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define COLOR 


void print(int16_t *img, char* msg){
    int i, j;
    printf("========== printing %s ===========\n", msg);
    for(i = 0 ; i < ROWS ;i++){
        for(j = 0 ; j < COLS ; j++){
            int16_t col = img[i*COLS + j];
            printf(COLOR "%4hd", col);  
        }
        printf("\n");
    }
    printf("====== End of printing %s =======\n", msg);

}

int main()
{
    int i, j;
    N = (ROWS)*(COLS);
    posix_memalign(&in_image, 16, sizeof(int16_t)*N );
    posix_memalign(&out_image, 16, sizeof(int16_t)*N );
    posix_memalign(&in_eg, 16, sizeof(float)*N );
    posix_memalign(&in_ep, 16, sizeof(float)*N );


    exp_image   = (int16_t*) malloc(sizeof(int16_t)*N);
    
    for(i = 0 ; i < ROWS ;i++){
        for(j = 0 ; j < COLS ; j++){
            in_image[i*COLS + j]  = i + j; 
            exp_image[i*COLS + j] = i + j;
            out_image[i*COLS + j] = 0;
            //input eg,ep
            in_eg[i*COLS + j] = 0.0;
            in_ep[i*COLS + j] = 0.0;

        }
    }
    
    Simple(N, cols, one, rows, threshold, zero, (const float *) in_eg, (const float *) in_ep, (const int16_t*) static_in_image[0], static_out_image[0]);
    
	printf("Running DFE halftone.\n");
	
	halftone_calc(static_in_image[0], static_exp_image[0], (int) threshold, (int) one, (int) zero, (int)(ROWS), (int) (COLS));
	int status = check(static_out_image[0], static_exp_image[0], N);
    print(static_in_image[0], "source img");
    print(static_out_image[0], "half toned img");

	if (status)
		printf("Test failed.\n");
	else
		printf("Test passed OK!\n");
	return 0;
}