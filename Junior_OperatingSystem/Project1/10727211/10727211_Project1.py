import threading
from multiprocessing import Pool
import time
from datetime import datetime, timezone, timedelta


def bubble_sort(data_bubble_sort):
    temp = 0
    n = len(data_bubble_sort)
    for i in range(n - 2):  # 數字越大 先往下沉
        store = False
        for j in range(n - i - 1):
            if data_bubble_sort[j] > data_bubble_sort[j + 1]:
                data_bubble_sort[j], data_bubble_sort[j + 1] = data_bubble_sort[j + 1], data_bubble_sort[j]
                store = True
        temp += 1
        if store is False:
            temp = n - 2
        print('\r' + '[Bubble Sort Progress]:[%s%s]%.2f%%;' % (
            '█' * int(temp * 20 / (n - 2)), ' ' * (20 - int(temp * 20 / (n - 2))),
            float(temp / (n - 2) * 100)), end='')
        if store is False:
            break
    return data_bubble_sort


def merge_sort(data_merge_sort):
    if len(data_merge_sort) > 1:
        mid = len(data_merge_sort) // 2  # integer divide
        left_merge_sort = data_merge_sort[:mid]
        right_merge_sort = data_merge_sort[mid:]

        # Recursive call on each half
        merge_sort(left_merge_sort)
        merge_sort(right_merge_sort)

        merge(left_merge_sort, right_merge_sort, data_merge_sort)
    return data_merge_sort


def merge(left_merge, right_merge, data_merge=None):
    temp = 0
    n = len(left_merge) + len(right_merge)
    if data_merge is None:
        data_merge = []
    while len(left_merge) is not 0 and len(right_merge) is not 0:
        if left_merge[0] < right_merge[0]:
            data_merge.append(left_merge[0])
            left_merge.pop(0)
        else:
            data_merge.append(right_merge[0])
            right_merge.pop(0)
        temp += 1
        print('\r' + '[Merge Progress]:[%s%s]%.2f%%;' % (
            '█' * int(temp * 20 / n), ' ' * (20 - int(temp * 20 / n)),
            float(temp / n * 100)), end='')

    while len(left_merge) is not 0:
        data_merge.append(left_merge[0])
        left_merge.pop(0)
        temp += 1
        print('\r' + '[Merge Progress]:[%s%s]%.2f%%;' % (
            '█' * int(temp * 20 / n), ' ' * (20 - int(temp * 20 / n)),
            float(temp / n * 100)), end='')
    while len(right_merge) is not 0:
        data_merge.append(right_merge[0])
        right_merge.pop(0)
        temp += 1
        print('\r' + '[Merge Progress]:[%s%s]%.2f%%;' % (
            '█' * int(temp * 20 / n), ' ' * (20 - int(temp * 20 / n)),
            float(temp / n * 100)), end='')
    return data_merge


def one_process_bubblesort_merge(data_task4, k_task4):
    data_part_task4 = []
    separate_data(data_task4, data_part_task4, k_task4)
    print()
    for i in data_part_task4:
        bubble_sort(i)
        print()

    while len(data_part_task4) is not 1:
        merge_count_task4 = len(data_part_task4) // 2
        for i in range(merge_count_task4):
            temp_1_task4 = data_part_task4[i]  # copy 頭
            temp_2_task4 = data_part_task4[-1]  # copy 尾
            data_part_task4[i] = []
            data_part_task4.pop(-1)  # 去尾
            merge(temp_1_task4, temp_2_task4, data_part_task4[i])
            print()
    return data_part_task4[0]


def separate_data(data, data_part, k):  # data_part is 2 dimensional vector

    size_of_data_part = len(data) // k
    for i in range(k):

        if i is k - 1:
            new_data_part = data[size_of_data_part * i:]
            data_part.append(new_data_part)
        else:
            new_data_part = data[size_of_data_part * i:size_of_data_part * (i + 1)]
            # index_of_data += size_of_data_part
            data_part.append(new_data_part)

    return data_part


def readK(num_of_data):
    while True:
        k = input("請輸入K:(將資料切成K分):")
        if k.isdigit() is True:
            if int(k) <= 0:
                print("[Error]", k, "is Positive Number!, Please try again!")
            elif int(k) > num_of_data:
                print("[Error]", k, "is bigger than data's size(", num_of_data, ") Please try again!")
            else:
                break
        else:
            print("[Error]", k, "is Not Positive Number!, Please try again!")
    return int(k)


def read_file():
    path = input("Please enter File Name (eg. input_1w 、 input_1w.txt) : ")
    a = path[-4:]
    if a != '.txt':
        path = path + '.txt'

    f = None
    try:
        f = open(path, 'r')
        data_input = [int(x) for x in f.read().split()]
    except IOError:
        print('Error: can not found ' + path)
        if f:
            f.close()
    finally:
        if f:
            f.close()
    # with open(path) as f:
    #     data = [int(x) for x in f.read().split()]

    return data_input, path[:-4]


