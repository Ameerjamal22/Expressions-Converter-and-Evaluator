#include <stdio.h>
#include <stdlib.h>

// Name : Ameer Rabie , Id : 1211226 , Section : 3 .

#define MaxExpressionSize 100 // maximum expression size

typedef struct IntegersStackNode * IntegersStack ;
typedef struct ListNode* ExpressionsList ;
typedef struct StackNode * Stack ;

int opeartors[] = {'+','-', '*', '/','@','#','^'} ; // Array that helps to check if the char is operator .
int parenthesis[] = {'[',']','(',')'} ; // Array to check if the char is dealt with as parenthesis .

/*
   parameter : character c  .
   return : returns 1 if the character c is dealt with as parenthesis 0 otherwise  .
*/
int isParenthesis( char c ){

    int exist = 0 ;  // initialize a integer value as a flag to 0 as an indication that the char is parenthesis

    // checking if the character is in parenthesis array if yes modify the value of exist .
    for( int i = 0 ; i < 4 ; i ++ ){

        if ( parenthesis[i] == c ){
            exist = 1 ;
        }
    }

    return exist ; // return the value of the flag .

}

/*
    parameter : Character c
    return : returns 1 if the character is one of the four arithmetic operator , otherwise returns zero .
*/
int isopeartor( char c ){

    int exist = 0 ; // initialize an integer value as a flag to zero .

    // checks if the character c is an operator and modifying the exist value based on the check .
    for( int i = 0 ; i < 7 ; i ++ ){

        if ( opeartors[i] == c ){
            exist = 1 ;
        }
    }

    return exist ; // returns the value of the flag .

}

/*
    parameter : character c .
    return value : returns an Integer value : 1 - (1) if the character is one of the decimal digits . 2- (0) otherwise .
*/
int isDigit( char c ){

    return ( c >= '0' && c <= '9') ; // returns the value of the function based on the comparison .

}

/*
    the expression node definition and attributes using struct .
*/
struct ListNode {

    // attributes for each expression
    char Infix[MaxExpressionSize] ; // infix representation of the expression
    char Prefix[ MaxExpressionSize * 2 ] ; // prefix representation of the expression after transformation (if the expression is valid ) .
    int  Valid ; // a integer (boolean) value , (1) if the expression is valid . (0) otherwise .
    int result ; // the result after evaluating the prefix of the expression

    // linking nodes and head attributes .
    struct ListNode * Next ;
    struct ListNode * Last ;
    int size ; // the number of expressions in the list that helps in the manipulation process .

};

/*
    Creates a head node for the list and returns a pointer to it  .
*/
ExpressionsList CreateList (){

    ExpressionsList Head = (struct ListNode * )malloc (  sizeof(struct ListNode) ) ; // initializing the head node and allocating a position for it in the memory
    Head -> size = 0 ; // initializing the size of the list of expressions to zero to be able to increment it .
    Head -> Next = NULL ;
    Head -> Last = Head ;

    return Head ; // returns a pointer to the head node .

}

/*
    Parameters : expression List head , string representation of the arithmetic expression .
    appends the expression to the passed list .
*/
void AppendExpression ( ExpressionsList Head , char ExpressionsList [MaxExpressionSize] ){

    // initializes the node that will be added to the list and allocating a position for it in the memory dynamically .
    struct ListNode * temp = ( struct ListNode *)malloc( sizeof( struct ListNode ) ) ;

    // copying the infix representation from the passed string to the node  .
    for(int i = 0 ; i < MaxExpressionSize ; i ++ )( temp ->Infix )[i] =  ExpressionsList[i] ;

    // linking the node with the list .
    Head -> Last -> Next = temp ;
    Head -> size ++ ;
    Head -> Last = temp ;
    temp -> Next = NULL ;

}

/*
    Parameter : a pointer to the head node of the list .
    return : an Integer (boolean) value , 1 if the list is empty , 0 otherwise .
*/
int isEmptyList( ExpressionsList List ){

    return (List -> Next == NULL ) ;

}

/*
    Parameters : a pointer to the head node of the expressions list .
    Prints the expression in the expressions List .
*/
void PrintExpressions ( ExpressionsList List ){



    if (isEmptyList(List)){
        printf("there is no expressions in the List ") ;
    }

    ExpressionsList temp = List -> Next ;

    while ( temp != NULL ){

        for(int i = 0 ; i < MaxExpressionSize ; i ++ ){

            if ( !isopeartor( (temp ->Infix)[i] ) && !isParenthesis( (temp ->Infix)[i] ) && !isDigit( (temp ->Infix)[i] ) ){
                break ;
            }

            printf("%c",(temp ->Infix)[i]) ;

        }
        printf("\n") ;

        temp = temp -> Next ;

    }


}

