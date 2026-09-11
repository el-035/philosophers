# Philosophers

Philosophers is a multithreaded simulation of the dining philosophers problem,
implemented in C as part of the 42 curriculum. Each philosopher alternates
between eating, sleeping, and thinking while competing for shared forks.

The project explores threads, mutexes, synchronization, timing, and avoiding
deadlocks and data races.

## Build

```sh
cd philo
make
```

This creates the `philo` executable.

## Usage

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
    [number_of_times_each_philosopher_must_eat]
```

All times are expressed in milliseconds. The final meal-count argument is
optional; when supplied, the simulation stops after every philosopher has eaten
at least that many times.

Example:

```sh
./philo 5 800 200 200 5
```

Each output line contains the elapsed time, philosopher number, and current
action:

```text
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
```

The simulation stops when a philosopher dies or when the optional meal target
has been reached by every philosopher.
