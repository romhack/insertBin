/*

Insert binary file into another file at given offset
Griever.magicteam.net

Usage:
insertBin patch.bin target.bin [-o offset][-s size] [-f fillValue]

offset - default 0
size - target size of patch, if patch.bin is greater, insertBin returns error, if greater allign to size with 0's or fillValue.
fillValue - if patch is greater, alligns patch.bin with given value.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned char u8;

int     main (int argc, char **argv)
{
u8* inputBuffer;
FILE* f_in, *f_out;
int offset = 0;
u8 fillByte = 0;
size_t sizeMaster = 0;



	if (argc > 2)
	{
		if (!(f_in = fopen(argv[1], "rb")))
		{
			fprintf(stderr,"Cannot open input file: %s\n", argv[1]);
			getchar();
			exit (EXIT_FAILURE);
		}
		if (!(f_out = fopen(argv[2], "rb+")))
		{
			fprintf(stderr,"Cannot open input file: %s\n", argv[2]);
			fclose(f_in);
			getchar();
			exit (EXIT_FAILURE);
		}

		//processing optional arguments
		int c;
		opterr = 0;    
		while ((c = getopt (argc, argv, "o:s:f:")) != -1)
         switch (c)
           {
           case 'o':
             offset = strtol ( optarg, NULL, 0);
             break;
           case 's':
             sizeMaster = strtol ( optarg, NULL, 0);
             break;
           case 'f':
             fillByte = strtol ( optarg, NULL, 0) & 0xFF;
             break;
           case '?':
			if (optopt == 'o' || optopt == 's' || optopt == 'f' )
				fprintf (stderr, "Option -%c requires an argument. Set to default.\n", optopt);
			else
				fprintf (stderr, "Unknown option character: %c.\n", optopt);	
           default:
			 ;
           }

		
		

		fseek(f_in, 0, SEEK_END);
		size_t f_size = ftell(f_in);
		fseek(f_in, 0, SEEK_SET);
		if ((sizeMaster != 0) & (f_size > sizeMaster))
		{
			fprintf(stderr, "Patch size is larger than specified. Aborted.\n");
			fclose(f_in);
			fclose(f_out);
			getchar();
			exit (EXIT_FAILURE);
		}
		inputBuffer = (u8*)malloc(f_size);
		fread(inputBuffer, f_size, sizeof(u8), f_in);
		fseek(f_out, offset, SEEK_SET);
		fwrite(inputBuffer, f_size, sizeof(u8), f_out);		
		free (inputBuffer);
		
		if (sizeMaster != 0)
			while (f_size++ < sizeMaster)//append patch with fillByte
				fwrite(&fillByte, 1, sizeof(u8), f_out);
		
		fclose(f_in);
		fclose(f_out);
		printf("Inserted successfully\n");
		getchar();
	}
	else//not enough arguments
	{
		fprintf(stderr,"Usage: insertBin patch.bin target.bin [-o offset][-s size] [-f fillValue]\n");		
		getchar();
		exit (EXIT_FAILURE);
	}
	return 0;
}