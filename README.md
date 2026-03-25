*This project has been created as part of the 42 curriculum by gabrgarc.*

# Philosophers

## Description
The **Philosophers** project is an implementation of the classic "Dining Philosophers problem". The main goal of this project is to learn the basics of threading a process, understand how to create and manipulate threads, and discover the concept of mutexes in C. It serves as an introduction to concurrent programming, highlighting the challenges of avoiding deadlocks, managing shared resources (forks), and preventing data races.

## Instructions

### Compilation
To compile the project, run the `make` command at the root of the repository. This will generate the `philo` executable.
```bash
make
```

### Execution
You can run the program using the following syntax:
```bash
./philo <number_of_philosophers> <time_of_die> <time_of_eat> <time_of_sleep> [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
* `number_of_philosophers`: The number of philosophers and also the number of forks.
* `time_of_die` (in milliseconds): If a philosopher didn’t start eating `time_of_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
* `time_of_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
* `time_of_sleep` (in milliseconds): The time a philosopher will spend sleeping.
* `number_of_times_each_philosopher_must_eat` *(optional)*: If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## Resources

Here are the classic references and tutorials used to build the knowledge required for this project:

* **Understanding the logic and time measurement:** [The Dining Philosophers (Medium Article)](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315)
* **Creating and manipulating threads:** [Unix Threads in C (YouTube Playlist)](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=JvY1OjxM99K_rY9a)
* **Measuring time in C:** [How to use gettimeofday() (YouTube Video)](https://www.youtube.com/watch?v=cunJcNgtxMk)

### AI Usage
AI (Large Language Models) was used during this project specifically for formatting, structuring, and generating the English text of this `README.md` file to ensure it meets the formatting requirements.
