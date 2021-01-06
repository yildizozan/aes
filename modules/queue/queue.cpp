//
// Created by yildizozan on 5.01.2021.
//

#include <iostream>
#include "queue.h"

// Constructor to initialize queue
queue::queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

// Destructor to free memory allocated to the queue
queue::~queue()
{
    delete[] arr;
}

// Utility function to remove front element from the queue
void queue::dequeue()
{
    // check for queue underflow
    if (isEmpty())
    {
        std::cout << "UnderFlow\nProgram Terminated\n";
        exit(1);
    }

    std::cout << "Removing " << arr[front] << '\n';

    front = (front + 1) % capacity;
    count--;
}

// Utility function to add an item to the queue
void queue::enqueue(int item)
{
    // check for queue overflow
    if (isFull())
    {
        std::cout << "OverFlow\nProgram Terminated\n";
        exit(1);
    }

    std::cout << "Inserting " << item << '\n';

    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}

// Utility function to return front element in the queue
int queue::peek()
{
    if (isEmpty())
    {
        std::cout << "UnderFlow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    return arr[front];
}

// Utility function to return the size of the queue
int queue::size()
{
    return count;
}

// Utility function to check if the queue is empty or not
bool queue::isEmpty()
{
    return (size() == 0);
}

// Utility function to check if the queue is full or not
bool queue::isFull()
{
    return (size() == capacity);
}