/*
    struct for the stack node that will help in the conversion of expressions from infix to prefix , and will help also
    in the evaluation of prefix expression .
*/
struct StackNode {

    // Attributes for each node in the stack .
    struct StackNode * Next ;
    char val ;
    int size ;

};

/*
    Creates an empty Stack and returns a pointer to the head node of it .
*/
Stack CreateStack (){

    // Creates the head node of the stack and initializes the attributes of the head node .
    struct StackNode* Head = ( struct StackNode * )malloc( sizeof ( struct StackNode ) ) ;
    Head -> size = 0 ;
    Head -> Next = NULL  ;
    return Head ;

}

/*
    Parameters : a pointer to the head of the stack , character c .
    Creates a node and push it  on top of the passed stack .
*/
void Push( Stack S , char c  ){

    // initializes the new node and allocating a place for it in the memory dynamically .
    struct StackNode * temp = ( struct StackNode * )malloc( sizeof( struct StackNode ) ) ;
    temp -> val = c ; // updating the value of the node to be the passed character

    // links the node with the nodes of the stack and incrementing the stack size
    temp -> Next = S -> Next ;
    S -> Next = temp ;
    S -> size ++ ;

}


/*
    Parameter : a pointer to the head node of the stack .
    removes the top node of the stack .
*/
void Pop( Stack S ){

    // initializes a pointer that will point to the head node of the stack .
    struct StackNode * temp = S -> Next ;

    // Checks if the stack is empty and if so gets out of the function since there is nothing to remove .
    if ( S -> size == 0 ){

        printf("Stack is empty \n") ;
        return ;

    }

    // Linking the remaining nodes together and erasing the top node from memory .
    S -> Next = S -> Next -> Next ;
    S -> size  -- ;
    free(temp) ;

}


/*
    Parameter : a pointer to the head node of the stack .
    return : returns the character value of the top node in the stack .
*/
char Top( Stack S ){

    // Checks if the stack is empty , and if so returns null since there is nothing to return .
    if( S -> size == 0 ){

        printf("Stack is empty \n") ;
        return '!' ;

    }


    return S -> Next -> val ; // returning the character value of the top node of the stack .

}

int isEmptyStack ( Stack s ){

    return ( s -> Next == NULL ) ;

}


/*
  Parameter : a pointer to the head node of the stack .
  removes all the nodes of the stack and prints them from the top to the least .
*/
void DisposeStackAndPrint ( Stack s ){

    while ( s -> size > 0  ){

        Pop(s) ;

    }

    free(s) ;

    return ;

}


/*
void printStack ( Stack s ){

    struct StackNode * temp = s -> Next ;

    while ( temp != NULL) {

        printf("  %c  " , temp -> val ) ;
        temp = temp -> Next ;
    }
    printf("\n") ;
}
*/

