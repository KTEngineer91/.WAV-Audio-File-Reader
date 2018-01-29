#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>




main()
{
    char rfile[100], wfile[100];
    FILE *fin, *fout;

    while(1)
    {

        printf("Enter the path/filename for the input audio file: ");
        scanf("%s", rfile);


        if (strstr(rfile,".wave")!=0||strstr(rfile,".wav")!=0||strstr(rfile,".WAVE")!=0||strstr(rfile,".WAV")!=0)
            goto start;
        else
        {
            printf("Error: Must be a .wav file.\n");
            continue;
        }

        start:

        fin=fopen(rfile,"rb");

        if (fin==0)
        {
            printf("The path is incorrect.\n");
            continue;
        }
        break;
    }


    unsigned char chunkID[5], format[5], subchunk_1_ID[5], subchunk_2_ID[5];
    unsigned int chunkSize, subchunk_1_size, sampleRate, byteRate, subchunk_2_size;
    unsigned short int audioFormat, numChannels, blockAlign, bitsPerSample;


    fread(chunkID,sizeof(unsigned char),4,fin);
    chunkID[4]='\0';
    printf("\nChunkID: %s\n", chunkID);

    fread(&chunkSize,sizeof(unsigned int),1,fin);
    printf("ChunkSize: %u\n",chunkSize);

    fread(format,sizeof(unsigned char),4,fin);
    format[4]='\0';
    printf("Format: %s\n",format);

    fread(subchunk_1_ID,sizeof(unsigned char),4,fin);
    subchunk_1_ID[4]='\0';
    printf("Subchunk1ID: %s\n",subchunk_1_ID);

    fread(&subchunk_1_size,sizeof(unsigned int),1,fin);
    printf("Subchunk1Size: %u\n",subchunk_1_size);

    fread(&audioFormat,sizeof(unsigned short int),1,fin);
    printf("AudioFormat: %hu\n",audioFormat);

    fread(&numChannels,sizeof(unsigned short int),1,fin);
    printf("NumChannels: %hu\n",numChannels);

    fread(&sampleRate,sizeof(unsigned int),1,fin);
    printf("SampleRate: %u\n",sampleRate);

    fread(&byteRate,sizeof(unsigned int),1,fin);
    printf("ByteRate: %u\n",byteRate);

    fread(&blockAlign,sizeof(unsigned short int),1,fin);
    printf("BlockAlign: %hu\n",blockAlign);

    fread(&bitsPerSample,sizeof(unsigned short int),1,fin);
    printf("BitsPerSample: %hu\n",bitsPerSample);

    fread(subchunk_2_ID,sizeof(unsigned char),4,fin);
    subchunk_2_ID[4]='\0';
    printf("Subchunk2ID: %s\n", subchunk_2_ID);

    fread(&subchunk_2_size,sizeof(unsigned int),1,fin);
    printf("Subchunk2Size: %u\n\n",subchunk_2_size);

    while(1)
    {
        printf("Enter the path/filename for the output audio file: ");
        scanf("%s", wfile);


        if (strstr(wfile,".wave")!=0||strstr(wfile,".wav")!=0||strstr(wfile,".WAVE")!=0||strstr(wfile,".WAV")!=0)
            goto start1;
        else
        {
            printf("Error: Must be a .wav file.\n");
            continue;
        }

        start1:

        fout=fopen(wfile,"wb");

        if (fout==0)
        {
            printf("The path is incorrect.\n");
            continue;
        }
        break;
    }

    rewind(fin);
    unsigned int* copied;
    copied=(unsigned int*)calloc((chunkSize+8),1);

    fread(copied,1,chunkSize+8,fin);
    fwrite(copied,1,chunkSize+8,fout);

    fclose(fin);

    sampleRate *= 2;
    byteRate=(sampleRate*numChannels*bitsPerSample)/8;


    fseek(fout,24,SEEK_SET);
    fwrite(&sampleRate,sizeof(unsigned int),1,fout);
    fseek(fout,28,SEEK_SET);
    fwrite(&byteRate,sizeof(unsigned int),1,fout);
    printf("\n%s has been created with double playback speed of %s.\n\n", wfile, rfile);
    fclose(fout);

    system("pause");
}

