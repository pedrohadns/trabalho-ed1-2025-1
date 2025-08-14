#!/bin/bash

# --- Configuration ---
# The program you want to test. Pass it as the first argument to the script.
# Example: ./run_tests.sh ./my_program
if [ -z "$1" ]; then
    echo "Error: Please provide the path to your program as an argument."
    echo "Usage: $0 ./your_program_executable"
    exit 1
fi
PROGRAM_TO_TEST=$1

# --- Colors for output ---
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# --- Main Test Loop ---
# Find all files that match the pattern 'test_input*.txt' and loop through them.
# The 'sort -V' command ensures that 'test_input2.txt' comes after 'test_input10.txt'.
for input_file in $(ls test_input*.txt | sort -V); do

    # Extract the number from the input file name (e.g., '00', '01', etc.)
    # This uses 'sed' to capture the digits between 'test_input' and '.txt'.
    test_num=$(echo "$input_file" | sed 's/test_input\([0-9]*\).txt/\1/')

    # Construct the name of the corresponding expected output file.
    expected_output_file="test_output${test_num}.txt"

    # --- Pre-test Checks ---
    # Check if the corresponding output file actually exists.
    if [ ! -f "$expected_output_file" ]; then
        echo -e "${YELLOW}--- Test ${test_num} ---${NC}"
        echo -e "${YELLOW}Warning: Skipping test. Could not find expected output file: ${expected_output_file}${NC}"
        echo ""
        continue # Skip to the next test
    fi

    # --- Test Execution & Output ---
    echo "--- Test ${test_num} ---"

    # Read and display the content of the input file.
    input_content=$(cat "$input_file")
    echo "Input:"
    echo "$input_content"

    # Read and display the content of the expected output file.
    expected_output=$(cat "$expected_output_file")
    echo "Expected Output:"
    echo "$expected_output"

    # Run your program, redirecting the input file to its standard input.
    # The program's output is captured into the 'actual_output' variable.
    actual_output=$($PROGRAM_TO_TEST < "$input_file")
    echo "Your Program's Output:"
    echo "$actual_output"

    # --- Verification ---
    # Compare the program's output with the expected output.
    if [ "$actual_output" == "$expected_output" ]; then
        echo -e "${GREEN}Result: OK${NC}"
    else
        echo -e "${RED}Result: NOT OK${NC}"
    fi

    echo "" # Add a blank line for better readability between tests.
done

echo "All tests complete."