/*
    Parameters : string ( infix arithmetic expression ) .
    return : Integer value , 1 if the infix expression is valid , 0 Otherwise .

    operations like 5 ++ 5 or 5 *- 3 are considered valid and the second operator is the sign of the second number , so it will be substituted
    @ for - and # for + and the priority of them will be the highest since @ , # stands for the sign
*/
int isValidExpression ( char toCheck [MaxExpressionSize] ){

    Stack parenthesis = CreateStack() ; // creates a stack to validate the opening and closing parenthesis and brackets .
    int valid = 1 ; // initializes an Integer boolean that stand for the validity of the expression to change it through the process .
    int i = 0 ; // initializes an integer to traverse the infix expression that have to be checked .
    int digitsCount = 0 ; // initializes the consecutive digits count to zero .
    int opeartorsCount = 0 ; // initializes the consecutive operators count to zero .

    /*
        traverses the infix expression to check if its valid or not and change the sign operators to
        - : @ , + : # .
    */
    while ( ( isParenthesis(toCheck[i]) || isopeartor(toCheck[i]) || isDigit(toCheck[i])  )  ){

        // if the current char of the infix is a parenthesis or brackets it will be handled using stack .
        if ( isParenthesis( toCheck[i] ) ){

            // if the current infix char is opening bracket or parenthesis it will be pushed to the stack .
            if ( toCheck[i] == '(' || toCheck[i] == '[' ){

                Push( parenthesis , toCheck[i]) ; // pushes the openings to the parenthesis stack .

            }

            // otherwise the current infix char will be a closing parenthesis , bracket .
            else {


                if ( toCheck[i] == ')'){

                    // if the current char is invalid closing for the top of the stack valid value will be changed to zero and will break the loop
                    if ( Top( parenthesis ) != '('){

                        valid = 0 ; // changes the value of the valid flag to zero .
                        break ; // breaks out of the loop .

                    }
                    // else the top of the stack will be deleted since it a valid closing .
                    else {

                        Pop( parenthesis ) ; // deletes the top of the stack .

                    }

                }

                if ( toCheck[i] == ']'){
                    // if the current char is invalid closing for the top of the stack valid value will be changed to zero and will break the loop
                    if ( Top( parenthesis ) != '['){

                        valid = 0 ; // changes the value of the valid flag to zero .
                        break ;  // breaks out of the loop .

                    }
                    // else the top of the stack will be deleted since it a valid closing .
                    else {

                        Pop( parenthesis ) ;  // deletes the top of the stack .

                    }

                }

            }

        }

        // if statement to a handle the operators .
        if ( isopeartor( toCheck[i] ) ){

            digitsCount = 0 ; // changes the count of the consecutive digits to zero since an operator is found .

            // if the operator is the first
            if (opeartorsCount == 0 && i == 0 && toCheck[i] == '-'){

                toCheck[i] = '@' ; // changes the current infix char to @ which represents (* -1 ) or the negative sign .

            }

            // if the first char in the infix expression is not sign and its and operator then the infix expression is not valid .
            else if ( opeartorsCount == 0 && i == 0 && toCheck[i] != '-' && toCheck[i] != '+' ){

                valid = 0 ; // changes the valid flag to zero .
                break ; // breaks out of the loop .

            }

            // handles the case of two consecutive operators .
            if (opeartorsCount == 1 ){

                // if there is also an operator after the two then the infix expression is not valid .
                if ( isopeartor( toCheck[i+1] ) ){

                    valid = 0 ; // changes the value of valid flag to zero .
                    break ; // breaks out of the loop .

                }

                // if the second operator is not a sign operator then the infix expression is not valid .
                if ( toCheck[i] != '+' && toCheck[i] != '-' ){

                    valid = 0 ; // changes the value of the valid flag to zero .
                    break ; // breaks out of the loop .

                }

                if ( toCheck[i] == '+' ){

                    toCheck[i] = '#' ; // changes the value of the positive sign char to #  .

                }

                else if ( toCheck[i] == '-' ){

                    toCheck[i] = '@' ; // change the value of the negative sign char to @ .

                }

            }

            // handles the case when there is 3 or more consecutive operators .
            else if ( opeartorsCount >= 2  ){

                if (  isopeartor( toCheck[i + 1] ) || isopeartor( toCheck[ i - 1 ] ) ){

                    valid = 0 ; // changes the value of the valid flag to zero if there is 3 consecutive operators
                    break ; // breaks out of the loop .

                }

                if ( toCheck[i] != '+' && toCheck[i] != '-' ){

                    valid = 0 ; // changes the value of the valid flag to zero if current char is not a sign and there is operators before it
                    break ;

                }

                if ( toCheck[i] == '+' ){

                    toCheck[i] = '#' ; // if the operator is a positive sign then changes the char of the infix expression to #

                }

                else if ( toCheck[i] == '-' ){

                    toCheck[i] = '@' ; // if the current infix character is a negative sign it changes its value to @ .

                }

            }

            opeartorsCount ++ ; // incrementing the consecutive operators count since one is found .

        }

        // handles the case when the current infix expression char is a digit .
        if ( isDigit ( toCheck[i] ) ){

            opeartorsCount = 0 ; // changes the value of the consecutive operators count to zero since a digit is found

            // handles the case when the consecutive digits are divided by parenthesis or brackets without and operator between them .
            if ( digitsCount >= 1  &&  !isDigit( toCheck[i-1] ) ){

                valid = 0 ; // changes the value of the valid flag to zero since there is no operator between the number and parenthesis .

            }

            digitsCount ++ ; // incrementing the consecutive digits count since a one is found .

        }



        i ++ ; // incrementing the the value of i to continue traversing the infix expression .

    }

    // if the size of the parenthesis stack is not zero the the infix expression is not valid
    if ( parenthesis -> size != 0 ){

        valid = 0 ; // changes the value of the valid flag to zero .

    }



    return valid ; // returns the value of the valid flag , 1 if the infix expression is valid , 0 otherwise .

}

/*
    Parameters : character (operation char )
    return : returns an integer that represents the priority of the operation
    @ : is considered as the negative sign of number .
    # : is considered as the positive sign of number .
*/
int priorityOf( char operation ){

    if ( operation == '+' || operation == '-' ){

        return 1 ; // returns 1 if the operator is + , - since they have same priority .

    }
    else if ( operation == '*' || operation == '/' ){

        return 2 ; // returns 2 if the passed operator since * , / have the same priority , and higher then the addition and subtraction .

    }
    else if ( operation == '^'){

        return 3 ; // returns 3 if the passed operator is power since it have higher priority than + , - , / , * .

    }
    else if ( operation == '@' || operation == '#'){

        return 4 ; // returns 4 if the passed operator is @ : negative sign , # : positive sign since the sign has the highest priority .

    }

    return 0 ; // returns zero if the passed char is not one of the above .
}