def write_file(path, task, cpu_time, data, k=None):
    path_output = path + '_output' + task + '.txt'
    f = open(path_output, 'w')
    temp = 0
    f.write("Sort :" + '\n')
    n = len(data)
    for i in data:
        f.write(str(i) + '\n')
        temp += 1
        print('\r' + '[Write File Progress]:[%s%s]%.2f%%;' % (
            '█' * int(temp * 20 / n), ' ' * (20 - int(temp * 20 / n)),
            float(temp / n * 100)), end='')
    print()
    if k is not None:
        f.write("資料共切成" + str(k) + "份" + '\n')
    f.write("CPU Time : " + str(cpu_time) + '\n')
    f.write("Output Time : " + str(datetime.utcnow().replace(tzinfo=timezone.utc).astimezone
                                   (timezone(timedelta(hours=8)))) + '\n')

if __name__ == '__main__':
    while True:
        print()
        print("******************************************************")
        print("**     Welcome to 10727211's Homework1              **")
        print("* 1. 直接BubbleSort()                                 *")
        print("* 2. K個Thread 進行 BubbleSort()、MergeSort()          *")
        print("* 3. K個Process 進行 BubbleSort()、MergeSort()         *")
        print("* 4. data切K分、一個process進行BubbleSort()、MergeSort() *")
        print("* 0. exit                                             *")
        print("*******************************************************")
        task = input("---------->請選擇(0,1,2,3,4): ")
        if task is "0":
            break
        elif task is "1":
            data, path = read_file()
            time_1_start = time.time()  # time start ----------------------
            bubble_sort(data)
            print()
            time_1_end = time.time()  # time end ----------------------
            write_file(path, '1', time_1_end - time_1_start, data)
        elif task is "2":
            data, path = read_file()
            time_2_start = time.time()  # time start ----------------------
            k_task2 = readK(len(data))
            threads = []
            data_part = []

            separate_data(data, data_part, k_task2)

            for i in range(k_task2):  # K-Thread for BubbleSort
                threads.append(threading.Thread(target=bubble_sort, args=(data_part[i],)))
                threads[i].start()
            for i in range(k_task2):
                threads[i].join()

            print()
            while len(data_part) is not 1:  # Thread for Merge
                threads.clear()
                merge_count = len(data_part) // 2
                for i in range(merge_count):
                    temp_1 = data_part[i]  # copy 頭
                    temp_2 = data_part[-1]  # copy 尾
                    data_part[i] = []
                    data_part.pop(-1)  # 去尾
                    threads.append(threading.Thread(target=merge, args=(temp_1, temp_2, data_part[i],)))
                    threads[i].start()
                for i in range(merge_count):
                    threads[i].join()

            data = data_part[0]
            print()
            time_2_end = time.time()  # time end ----------------------
            write_file(path=path, task='2', cpu_time=time_2_end - time_2_start, data=data, k=k_task2)
        elif task is "3":
            data, path = read_file()
            time_3_start = time.time()  # time start ----------------------
            k_task3 = readK(len(data))
            data_part = []

            separate_data(data, data_part, k_task3)

            with Pool(processes=k_task3) as pool:
                data_part = pool.map(bubble_sort, data_part)  # K-Process for BubbleSort
                print()
                while len(data_part) is not 1:  # Pools for Merge
                    temp_left_data_part = None
                    if len(data_part) % 2 is 1:
                        temp_left_data_part = data_part[-1]
                        data_part.pop(-1)
                    data_part_1 = data_part[:len(data_part) // 2]
                    data_part_2 = data_part[len(data_part) // 2:]

                    data_part = pool.starmap(merge, zip(data_part_1, data_part_2))
                    print()

                    if temp_left_data_part is not None:
                        data_part.append(temp_left_data_part)

            data = data_part[0]
            time_3_end = time.time()  # time end ----------------------
            write_file(path=path, task='3', cpu_time=time_3_end - time_3_start, data=data, k=k_task3)
        elif task is "4":
            data, path = read_file()
            time_4_start = time.time()  # time start ----------------------
            k_task4 = readK(len(data))
            data_part = []
            with Pool(processes=1) as pool:  # pool = Pool(1)
                data = pool.starmap(one_process_bubblesort_merge, [(data, k_task4)])  # 合併頭尾
                data = data[0]
            time_4_end = time.time()  # time end ----------------------
            write_file(path=path, task='4', cpu_time=time_4_end - time_4_start, data=data, k=k_task4)
        else:
            print("Error, Please Try again!")
