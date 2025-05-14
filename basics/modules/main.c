#include <stdio.h>
#include "math_utils.h"

int main()
{
    int sum = add(5, 3);
    printf("Sum: %d\n", sum);

    int diff = subtract(10, 4);
    printf("Difference: %d\n", diff);

    return 0;
}

// leave the header file math_utils.h be as is
// make an object file of all the present .c files
// once done, link them into an executable file ( binary )
// if you try to declare body of the function inside the .h file you will get an
// ODR violation error
/* The One Definition Rule is an important rule of the C & C++ programming
   language that prescribes that classes/structs and non-inline functions cannot
   have more than one definition in the entire program and template and types
   cannot have more than one definition by translation unit.
*/
