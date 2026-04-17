#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Sorts an array of integers in ascending order using qsort
 * @param data Array of integers to sort
 * @param count Number of elements in the array
 */
void sort_integers(int *data, int count) {
    qsort(data, count, sizeof(int), compare);
}

/**
 * Calculates the mean of an integer array
 * @param data Array of integers
 * @param count Number of elements in the array
 * @return The mean value as a double, or 0.0 if count is 0
 */
double calculate_mean(int *data, int count) {
    if (count == 0) {
        return 0.0;
    }

    long long sum = 0;
    for (int i = 0; i < count; i++) {
        sum += data[i];
    }
    return (double)sum / count;
}

/**
 * Calculates the median of an integer array
 * @param data Array of integers 
 * @param count Number of elements in the array
 * @return The median value as a double, or 0.0 if count is 0
 * @note The input array will be sorted by this function
 */
double calculate_median(int *data, int count) {
    if (count == 0) {
        return 0.0;
    }

    sort_integers(data, count);
    
    if (count % 2 == 1) {
        return (double)data[count / 2];
    }
    return ((double)data[count / 2 - 1] + (double)data[count / 2]) / 2.0;
}

/**
 * Calculates the mode(s) of an integer array
 * @param data Array of integers 
 * @param count Number of elements in the array
 * @param num_modes Output parameter: number of modes found
 * @return Pointer to dynamically allocated array of mode values, or NULL if error
 * @note The input array will be sorted by this function
 * @note Caller is responsible for freeing the returned array
 */
int *calculate_mode(int *data, int count, int *num_modes) {
    if (count == 0) {
        *num_modes = 0;
        return NULL;
    }

    sort_integers(data, count);

    int current_value = data[0];
    int current_count = 1;
    int max_count = 1;

    // First pass: determine max frequency
    for (int i = 1; i < count; i++) {
        if (data[i] == current_value) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
            }
            current_value = data[i];
            current_count = 1;
        }
    }
    if (current_count > max_count) {
        max_count = current_count;
    }

    // Second pass: collect all values matching max frequency
    current_value = data[0];
    current_count = 1;
    *num_modes = 0;
    
    int *modes = malloc(count * sizeof(int));
    if (modes == NULL) {
        *num_modes = -1;  // Error indicator
        return NULL;
    }

    for (int i = 1; i < count; i++) {
        if (data[i] == current_value) {
            current_count++;
        } else {
            if (current_count == max_count) {
                modes[*num_modes] = current_value;
                (*num_modes)++;
            }
            current_value = data[i];
            current_count = 1;
        }
    }
    if (current_count == max_count) {
        modes[*num_modes] = current_value;
        (*num_modes)++;
    }

    return modes;
}

/**
 * Gets integer input from the user
 * @param count Output parameter: number of integers entered
 * @return Pointer to dynamically allocated array of integers, or NULL if error
 * @note Caller is responsible for freeing the returned array
 */
int* get_user_input(int *count) {
    printf("Enter the number of integers: ");
    if (scanf("%d", count) != 1) {
        fprintf(stderr, "Error: Invalid input for count.\n");
        return NULL;
    }
    
    if (*count <= 0) {
        fprintf(stderr, "Error: Count must be a positive integer.\n");
        return NULL;
    }
    
    if (*count > 1000000) {
        fprintf(stderr, "Error: Count is too large (max 1,000,000).\n");
        return NULL;
    }

    int *numbers = malloc(*count * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for input array.\n");
        return NULL;
    }

    printf("Enter %d integers separated by spaces or newlines:\n", *count);
    for (int i = 0; i < *count; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Error: Invalid integer input at position %d.\n", i + 1);
            free(numbers);
            return NULL;
        }
    }

    return numbers;
}

/**
 * Creates a copy of an integer array
 * @param source Source array to copy
 * @param count Number of elements to copy
 * @return Pointer to new array, or NULL if allocation fails
 * @note Caller is responsible for freeing the returned array
 */
int* copy_array(int *source, int count) {
    int *dest = malloc(count * sizeof(int));
    if (dest == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        dest[i] = source[i];
    }
    return dest;
}

/**
 * Displays the calculated statistics
 * @param original_data The original input array
 * @param count Number of elements
 * @param mean The calculated mean
 * @param median The calculated median
 * @param modes Array of mode values
 * @param num_modes Number of modes
 */
void display_results(int *original_data, int count, double mean, double median, int *modes, int num_modes) {
    printf("\n=== Results ===\n");
    
    printf("Original numbers: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", original_data[i]);
    }
    printf("\n");
    
    printf("Mean:   %.2f\n", mean);
    printf("Median: %.2f\n", median);
    
    printf("Mode:   ");
    if (num_modes == 0) {
        printf("(no data)");
    } else if (num_modes == count) {
        printf("(all values appear once)");
    } else {
        for (int i = 0; i < num_modes; i++) {
            printf("%d ", modes[i]);
        }
    }
    printf("\n");
}

int main(void) {
    int count;
    int *numbers = NULL;           // Original input array
    int *temp_buffer = NULL;       // Reusable buffer for median/mode calculations
    int *modes = NULL;             // Array of mode values
    int num_modes;
    
    // Get input from user
    numbers = get_user_input(&count);
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }
    
    // Create a single reusable buffer for calculations
    temp_buffer = copy_array(numbers, count);
    if (temp_buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for temporary buffer.\n");
        free(numbers);
        return EXIT_FAILURE;
    }
    
    // Calculate mean (doesn't modify the array)
    double mean = calculate_mean(numbers, count);
    
    // Calculate median (sorts temp_buffer)
    double median = calculate_median(temp_buffer, count);
    
    // Reset temp_buffer to original values for mode calculation
    for (int i = 0; i < count; i++) {
        temp_buffer[i] = numbers[i];
    }
    
    // Calculate mode (sorts temp_buffer again)
    modes = calculate_mode(temp_buffer, count, &num_modes);
    
    // Check for mode calculation errors
    if (num_modes == -1) {
        fprintf(stderr, "Error: Memory allocation failed for mode array.\n");
        free(numbers);
        free(temp_buffer);
        return EXIT_FAILURE;
    }
    
    // Display results
    display_results(numbers, count, mean, median, modes, num_modes);
    
    // Clean up all allocated memory
    free(numbers);
    free(temp_buffer);
    free(modes);
    
    return EXIT_SUCCESS;
}