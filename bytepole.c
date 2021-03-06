#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef unsigned char BYTE;

typedef struct Stack {
    int top;
    int size;
    BYTE *stack;
} Stack;

BYTE pop(Stack *stack)
{
    return stack->stack[--stack->top];
}

void push(BYTE val, Stack *stack)
{
    stack->stack[stack->top++] = val;
    if(stack->top >= stack->size) {
        stack -> size = stack->size + 16;
        BYTE *new = malloc(stack->size * sizeof(BYTE));
        memcpy(new, stack->stack, stack->top);
        free(stack->stack);
        stack->stack = new;
    }
}

void exec(char* code)
{
    BYTE mem[256];
    strcpy((char*) mem, code);
    Stack stack;
    stack.top = 0;
    stack.size = 16;
    stack.stack = malloc(stack.size * sizeof(BYTE));
    BYTE pos = 0;

    int cont = 1;

    while (cont)
    {
        BYTE instr = mem[pos];
        // printf("%c\n", instr);
        // printf("---\n");
        if ('0' <= instr && instr <= '9')
        {
            push(instr - '0', &stack);
        }
        else if ('a' <= instr && instr <= 'f')
        {
            push(10 + instr - 'a', &stack);
        }
        else if (instr == '.') {
            BYTE little = pop(&stack);
            BYTE big = pop(&stack);
            push((big << 4) | little, &stack);
        }
        else if (instr == '+') {
            push(pop(&stack) + pop(&stack), &stack);
        }
        else if (instr == '-') {
            BYTE sub = pop(&stack);
            push(pop(&stack) - sub, &stack);
        }
        else if (instr == '*') {
            push(pop(&stack) * pop(&stack), &stack);
        }
        else if (instr == '/') {
            BYTE div = pop(&stack);
            push(pop(&stack) / div, &stack);
        }
        else if (instr == '%') {
            BYTE div = pop(&stack);
            push(pop(&stack) % div, &stack);
        }
        else if (instr == '&') {
            push(pop(&stack) & pop(&stack), &stack);
        }
        else if (instr == '|') {
            push(pop(&stack) | pop(&stack), &stack);
        }
        else if (instr == 'X') {
            push(pop(&stack) ^ pop(&stack), &stack);
        }
        else if (instr == '~') {
            push(~pop(&stack), &stack);
        }
        else if (instr == '!') {
            push(!pop(&stack), &stack);
        }
        else if (instr == 'r')
        {
            unsigned int res;
            scanf("%u", &res);
            push((BYTE) res, &stack);
        }
        else if (instr == 'p')
        {
            printf("%d\n", pop(&stack));
        }
        else if (instr == '\'')
        {
            putchar(pop(&stack));
        }
        else if (instr == '(')
        {
            BYTE val = pop(&stack);
            push(val, &stack);
            push(val, &stack);
        }
        else if (instr == ')')
        {
            pop(&stack);
        }
        else if (instr == '@')
        {
            BYTE val1 = pop(&stack);
            BYTE val2 = pop(&stack);
            push(val1, &stack);
            push(val2, &stack);
        }
        else if (instr == 'g')
        {
            pos = pop(&stack);
            continue;
        }
        else if (instr == 'j')
        {
            BYTE new = pop(&stack);
            if (pop(&stack))
            {
                pos = new;
                continue;
            }
        }
        else if (instr == 'I')
        {
            push(pos, &stack);
        }
        
        else if (instr == 'l')
        {
            push(mem[pop(&stack)], &stack);
        }
        else if (instr == 's')
        {
            mem[pop(&stack)] = pop(&stack);
        }
        else if (instr == ' ')
        {
            // do nothing
        }
        else
        {
            cont = 0;
        }
        pos++;
    }
    free(stack.stack);
}

int main(int argc, char **argv)
{
    char* code;
    while ((code = readline("> ")) != NULL)
    {
        if (strlen(code) > 0) {
            add_history(code);
        }
        
        exec(code);
        putchar('\n');
        free(code);
    }
    
    return 0;
}