/*
    Parameters : expression node .
    works on the infix expression of the expression nodes and convert it to prefix in other string and then assigns its value to the prefix
    expression of the passed expression node .
*/
void InfixToPrefix ( struct ListNode * Expression){


    char reversedExpression [ MaxExpressionSize ] ; // defines a string to put the reversed infix expression in it .
    for (int i = 0; i  < MaxExpressionSize ; i ++ )reversedExpression[i] = '\0' ; // initializes all the characters of the reversed expression to null

    int end = 0 ; // initializes the end integer and assigns the value zero to it .

    // traverses the infix expression of the passed expression node until the end of expression then breaks so the end integer value will be at the end of the expression
    for ( end = 0 ; end < MaxExpressionSize ; end ++ ){

        if ( !isDigit( ( Expression ->Infix)[end] ) && !isopeartor( ( Expression ->Infix)[end] ) && !isParenthesis( ( Expression ->Infix)[end] ) ){
            break ;
        }

    }


    int k = 0 ; // defining integer k and initializes it with value 0 to help reversing the infix expression
    char current ; // defining a character current to save the value of the current character in it .

    end -- ;

    // traverses the infix expression from the end and assigns its chars to the reversed string chars, and also handles the brackets reversing .
    while ( end >= 0 ){


        current = (  Expression -> Infix )[end] ;

        if ( current == '(' )reversedExpression[k] = ')' ;
        else if ( current == ')' )reversedExpression[k] = '(' ;
        else if ( current == '[' )reversedExpression[k] = ']' ;
        else if ( current == ']' )reversedExpression[k] = '[' ;
        else
        reversedExpression[k] = ( Expression -> Infix )[end] ;

        k ++ ; end -- ;

    }

    char prefixResult[ MaxExpressionSize * 2 ] ; // defining the result prefix string
    for (int i = 0 ; i < MaxExpressionSize * 2 ; i ++ )prefixResult[i] = '\0' ; // initializes the value of it chars to null

    int pre = 0 ; // defining a pointer that will help us to put the values in the result expressions .

    Stack operations = CreateStack() ; // defining the stack that will help to handle the operations and there priorities in the prefix expression .

    for( int i = 0 ; i < MaxExpressionSize ; i ++ ){

        // breaks out of the loop when the end of the reversed infix expression is reached .
        if ( !isDigit( reversedExpression[i] ) && !isopeartor( reversedExpression[i] ) && !isParenthesis( reversedExpression[i] ) )break ;


        if ( isDigit( reversedExpression[i] )){

            // traverses consecutive digits in the reversed expression and assigns the values of them to the prefix chars then a space after them to make the manipulation easier .
            while ( isDigit ( reversedExpression[i] ) ){

                prefixResult[pre] = reversedExpression[i] ;
                i ++ ; pre ++ ;

            }
            i -- ;

            prefixResult[pre] = ' ' ;
            pre ++ ;

        }


        else if ( reversedExpression[i] == '(' || reversedExpression[i] == '['){

            Push( operations , '(' ) ; // adds an the current reversed expression to the top of the stack if its ( or [ .

        }

        else if ( isopeartor( reversedExpression[i] ) ){

            // if the current char of the rev expression = @ , @ is added to the top of the stack and -1 is added to the prefix expression since @ is considered the negative sign which is equivalent to (* -1 )
            if ( reversedExpression[i] == '@' ){

                prefixResult[pre] = '-' ;
                pre ++ ;
                prefixResult[pre] = '1' ;
                pre ++ ;
                prefixResult[pre] = ' ' ; // appends space after the added number in the prefix expression .
                pre ++ ;
            }

            /*
                if an operation is found , then all the operations that have higher priority in the stack will be deleted and from the stack
                and appended to the prefix expression .
            */
            while ( operations -> size > 0  && priorityOf( reversedExpression[i] ) < priorityOf( Top( operations ) ) ){

                if ( Top( operations ) != '@' && Top( operations ) != '#' ){

                    prefixResult[pre] = Top( operations ) ;
                    pre ++ ;
                    Pop( operations ) ;

                    prefixResult[pre] = ' ' ;
                    pre ++ ;

                }

                else {

                    // if the top of the stack is @ then a * operation is added to expression .
                    if ( Top( operations ) == '@'){

                        prefixResult[pre] = '*' ;
                        pre ++ ;
                        Pop ( operations ) ;

                        prefixResult[pre] = ' ' ;
                        pre ++ ;

                    }

                    // non operators in the stack like parenthesis and brackets will be deleted .
                    else {

                        Pop( operations ) ;

                    }

                }

            }


            Push ( operations , reversedExpression[i] ) ; // adds the new operation to the top of the stack

        }

        else if ( reversedExpression[i] == ')' || reversedExpression[i] == ']'){

            /*
                if a closing parenthesis or brackets then all operations in the stack are poped and appended to the prefix expression until the top of the stack is the opening part
            */
            while ( Top( operations ) != '(' ){

                if ( Top( operations ) != '@' && Top( operations ) != '#' ){

                    prefixResult[pre] = Top( operations ) ;
                    pre ++ ;
                    Pop( operations ) ;

                    prefixResult[pre] = ' ' ;
                    pre ++ ;

                }

                else {

                    if ( Top( operations ) == '@'){

                        prefixResult[pre] = '*' ;
                        pre ++ ;
                        Pop ( operations ) ;

                        prefixResult[pre] = ' ' ;
                        pre ++ ;

                    }
                    else {

                        Pop( operations ) ;

                    }

                }

            }
            Pop( operations ) ; // deletes the opening parenthesis or brackets .


        }



    }

    /*
        deletes all the remaining operations in the stack and add them to the prefix expression .
    */
    while ( operations -> size > 0 ){

        if ( Top( operations ) != '@' && Top( operations ) != '#' ){

                    prefixResult[pre] = Top( operations ) ;
                    pre ++ ;
                    Pop( operations ) ;

                    prefixResult[pre] = ' ' ;
                    pre ++ ;

                }

                else {

                    if ( Top( operations ) == '@'){

                        prefixResult[pre] = '*' ;
                        pre ++ ;
                        Pop ( operations ) ;

                        prefixResult[pre] = ' ' ;
                        pre ++ ;

                    }
                    else {

                        Pop( operations ) ;

                    }

                }

    }

    pre -- ;

    for( int i = 0 ; i < MaxExpressionSize * 2 ; i ++ )(Expression ->Prefix)[i] = '$' ;

    int j = 0 ;

    // assigns the char values of the prefix result string to the prefix of the passed expression nodes .
    while ( pre >= 0 ){

        ( Expression ->Prefix )[j] = prefixResult[pre] ;
        pre -- ; j ++ ;

    }



}

