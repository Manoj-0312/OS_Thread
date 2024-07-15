import threading
import time
import random

shared_variable = 0

lock = threading.Lock()

def thread_work(id):
    global shared_variable
    print(f"Thread {id} starting...")
    
    for _ in range(5):
        with lock:
            shared_variable += 1
            print(f"Thread {id}: Shared variable incremented to {shared_variable}")
        
        time.sleep(random.random())
    
    print(f"Thread {id} finished.")

num_threads = 3

threads = []

for i in range(num_threads):
    thread = threading.Thread(target=thread_work, args=(i,))
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

print("All threads have finished.")
print(f"Final value of shared variable: {shared_variable}")