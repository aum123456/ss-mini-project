#include <stdio.h>
#include <string.h>

char input[10], label[10], ch1, ch2;
int addr, w = 0, start, prev_taddr, prev_length, length = 0, total_length, count = 0, taddr, address, block = 0;
FILE * fp1, * fp2;

void check();

int main() {
    printf("ABSOLUTE LOADER: By 1DS20CS145, 146, 147, 148\n\n");

    fp1 = fopen("input.o", "r");
    fp2 = fopen("output.mem", "w");
    // Read the letter at the beginning of the line
    fscanf(fp1, "%s ", input);
    // While it is not the end record
    while (strcmp(input, "E") != 0) {
        // Header record
        if (strcmp(input, "H") == 0) {
            // Scan label, start address, total length
            fscanf(fp1, "%s %x %x", label, & start, & total_length);
            address = start;
            fscanf(fp1, "%s ", input);
            continue;
        }
        // Text record
        if (strcmp(input, "T") == 0) {
            prev_length = length;
            prev_taddr = addr;
            fscanf(fp1, "%x %x %s", & taddr, & length, input);
            addr = taddr;
            if (w == 0) {
                prev_taddr = address;
                w = 1;
            }
            // Print "xx" for empty memory locations
            for (int i = 0; i < (taddr - (prev_taddr + prev_length)); i++) {
                address = address + 1;
                fprintf(fp2, "xx");
                count++;
                if (count == 4) {
                    fprintf(fp2, " ");
                    block++;
                    if (block == 4) {
                        fprintf(fp2, "\n%x ", address);
                        block = 0;
                    }
                    count = 0;
                }
            }
            // Newline if it is the first text record
            if (taddr == start) {
                fprintf(fp2, "\n%x ", taddr);
            }
        }
        fprintf(fp2, "%c%c", input[0], input[1]);
        check();
        fprintf(fp2, "%c%c", input[2], input[3]);
        check();
        fprintf(fp2, "%c%c", input[4], input[5]);
        check();
        fscanf(fp1, "%s ", input);
    }

    fclose(fp1);
    fclose(fp2);

    printf("Memory state:\n");
    printf("-------------------------------------------------------\n");
    printf("MEM\t\tCONTENTS\n");
    printf("-------------------------------------------------------\n");
    fp2 = fopen("output.mem", "r");
    ch2 = fgetc(fp2);
    while (ch2 != EOF) {
        printf("%c", ch2);
        ch2 = fgetc(fp2);
    }
    fclose(fp2);
    printf("\n");
}

void check() {
    count++;
    address++;
    taddr = taddr + 1;
    if (count == 4) {
        fprintf(fp2, " ");
        block++;
        if (block == 4) {
            fprintf(fp2, "\n%x ", taddr);
            block = 0;
        }
        count = 0;
    }
}