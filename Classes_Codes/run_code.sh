#!/bin/bash

echo "Welcome to my script runner!"
echo "Select a option:"

options=("Bhaskara" "Linked List" "Quit")

select choice in "${options[@]}"
do
    case $choice in
        "Bhaskara")
            echo "You chose option 1"
            gcc -ansi -pedantic -std=c90 bhaskara.c -lm -o a.out && ./a.out && rm a.out
            ;;
        "Linked List")
            echo "You choose option 2"
            gcc -ansi -pedantic -std=c90 linked_list.c -lm -o a.out && ./a.out && rm a.out
            ;;
        "Quit")
            echo "Exiting..."
            break
            ;;
        *) echo "Invalid option. Please try again." ;;
    esac
done