struct IntegersStackNode {

    // Attributes for each node in the stack .
    struct IntegersStackNode * Next ;
    int val ;
    int size ;

};

/*
    Creates an empty Stack and returns a pointer to the head node of it .
*/
IntegersStack CreateIntegersStack (){

    // Creates the head node of the stack and initializes the attributes of the head node .
    struct IntegersStackNode* Head = ( struct IntegersStackNode * )malloc( sizeof ( struct IntegersStackNode ) ) ;
    Head -> size = 0 ;
    Head -> Next = NULL  ;
    return Head ;

}

/*
    Parameters : a pointer to the head of the stack , integer c .
    Creates a node and push it  on top of the passed stack .
*/
void PushInteger( IntegersStack S , int c  ){

    // initializes the new node and allocating a place for it in the memory dynamically .
    struct IntegersStackNode * temp = ( struct IntegersStackNode * )malloc( sizeof( struct IntegersStackNode ) ) ;
    temp -> val = c ; // updating the value of the node to be the passed Integer

    // links the node with the nodes of the stack and incrementing the stack size
    temp -> Next = S -> Next ;
    S -> Next = temp ;
    S -> size ++ ;

}


/*
    Parameter : a pointer to the head node of the stack .
    removes the top node of the stack .
*/
void PopInteger( IntegersStack S ){

    // initializes a pointer that will point to the head node of the stack .
    struct IntegersStackNode * temp = S -> Next ;

    // Checks if the stack is empty and if so gets out of the function since there is nothing to remove .
    if ( S -> size == 0 ){

        printf("Stack is empty \n") ;
        return ;

    }

    // Linking the remaining nodes together and erasing the top node from memory .
    S -> Next = S -> Next -> Next ;
    S -> size  -- ;
    free(temp) ;

}


/*
    Parameter : a pointer to the head node of the stack .
    return : returns the inetger value of the top node in the stack .
*/
int TopInteger( IntegersStack S ){

    // Checks if the stack is empty , and if so returns null since there is nothing to return .
    if( S -> size == 0 ){

        printf("Stack is empty \n") ;
        return -1 ;

    }

    return S -> Next -> val ; // returning the Integer value of the top node of the stack .

}

/*
    Parameters : the head node of the Integer stack .
    return : return and integer value , 1 if the Integers stack is empty , 0 otherwise
*/
int isEmptyIntegersStack ( IntegersStack s ){

    return ( s -> Next == NULL ) ; // if the top node of the Integers Stack is null then its empty .

}


