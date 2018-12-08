#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define SIZE 1024
#define SYNTAX_ERROR {printf("syntax error\n"); free(out_stack); return 0;}
#define DIVISON_ERROR {printf("division by zero\n"); free(stack); free(res); return;}
#define NUMBER  false
#define OPERATOR true


enum last_item_type {///перечисление всех возможных типов в строке

    LAST_START_FILE,

    LAST_NUMBER,

    LAST_OPEN_BRACKET,

    LAST_CLOSE_BRACKET,

    LAST_OPERATOR

};




struct stack_item {///элемент стека

    int value;

    bool is_operator;

};


size_t push(struct stack_item *stack, size_t stack_pos, int valve, bool is_operator) {///добавить элемент в стек

    struct stack_item item = {valve, is_operator};

    stack[stack_pos] = item;
    ++stack_pos;

    return stack_pos;

}



 bool is_operator(char c) {

    return (c == '+') || (c == '-') || (c == '*') || (c == '/');

}



 bool is_number(char c) {

    return c - '0' >= 0 && c - '0' <= 9;



}



 int priority(char operator) {

    switch (operator) {///без default ?

        case '*':

        case '/':

            return 1;

        case '+':

        case '-':

            return 0;



    }

    return -1;

}



struct stack_item *TAKE_THE_POLAND(char *input) {

    struct stack_item *out_stack = malloc(SIZE * sizeof(struct stack_item));

    if (!out_stack) {

        printf("memory error\n");

        return 0;

    }

    char operator_stack[SIZE];

    enum last_item_type last_type = LAST_START_FILE;

    size_t out_top = 0;

    size_t oper_top = 1;

    size_t pos = 0;

    while (input[pos] != '\n') {

        if (is_number(input[pos])) {

            if (last_type == LAST_NUMBER || last_type == LAST_CLOSE_BRACKET) SYNTAX_ERROR;//нельзя )X и XX

            int number = 0;

            while (is_number(input[pos])) {

                number = number * 10 + (input[pos] - '0');

                ++pos;

            }

            pos--;

            out_top = push(out_stack, out_top, number, NUMBER);

            last_type = LAST_NUMBER;

        } else if (input[pos] == '(') {//// нельзя X(

            if (last_type == LAST_NUMBER) {

                SYNTAX_ERROR;
            }

            operator_stack[oper_top] = input[pos];
            ++oper_top;

            last_type = LAST_OPEN_BRACKET;


        } else if (is_operator(input[pos])) {

            if (last_type == LAST_START_FILE || last_type == LAST_OPEN_BRACKET) {

                if (input[pos] == '-') {///для отрицательных чисел

                    out_top = push(out_stack, out_top, 0, NUMBER);

                } else SYNTAX_ERROR;

            }

            if (last_type == LAST_OPERATOR) { ///нельзя ** // ++ --

                SYNTAX_ERROR;

            }

            if (priority(input[pos]) <= priority(operator_stack[oper_top - 1])) {///если приоритет оператора в стеке операторов больше или равен приоритету нового,старый вытолкнуть в массив выхода

                out_top = push(out_stack, out_top, operator_stack[oper_top - 1], OPERATOR);

                --oper_top;

            }

            operator_stack[oper_top] = input[pos];
            ++oper_top;

            last_type = LAST_OPERATOR;

        } else if (input[pos] == ')') {/// нелья ()

            if (last_type == LAST_OPEN_BRACKET) {

                SYNTAX_ERROR;

            }

            if (last_type == LAST_OPERATOR) {///нельзя *)

                SYNTAX_ERROR;

            }

            bool found = false;

            while (oper_top > 0) {///найти открывающую скобку и вытолкнуть все операторы до скобки

                if (operator_stack[oper_top - 1] == '(') {

                    found = true;

                    break;

                }

                out_top = push(out_stack, out_top, operator_stack[oper_top - 1], OPERATOR);///вытолкнуть

                oper_top--;

            }

            if (!found) { ///

                SYNTAX_ERROR;

            }

            oper_top--;

            last_type = LAST_CLOSE_BRACKET;

        }  else // Неизвестный символ -  '. ' например

        SYNTAX_ERROR;

        ++pos;

    }

    if (last_type == LAST_OPERATOR) { /// *)

        SYNTAX_ERROR;

    }

    while (oper_top > 1) {  /// Все оставшикся операции в стек

        if (operator_stack[oper_top - 1] == '(') { ///лишняя скобка

            SYNTAX_ERROR;

        }

        out_top = push(out_stack, out_top, operator_stack[oper_top - 1], OPERATOR);///вытолкнуть оставшиеся операторы в массив выхода

        oper_top--;

    }

    push(out_stack, out_top, 0, OPERATOR);///конец стека

    return out_stack;

}


 size_t stack_size(struct stack_item *stack) {///определить размер стека

    size_t i = 0;

    while (!stack[i].is_operator || stack[i].value) {

        ++i;

    }

    return i;

}



void calc(struct stack_item *stack) {

    size_t size = stack_size(stack);

    int *res  = malloc(SIZE * sizeof(int));

    if (!res) {

        printf("syntax error\n");

        return;

    }

    size_t calculation_pos = 0;

    int a, b, result;

    for (size_t i = 0; i < size; i++) {

        if (!stack[i].is_operator) {

            res[calculation_pos] = stack[i].value;

           ++ calculation_pos;

        } else {
            --calculation_pos;

            b = res[calculation_pos];

            --calculation_pos;

            a = res[calculation_pos];

            switch (stack[i].value) {

                case '+':

                    res[calculation_pos] = a + b;

                    ++calculation_pos;

                    break;

                case '-':

                    res[calculation_pos] = a - b;

                    ++calculation_pos;

                    break;

                case '*':

                    res[calculation_pos] = a * b;

                    ++calculation_pos;

                    break;

                case '/':

                    if (b == 0) DIVISON_ERROR;

                    res[calculation_pos++] = a / b;
                   ++calculation_pos;

                    break;

            }

        }

    }

    result = res[0];

    free(stack);

    free(res);

    printf("%d\n", result);

}


int main(void) {
    char input[SIZE];

    fgets(input, sizeof(char)*SIZE, stdin);

    struct stack_item *stack = TAKE_THE_POLAND(input);

    if  (stack!=0 && stack[0].is_operator && stack[0].value == 0 )  printf("syntax error\n");
    if  (stack!=0 && !(stack[0].is_operator && stack[0].value == 0 )) calc(stack);
    return 0;

}