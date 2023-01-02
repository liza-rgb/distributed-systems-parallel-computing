import random
import threading as th

# функція конвертуванняя списку в рядок
def convert_list_to_str(list):
    new_str = []
    for el in list:
        new_str.append(str(el))
    return new_str

# обчислення чисел відповідно до гіпотези Колаца
def calculate_collatz(N):
    if N % 2 == 1:
        return 3 * N + 1
    else:
        return N / 2

def collatz_threading(queue, mutex, results):
    with mutex:
        if(len(queue) == 0):
            return 
        value = queue.pop(0)
    while True:
        n = value
        while n != 1:
            n = calculate_collatz(n)
            results[value - 1].append(n)
        with mutex:
            if(len(queue) == 0):
                break
            value = queue.pop(0)

def main():
    amount_of_threads = 10
    N = random.randint(100000, 200000)
    results = []

    for i in range(N):
        results.append([i + 1])
    queue = list(range(1, N+1))
    threadpool = []
    mutex =  th.Lock()
    for _ in range(amount_of_threads):
        threadpool.append(th.Thread(target = collatz_threading, args = (queue, mutex, results)))
    for thread in threadpool:
        thread.start()
    for thread in threadpool:
        thread.join()

    # записуємо результати виконання до файлу
    with open("results.txt",'w') as f:
        for result in results:
            f.write(', '.join(convert_list_to_str(result)) + '\n')

if __name__ == "__main__":
    main()