/*
  Parameter : a pointer to the head node of the stack .
  removes all the nodes of the stack and prints them from the top to the least .
*/
void DisposeIntegersStack ( IntegersStack s ){

    while ( s -> size > 0  ){

        PopInteger(s) ;

    }

    free(s) ;

    return ;

}

/*
    Parameters : int x , int y
    return : returns an integer with the value x ^ y .
*/
int power(int x, int y)
{
    int temp ;

    if (y == 0) // if the power is zero the answer will always be 1 .
        return 1 ; // returns 1 .

    // if the power is even then the base is squared and the power is divided by two , and if its odd then its squared and multiplied by the original value of x .
    temp = power (x, y / 2) ;

    if (y % 2 == 0)
        return temp * temp;
    else
        return x * temp * temp;
}

/*
    prints the values in the stack from top and goes down .
*/
void printIntegersStack ( IntegersStack s ){

    struct IntegersStackNode * temp = s -> Next ;

    while ( temp != NULL) {

        printf("  %d  " , temp -> val ) ;
        temp = temp -> Next ;
    }
    printf("\n") ;
}

/*
    Parameters : Expression node .
    return : returns an Integer value that represents the result of evaluating the prefix expression .
*/
int EvaluateExpression ( struct ListNode * Expression ){

    // finds the end of the prefix expression to start evaluating from it

    int end = 0 ;

    for ( end = 0 ; end < MaxExpressionSize ; end ++ ){

        if ( !isDigit( ( Expression ->Prefix )[end] ) && !isopeartor( ( Expression -> Prefix )[end] ) && !isParenthesis( ( Expression ->Prefix)[end] ) && ( Expression ->Prefix )[end] != ' ' ){
            break ;
        }

    }
    end -- ;

    IntegersStack PrefixEvaluationStack = CreateIntegersStack() ; // create a stack that will be used in the manipulation process .

    int Number ; // defining the number Integer that will be used when converting a string integer to integer .
    int Base ; // defining the base Integer that will be used when converting a string integer to integer .
    int opperand1 , opperand2 ; // defining the operands integers that will be used to store the value before applying the operations to them .

    /*
        traverses the prefix expression starting from the end to evaluate it .
    */

    int divByZero = 0 ;

    while ( end >= 0 ){

        // skips to the next iteration if there is a space .
        if ( ( Expression -> Prefix )[end] == ' ' ){

            end -- ;
            continue ;

        }

        // handles negative number case
        else if ( ( Expression -> Prefix )[end] == '-' && end != 0 && ( Expression -> Prefix )[ end - 1 ] == '1' ){

            PushInteger ( PrefixEvaluationStack , -1 ) ; // adds -1 to the top of the stack
            end -- ; // decrements the value of end .

        }

        // handles the Integers conversion and add it to the stack
        else if ( isDigit( ( Expression -> Prefix )[end] ) ){

            Number = 0 ;
            Base = 1 ;
            /*
                traverses the integer digits and add them to the Integer number .
            */
            while ( isDigit( ( Expression -> Prefix )[end] ) ){

                Number += Base * ( ( Expression -> Prefix )[end] - '0' ) ;
                Base *= 10 ;

                end -- ;

            }
            end ++ ;


            PushInteger ( PrefixEvaluationStack , Number ) ; // pushing the value of the Integer to the stack .

        }


        // handles the operators in the prefix expression
        else if ( isopeartor( ( Expression -> Prefix )[end] )){

            // assigning the top value of the stack to operand 1 and deleting it from the stack .
            opperand1 = TopInteger( PrefixEvaluationStack ) ;
            PopInteger ( PrefixEvaluationStack ) ;

            // assigning the next top value of the stack to operand 2 and deleting it from the stack .
            opperand2 = TopInteger( PrefixEvaluationStack ) ;
            PopInteger( PrefixEvaluationStack ) ;

            /*
                applies the operation on the numbers based on the operation and add it to the top of the stack .
            */
            if ( ( Expression ->Prefix )[end] == '+' ){

                PushInteger ( PrefixEvaluationStack , opperand1 + opperand2 ) ;

            }

            else if ( ( Expression ->Prefix )[end] == '-' ){

                PushInteger ( PrefixEvaluationStack , opperand1 - opperand2 ) ;

            }

            else if ( ( Expression ->Prefix )[end] == '*' ){

                PushInteger ( PrefixEvaluationStack , opperand1 * opperand2 ) ;

            }

            else if ( ( Expression ->Prefix )[end] == '/' ){

                if (opperand2 != 0 )
                    PushInteger ( PrefixEvaluationStack , opperand1 / opperand2 ) ;

                else {

                    printf("The expression is not valid \n") ;
                    divByZero = 1 ;
                    break ;

                }

            }
            else if ( ( Expression -> Prefix )[end] == '^' ){

                PushInteger ( PrefixEvaluationStack , power( opperand1 , opperand2 ) ) ;

            }



        }


        end -- ;




    }

    int result ;

    if (divByZero == 0)
        result = TopInteger( PrefixEvaluationStack ) ; // assigning the top of the stack to the result after the manipulation process ends.
    else
        result = -1 ; // In case there is a division by zero in the expression the result will be -1 and an error message will be displayed on the console .

    return result ; // returns the result of the prefix expression .

}

