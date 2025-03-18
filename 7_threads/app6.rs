/*
    Write a C program consisting of a single process running 6 threads (including the initial one).
    The process creates an array of 5 characters, whose elements are initialized with '#'.
    There will be 5 "producer" threads in the process that will continuously fill in a random location in the array with one character each,
as follows: the first thread with the character 'A', the second with 'B' and so on up to 'E'.

    Each "producer" thread will count how many characters it has entered into the array;
    the first thread will terminate when it has entered 100,000 characters, the second 200,000 and so on.
    The main thread will continuously display the contents of the array until all the "producer" threads terminate,
at which point it will take over their state and terminate the process.
*/

fn main(){
    println!("Hello world!")
}