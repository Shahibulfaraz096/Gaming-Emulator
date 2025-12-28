#include <stdio.h>
#include <stdint.h>

#define MEMORY_SIZE 256

#define LOAD 1
#define ADD 2
#define SUB 3
#define JMP 4
#define PRINT 5
#define HALT 255

uint8_t memory[MEMORY_SIZE];
uint8_t R[4];
uint8_t PC = 0;

void load_program()
{
    int i = 0;

    memory[i++] = LOAD;
    memory[i++] = 0;
    memory[i++] = 10;
    memory[i++] = LOAD;
    memory[i++] = 1;
    memory[i++] = 20;
    memory[i++] = ADD;
    memory[i++] = 0;
    memory[i++] = 1;
    memory[i++] = PRINT;
    memory[i++] = 0;
    memory[i++] = HALT;
}

void execute()
{
    while (1)
    {
        uint8_t opcode = memory[PC++];

        switch (opcode)
        {
        case LOAD:
        {
            uint8_t reg = memory[PC++];
            uint8_t val = memory[PC++];
            R[reg] = val;
            break;
        }

        case ADD:
        {
            uint8_t r1 = memory[PC++];
            uint8_t r2 = memory[PC++];
            R[r1] += R[r2];
            break;
        }

        case SUB:
        {
            uint8_t r1 = memory[PC++];
            uint8_t r2 = memory[PC++];
            R[r1] -= R[r2];
            break;
        }

        case JMP:
        {
            uint8_t addr = memory[PC++];
            PC = addr;
            break;
        }

        case PRINT:
        {
            uint8_t reg = memory[PC++];
            printf("R%d = %d\n", reg, R[reg]);
            break;
        }

        case HALT:
            printf("Program halted.\n");
            return;

        default:
            printf("Unknown instruction %d\n", opcode);
            return;
        }
    }
}

int main()
{
    load_program();
    execute();
    return 0;
}