/*
    reads the expressions in the file (name given by the user ) and put them in expression list .
    return : returns a list of expressions .
*/
ExpressionsList ReadInputFile() {

    ExpressionsList list = CreateList() ; // create

    // defining the file name string and the file and the input expression string .
    char filename[100];
    FILE *file;
    char InputExpression[MaxExpressionSize];

    // Get the filename from the user
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file in read mode
    file = fopen(filename, "r");

    if (file == NULL) {

        printf("Failed to open the file.\n");
        return list;

    }

    // initializes the chars of the input expression with null value .
    for (int i = 0; i < MaxExpressionSize; i++) {

        InputExpression[i] = '\0';

    }


    // traverses the string in the file till the end of file is reached .
    while (fgets(InputExpression, MaxExpressionSize , file) != NULL) {

        AppendExpression( list , InputExpression ) ;


        for (int i = 0; i < MaxExpressionSize ; i++) {

            InputExpression[i] = '\0';

        }
    }

    fclose(file) ; // closes the file .

    return list ; // returns the list of expressions that contains the expressions read from the file .
}

/*
    prints the text message to the console so the user see it .
*/
void PrintTextMessage(){

    printf("\n\nEnter the number of your choice \n") ;
    printf("1- Read expression from file \n") ;
    printf("2- Check the validity of equations\n") ;
    printf("3- Convert valid equations from infix to prefix and print the prefix expressions \n") ;
    printf("4- Evaluate the results of the Equations \n") ;
    printf("5- Print invalid equations \n") ;
    printf("6- print all the results to the output file \n") ;
    printf("7- Exit\n\n\n") ;

}


