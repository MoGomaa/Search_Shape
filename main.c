#include <stdio.h>
#include <stdlib.h>

int Seek_NextLine(FILE *fp);

int main()
{
    FILE *fp_Shape;
    FILE *fp_Sample;
    fp_Shape = fopen("Shape.txt", "r");
    fp_Sample = fopen("Sample.txt", "r");

    char ch_Shape;
    char ch_Sample;
    int Shape_count = 0;
    int ch_pos_in_row = 0;
    int Shape_start_pos = 0;
    int Shape_start_falg = 0;

    //Looping on the fp_Sample
    do
    {
        ch_Shape = getc(fp_Shape);
        ch_Sample = getc(fp_Sample);

        // Special Case 1 : fp_Shape  end line -- (Move to next line)
        if(ch_Shape == '\n')
        {
            // The current chars are invaild
            // fp_Shape  : Take the next char
            if(ch_Sample != '\n')
            // fp_Sample : Move to the next line
                if(Seek_NextLine(fp_Sample) == -1)  // -1 means fp_Sample EOF
                    break;
            // Move to the Shape_start_pos
            // Take the next char
            ch_pos_in_row = Shape_start_pos;
            fseek(fp_Sample, Shape_start_pos, SEEK_CUR);
            continue;
        }

        // Special Case 2 : fp_Shape EOF -- (Shape found)
        if(ch_Shape == EOF)
        {
            Shape_count++;

            fseek(fp_Shape, 0, SEEK_SET);

            if(ch_Sample != '\n')
                fseek(fp_Sample, ftell(fp_Sample)-1, SEEK_SET);
            else    // Handel '\n' as it jumps +2 steps
                fseek(fp_Sample, ftell(fp_Sample)-2, SEEK_SET);

            Shape_start_pos = 0;
            Shape_start_falg = 0;
            continue;
        }

        // Special Case 3 : fp_Sample end line -- (Move to next line)
        if(ch_Sample == '\n')
        {
            ch_pos_in_row = 0;

            fseek(fp_Shape, 0, SEEK_SET);
            Shape_start_falg = 0;
            continue;
        }

        ch_pos_in_row++;
        if(ch_Sample==ch_Shape)
        {
            if(Shape_start_falg==0)
            {
                Shape_start_falg = 1;
                Shape_start_pos = ch_pos_in_row-1;
            }
        }
        else
        {
            fseek(fp_Shape, 0, SEEK_SET);
            Shape_start_falg = 0;
        }
    }while(ch_Sample != EOF);

    fclose(fp_Shape);
    fclose(fp_Sample);

    printf("\n\nNumber of shapes found : %d\n\n", Shape_count);
    return 0;
}

int Seek_NextLine(FILE *fp)
{
    char ch;
    do
    {
        ch = getc(fp);
        if(ch == '\n')
            return 0;
    }while(ch != EOF);
    return -1;
}


