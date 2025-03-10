# Philosophers Project




## Description

The Philosophers project is a multi-threading and synchronization project aimed at simulating the classical dining philosophers problem. The goal is to implement a solution in which a set of philosophers seated at a round table engage in actions of thinking and eating while avoiding deadlock and starvation.

## Requirements

To run the Philosophers project, you need:

- A C compiler (such as GCC or Clang)
- Basic understanding of concurrency and synchronization techniques
- Familiarity with POSIX threads and mutexes

## Installation

1. Clone the repository:

   ```bash
   git clone <repository_url>
   ```

2. Navigate to the project directory:

   ```bash
   cd philosophers
   ```

3. Compile the program:

   ```bash
   make
   ```

## Usage

To execute the program, run the following command:

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

Replace the placeholders with appropriate values:

- `[number_of_philosophers]`: The number of philosophers seated at the table.
- `[time_to_die]`: The time (in milliseconds) after which a philosopher dies if they haven't eaten.
- `[time_to_eat]`: The time (in milliseconds) it takes for a philosopher to finish eating.
- `[time_to_sleep]`: The time (in milliseconds) a philosopher spends sleeping after eating or thinking.
- optional `[number_of_times_each_philosopher_must_eat]`: The number of times each philosopher must eat before the simulation ends.

## Keep in mind before input data : 

Thinking time or "t_think" is the contention time waiting for the forks
If
#### Even amount of philosophers 
   - t_die = t_eat + t_sleep + 10
   - if (t_eat <= t_sleep) === 0 t_think
      - No contention and the process is symetric philos will sleep and eat.
      - exs: 
         - ./philo 4 800 200 350
         - ./philo 4 800 200 200
   - if (t_eat > t_sleep) ===  t_think = t_eat - t_sleep
         - ./philo 4 800 200 100
         - ./philo 4 800 200 60

#### Odd amount of philosophers :
   - t_die = t_eat * 2 + t_sleep + 10
   - if (t_eat = t_sleep) === t_think = t_eat 
      - ./philo 3 800 200 200
      - ./philo 3 800 100 100
   - if (t_eat < t_sleep) === t_think = t_eat *2 - t_sleep
      - ./philo 3 800 200 300
      - ./philo 3 800 200 350
      - ./philo 3 800 200 400


   


exec projet ex:
```bash
# Normal launch
./philo 4 410 200 200 5

# Leaks
valgrind ./philo 2 800000 20 20 1

valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all ./philo 2 800000 20 20 1

# Data races
valgrind --tool=helgrind ./philo 2 8000000 20 20 1
valgrind --tool=helgrind --history-level=full -s ./philo 2 8000000 20 20 1
# data races complet report :
valgrind --tool=helgrind --verbose --history-level=full -s ./philo 2 8000000 20 20 1
```

usefull comands : 
```bash
# clean vs-code cash
rm -rf ~/.config/Code/CachedData

# While the project is running you can check the proces (PID) data with these comand : 
ps aux | grep "path of your projet"
```

## Contributing

Contributions to the project are welcome! If you have any ideas, enhancements, or bug fixes, feel free to open an issue or submit a pull request.



Ref proyects : 
- https://github.com/zelhajou/ft_unix_philosophers?tab=readme-ov-file
- https://github.com/MarkosComK/42-Philosophers

