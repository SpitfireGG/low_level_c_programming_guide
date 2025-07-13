#include <stdio.h>   // Include for printf
#include <stddef.h>  // Include for size_t

// Function prototype for print_array
void print_array(const int *array, size_t size);

/**
 * bubble_sort - sorts an array of integers in ascending order using the
 * Bubble sort algorithm
 *
 * @array: data to sort
 * @size: size of data
 *
 * Return: No Return
 */
void bubble_sort(int *array, size_t size)
{
    size_t i, j;
    int tmp;  // Use int for temporary variable as array elements are int
    // Flag to optimize: if no swaps occur in a pass, the array is sorted
    int swapped;

    if (array == NULL || size < 2)
        return;

    // Outer loop for passes
    // We only need size - 1 passes, as the last element will be in place
    for (i = 0; i < size - 1; i++)
    {
        swapped = 0;  // Reset swapped flag for each pass
        // Inner loop for comparisons and swaps
        // The last i elements are already sorted, so we don't need to compare
        // them
        for (j = 0; j < size - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                tmp          = array[j];
                array[j]     = array[j + 1];
                array[j + 1] = tmp;
                swapped      = 1;          // A swap occurred
                print_array(array, size);  // Print array after each swap
            }
        }
        // If no two elements were swapped by inner loop, then break
        if (swapped == 0)
            break;
    }
}

/**
 * print_array - Prints an array of integers.
 *
 * @array: The array to be printed.
 * @size: The number of elements in the array.
 */
void print_array(const int *array, size_t size)
{
    size_t i;

    if (array == NULL)
        return;

    for (i = 0; i < size; i++)
    {
        printf("%d", array[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("\n");
}

int main(void)
{
    int arr[]   = {14, 21, 4, 42, 32, 434};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    print_array(arr, size);
    printf("---\n");

    bubble_sort(arr, size);

    printf("---\n");
    printf("Sorted array: ");
    print_array(arr, size);

    return 0;
}
