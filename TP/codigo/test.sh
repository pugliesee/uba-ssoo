#!/bin/bash

# Check for the correct number of arguments
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <N> <Test>"
  exit 1
fi

N="$1"  # Number of times to run the Makefile
TEST="$2"

case "$2" in
   "test") 
       TEST="test"
   ;;
   "books") 
       TEST="books"
   ;;
   "uniform") 
       TEST="uniform"
   ;;
   "normal") 
       TEST="normal"
   ;;
   *) 
       echo "No test defined." 
       exit 1
   ;;
esac


# Run the Makefile N times
for ((i=1; i<=N; i++)); do
  make $TEST
  if [ $? -ne 0 ]; then
    echo "Error: Makefile execution failed on iteration $i."
    exit 1
  fi
done

echo "Makefile ran successfully $N times."