void Menu (){

    printf(".....welcome to the Expressions converter and calculator program....\n\n") ;


    int choice =- 1 ; // defining the choice integer to control the flow of the program .

    ExpressionsList List ; // defining the list of expressions that will contain the input .

    // controls the flow of the program .
    while (1){

        PrintTextMessage() ; // prints the text message to the user
        scanf( "%d" , &choice ) ; // takes the value of the choice from the user .

        if ( choice == 1){

            List = ReadInputFile() ; // reads the expressions in from the input file and put them in the List of expressions .

        }

        else if ( choice == 2 ){

            int count = 1 ;

            struct ListNode * temp = List -> Next ; // defining temporary expression node to traverse the expressions list

            /*
                loops through expressions and prints if they are valid or not .
            */
            while ( temp != NULL ){

                temp -> Valid = isValidExpression( temp -> Infix ) ; // validating the expression ,and puts the value in the expression node valid integer .

                printf("Equation NO %d -> ", count ) ; // prints the equation order number .

                if ( temp -> Valid == 1 ){
                    printf("Valid \n") ;
                }
                else {
                    printf("Invalid \n") ;
                }

                count ++ ; // incrementing count ;
                temp = temp -> Next ; // moving the temporary pointer to the next node .

            }

            printf("\n") ;

        }

        else if ( choice == 3 ){

            int count = 1 ;

            struct ListNode * Expression = List -> Next ; // defining the temporary node expression to traverse expression in the list .

            /*
                traverses the expression nodes and prints the prefix notation of them .
            */
            while ( Expression != NULL ){

                if ( Expression -> Valid == 1 ){

                InfixToPrefix( Expression ) ; // converts the infix expression to prefix notations and stores it in the expression node .
                printf("Equation No %d Prefix notation ->" , count ) ;

                // traverses the prefix string in the expression node and prints it .
                for ( int i = 0 ; i < MaxExpressionSize * 2 ; i ++ ){

                    if ( !isDigit( ( Expression ->Prefix )[i] ) && !isopeartor( ( Expression -> Prefix )[i] ) && !isParenthesis( ( Expression ->Prefix)[i] ) && ( Expression ->Prefix )[i] != ' ' ){
                        break ;
                    }

                    printf("%c", Expression -> Prefix[i]) ;

                }
                printf("\n") ;

                }

                count ++ ;
                Expression = Expression -> Next ;

            }
            printf("\n") ;

        }

        else if ( choice == 4 ){

            struct ListNode * temp = List -> Next ;
            int count = 1 ;

            while ( temp != NULL ){

                if ( temp -> Valid == 1 ){

                    temp -> result = EvaluateExpression( temp ) ;
                    printf("Equation No. %d Result = %d \n",count, temp -> result ) ;

                }
                count ++ ;
                temp = temp -> Next ;
            }

        }

        else if ( choice == 5 ) {

            printf("Invalid Equations: \n") ;

            struct ListNode* Expression = List -> Next ; // defines the temporary Expression node to traverse the list of expressions .

            int count = 1 ;

            /*
                traverses the expression nodes and prints the infix notation of them if the valid value of the expression node = 0 .
            */
            while ( Expression != NULL ){

                if( Expression -> Valid  != 1  ){

                    printf("%d- ",count) ;

                    // prints the infix expression .
                    for ( int i = 0 ; i < MaxExpressionSize  ; i ++ ){

                        if ( !isDigit( ( Expression -> Infix )[i] ) && !isopeartor( ( Expression -> Infix )[i] ) && !isParenthesis( ( Expression -> Infix )[i] ) && ( Expression -> Infix )[i] != ' ' ){

                            break ;

                        }
                        if ( ( Expression -> Infix )[i] != '@' && ( Expression -> Infix )[i] != '#' )
                            printf("%c", Expression -> Infix[i]) ;

                        else if ( ( Expression -> Infix )[i] == '@' ){

                            printf("-") ;

                        }

                        else if ( ( Expression -> Infix )[i] == '#' ){

                            printf("+") ;

                        }

                    }

                    printf("\n") ;

                }

                Expression = Expression -> Next ;
                count ++ ;

            }


        }

        else if ( choice == 6 ){

            FILE* file; // defining the file to write on it .
            char filename[] = "output.txt";

            // Open the file in write mode
            file = fopen(filename, "w");

            if (file == NULL) {

                printf("Failed to open the file.\n");
                return;

            }

            // handles the case when the list of expressions is empty .
            if (List->Next == NULL) {

                printf("There are no results to print yet.\n") ;
                fclose(file) ;
                return  ;

            }

            struct ListNode * Expression = List -> Next ; // defines the temporary Expression node (Expression) .
            int count = 1 ;

            while ( Expression != NULL ){

                fprintf( file ,"Equation No. %d ->",count) ;

                // handles the case of not valid infix expressions
                if( Expression -> Valid  != 1  ){


                    // prints the infix notation of the expression .
                    for ( int i = 0 ; i < MaxExpressionSize  ; i ++ ){

                        if ( !isDigit( ( Expression -> Infix )[i] ) && !isopeartor( ( Expression -> Infix )[i] ) && !isParenthesis( ( Expression -> Infix )[i] ) && ( Expression -> Infix )[i] != ' ' ){
                            break ;
                        }

                        fprintf( file ,"%c", Expression -> Infix[i]) ;

                        }

                        fprintf( file ," -> Invalid\n") ;

                }

                // handles the valid expressions case .
                else {


                    // prints the infix notation of the expression in the file .
                    for ( int i = 0 ; i < MaxExpressionSize  ; i ++ ){

                        if ( !isDigit( ( Expression -> Infix )[i] ) && !isopeartor( ( Expression -> Infix )[i] ) && !isParenthesis( ( Expression -> Infix )[i] ) && ( Expression -> Infix )[i] != ' ' ){
                            break ;
                        }


                        if ( ( Expression -> Infix )[i] != '@' && ( Expression -> Infix )[i] != '#' )
                            fprintf(file,"%c", Expression -> Infix[i]) ;

                        else if ( ( Expression -> Infix )[i] == '@' ){

                            fprintf(file,"-") ;

                        }

                        else if ( ( Expression -> Infix )[i] == '#' ){

                            fprintf(file,"+") ;

                        }

                    }

                    fprintf(file," -> Valid ") ;

                    fprintf(file,"-> Prefix Expression : ") ;

                    // prints the prefix notation of the expressions on the file .
                    for ( int i = 0 ; i < MaxExpressionSize * 2 ; i ++ ){

                        if ( !isDigit( ( Expression ->Prefix )[i] ) && !isopeartor( ( Expression -> Prefix )[i] ) && !isParenthesis( ( Expression ->Prefix)[i] ) && ( Expression ->Prefix )[i] != ' ' ){
                            break ;
                        }

                        fprintf(file,"%c", Expression -> Prefix[i]) ;

                    }

                    fprintf( file , " -> Result =%d \n" , Expression -> result ) ;

                }


                Expression = Expression -> Next ; // updating the value of the pointer to the next node .
                count ++ ;

            }

            fclose(file) ; // closing the file

        }

        else if ( choice == 7 ){

            // breaks out of the program loop if the choice is 7 .
            printf("Program Exits..... \n\n") ;
            break ;

        }

        else {

            printf("Invalid choice\n\n") ;

        }

    }

}


int main(){

    Menu() ; // calling the menu function that controls the flow of the program .

    return 0 ;

}
