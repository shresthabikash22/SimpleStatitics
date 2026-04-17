#!/usr/bin/env python3
"""
stats.py - Object-Oriented Python implementation of basic statistical calculations
Calculates mean, median, and mode for a list of integers entered by the user.
"""

import sys
from collections import Counter


class StatisticsCalculator:
    """
    Object-Oriented Statistics Calculator class.
    Encapsulates data and methods for statistical calculations.
    """
    
    def __init__(self, data=None):
        """
        Initialize the calculator with optional data.
        
        Args:
            data: List of integers (default: None)
        """
        self._data = data if data is not None else []
    
    def load_data(self, data):
        """
        Load new data into the calculator.
        
        Args:
            data: List of integers
        """
        self._data = data.copy()
    
    def mean(self):
        """
        Calculate the mean of the data.
        
        Returns:
            float: The mean value, or 0.0 if the list is empty
        """
        if not self._data:
            return 0.0
        return sum(self._data) / len(self._data)
    
    def median(self):
        """
        Calculate the median of the data.
        
        Returns:
            float: The median value, or 0.0 if the list is empty
        """
        if not self._data:
            return 0.0
        
        sorted_data = sorted(self._data)
        n = len(sorted_data)
        mid = n // 2
        
        if n % 2 == 1:
            return float(sorted_data[mid])
        else:
            return (sorted_data[mid - 1] + sorted_data[mid]) / 2.0
    
    def mode(self):
        """
        Calculate the mode(s) of the data.
        
        Returns:
            list: List of mode values (most frequent values)
        """
        if not self._data:
            return []
        
        # Count frequencies
        freq = Counter(self._data)
        
        # Find maximum frequency
        max_freq = max(freq.values())
        
        # Get all values that have the maximum frequency
        modes = [num for num, count in freq.items() if count == max_freq]
        
        return sorted(modes)
    
    def display(self):
        """
        Display all calculated statistics.
        """
        print("\n=== Results ===")
        print("Original numbers:", " ".join(map(str, self._data)))
        print(f"Mean:   {self.mean():.2f}")
        print(f"Median: {self.median():.2f}")
        
        modes = self.mode()
        print("Mode:   ", end="")
        if not modes:
            print("(no data)")
        elif len(modes) == len(self._data):
            print("(all values appear once)")
        else:
            print(" ".join(map(str, modes)))


def get_user_input():
    """
    Get integer input from the user.
    
    Returns:
        list: List of integers entered by the user
    
    Raises:
        ValueError: If input is invalid
    """
    try:
        # Get the number of integers
        count_str = input("Enter the number of integers: ").strip()
        count = int(count_str)
        
        if count <= 0:
            raise ValueError("Count must be a positive integer")
        if count > 1000000:
            raise ValueError("Count is too large (max 1,000,000)")
        
        # Get the integers
        print(f"Enter {count} integers separated by spaces or newlines:")
        numbers = []
        
        while len(numbers) < count:
            line = input().strip()
            if not line:
                continue
            
            # Split the line and convert to integers
            try:
                line_numbers = [int(x) for x in line.split()]
                numbers.extend(line_numbers)
            except ValueError:
                raise ValueError("Invalid integer input")
        
        # Check if we got exactly the right number
        if len(numbers) != count:
            raise ValueError(f"Expected {count} numbers, but got {len(numbers)}")
        
        return numbers
    
    except (ValueError, EOFError) as e:
        if isinstance(e, ValueError):
            raise
        else:
            raise ValueError("Invalid input")


def main():
    """
    Main function to run the statistics calculator using OOP approach.
    """
    try:
        # Get input from user
        numbers = get_user_input()
        
        # Create instance of StatisticsCalculator class (OOP!)
        calculator = StatisticsCalculator(numbers)
        
        # Display results using class methods
        calculator.display()
        
    except ValueError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)
    except KeyboardInterrupt:
        print("\nProgram interrupted by user", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()