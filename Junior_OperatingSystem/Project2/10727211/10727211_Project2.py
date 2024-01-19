import copy

mode = 0
# mode = 0 ( info )
# mode = 1 ( debug )
class Process:
    def __init__(self, process_ID, cpu_burst, arrival_time, priority):
        self.process_ID = int(process_ID)
        self.cpu_burst = int(cpu_burst)
        self.arrival_time = int(arrival_time)
        self.priority = int(priority)

        self.remain_time = self.cpu_burst
        self.turnaround_time = None
        self.waiting_time = None

    def debug_print_process_status(self):
        print('ID   CPU_Burst   Arrival Priority   | remain  turnaround  waiting')
        print(self.process_ID, ' ', self.cpu_burst, '           ', self.arrival_time, '    ', self.priority, '        ',
              self.remain_time, '      ', self.turnaround_time, '      ', self.waiting_time)
        print()


class Schedule:
    def __init__(self, info, job_task, time_slice):
        self.gantt_chart = []
        self.waiting_list = None
        self.turnaround_time_list = None
        self.running(info, job_task, time_slice)

    def running(self, info, job_task, time_slice):
        # input : Process[][] info
        # input : string      job_task
        # input : int     time_slice

        submit_queue = []
        for i in info:
            submit_queue.append(Process(i[0], i[1], i[2], i[3]))

        if job_task is '1':
            self.gantt_chart.append(['FCFS'])
            terminate_queue = self.fcfs(submit_queue)
            self.analyaze('FCFS', terminate_queue)

        elif job_task is '2':
            self.gantt_chart.append(['RR'])
            terminate_queue = self.rr(submit_queue, time_slice)
            self.analyaze('RR', terminate_queue)

        elif job_task is '3':
            self.gantt_chart.append(['SRTF'])
            terminate_queue = self.srtf(submit_queue)
            self.analyaze('SRTF', terminate_queue)

        elif job_task is '4':
            self.gantt_chart.append(['PPRR'])
            terminate_queue = self.pprr(submit_queue, time_slice)
            self.analyaze('PPRR', terminate_queue)

        elif job_task is '5':
            self.gantt_chart.append(['HRRN'])
            terminate_queue = self.hrrn(submit_queue)
            self.analyaze('HRRN', terminate_queue)

        elif job_task is '6':
            self.gantt_chart.append(['All'])
            self.all(submit_queue, time_slice, gantt_chart)

    def all(self, submit_queue, time_slice, gantt_chart):  # Task6 all
        self.gantt_chart.append(['==        FCFS=='])
        terminate_queue_fcfs = self.fcfs(copy.deepcopy(submit_queue))
        self.analyaze('FCFS', terminate_queue_fcfs)

        self.gantt_chart.append(['==          RR=='])
        terminate_queue_rr = self.rr(copy.deepcopy(submit_queue), time_slice)
        self.analyaze('RR', terminate_queue_rr)

        self.gantt_chart.append(['==        SRTF=='])
        terminate_queue_srtf = self.srtf(copy.deepcopy(submit_queue))
        self.analyaze('SRTF', terminate_queue_srtf)

        self.gantt_chart.append(['==        PPRR=='])
        terminate_queue_pprr = self.pprr(copy.deepcopy(submit_queue), time_slice)
        self.analyaze('PPRR', terminate_queue_pprr)

        self.gantt_chart.append(['==        HRRN=='])
        terminate_queue_hrrn = self.hrrn(copy.deepcopy(submit_queue))
        self.analyaze('HRRN', terminate_queue_hrrn)

        self.turnaround_time_list.append(['==========================================================='])
        return gantt_chart

    def fcfs(self, submit_queue):  # Task1  First Come First Serve
        gantt_content = []

        ready_queue = []
        running_queue = None
        terminate_queue = []
        self.sort_process('process_ID', submit_queue)
        self.sort_process('arrival_time', submit_queue)
        time = 0

        while len(submit_queue) is not 0 or len(ready_queue) is not 0 or running_queue is not None:  # runningloop start
            submit_queue, ready_queue = self.detect_job_arrival(submit_queue, ready_queue, time)

            running_queue, terminate_queue = self.detect_job_terminal(running_queue, terminate_queue, time)

            if running_queue is None:  # dispatch job
                if len(ready_queue) is not 0:
                    running_queue = ready_queue[0]
                    running_queue.waiting_time = time - running_queue.arrival_time
                    ready_queue.pop(0)
                    running_queue.remain_time = running_queue.remain_time - 1
            else:
                running_queue.remain_time = running_queue.remain_time - 1

            gantt_content.append(self.convert_processID(running_queue))
            time = time + 1  # running loop end

        gantt_content.pop(-1)
        self.gantt_chart.append(gantt_content)
        return terminate_queue

    def rr(self, submit_queue, time_slice):  # Task2  Round Robin
        gantt_content = []

        ready_queue = []
        running_queue = None
        terminate_queue = []

        self.sort_process('process_ID', submit_queue)
        self.sort_process('arrival_time', submit_queue)
        time = 0
        time_reciprocal = 0
        while len(submit_queue) is not 0 or len(ready_queue) is not 0 or running_queue is not None:  # runningloop start
            submit_queue, ready_queue = self.detect_job_arrival(submit_queue, ready_queue, time)

            running_queue, terminate_queue = self.detect_job_terminal(running_queue, terminate_queue, time)

            if running_queue is not None:  # detect timeout
                if time_reciprocal is 0:
                    ready_queue.append(running_queue)
                    running_queue = None

            if running_queue is None:  # dispatch job
                if len(ready_queue) is not 0:
                    running_queue = ready_queue[0]
                    ready_queue.pop(0)
                    running_queue.remain_time = running_queue.remain_time - 1
                    time_reciprocal = time_slice - 1
            else:
                running_queue.remain_time = running_queue.remain_time - 1
                time_reciprocal = time_reciprocal - 1

            gantt_content.append(self.convert_processID(running_queue))
            time = time + 1  # running loop end

        gantt_content.pop(-1)
        self.gantt_chart.append(gantt_content)
        return terminate_queue

    def srtf(self, submit_queue):  # Task3 Shortest Remaining Time First
        gantt_content = []

        ready_queue = []
        running_queue = None
        terminate_queue = []

        self.sort_process('process_ID', submit_queue)
        self.sort_process('arrival_time', submit_queue)
        time = 0
        while len(submit_queue) is not 0 or len(ready_queue) is not 0 or running_queue is not None:  # runningloop start
            submit_queue, ready_queue = self.detect_job_arrival(submit_queue, ready_queue, time)

            running_queue, terminate_queue = self.detect_job_terminal(running_queue, terminate_queue, time)

            if running_queue is not None:
                ready_queue.append(running_queue)
                running_queue = None

            self.sort_process('process_ID', ready_queue)
            self.sort_process('arrival_time', ready_queue)
            self.sort_process('remain_time', ready_queue)

            # if running_queue is None:
            if len(ready_queue) is not 0:  # dispatch job
                running_queue = ready_queue[0]
                ready_queue.pop(0)
                running_queue.remain_time = running_queue.remain_time - 1

            gantt_content.append(self.convert_processID(running_queue))
            time = time + 1  # running loop end

        gantt_content.pop(-1)
        self.gantt_chart.append(gantt_content)
        return terminate_queue

    def pprr(self, submit_queue, time_slice):  # Task4  Preemptive Priority + RR
        gantt_content = []

        ready_queue = []
        running_queue = None
        terminate_queue = []

        # self.sort_process('process_ID', submit_queue)
        self.sort_process('arrival_time', submit_queue)
        time = 0
        time_reciprocal = 0
        while len(submit_queue) is not 0 or len(ready_queue) is not 0 or running_queue is not None:  # runningloop start
            submit_queue, ready_queue = self.detect_job_arrival(submit_queue, ready_queue, time)

            running_queue, terminate_queue = self.detect_job_terminal(running_queue, terminate_queue, time)

            if running_queue is not None:  # detect timeout
                if time_reciprocal is 0:
                    ready_queue.append(running_queue)
                    running_queue = None

            self.sort_process('priority', ready_queue)  # 與RR差異

            if running_queue is None:  # dispatch job
                if len(ready_queue) is not 0:
                    running_queue = ready_queue[0]
                    ready_queue.pop(0)
                    running_queue.remain_time = running_queue.remain_time - 1
                    time_reciprocal = time_slice - 1
            else:
                if len(ready_queue) is not 0:
                    if running_queue.priority > ready_queue[0].priority:  # difference
                        ready_queue.append(running_queue)
                        running_queue = ready_queue[0]
                        ready_queue.pop(0)
                        time_reciprocal = time_slice

                running_queue.remain_time = running_queue.remain_time - 1
                time_reciprocal = time_reciprocal - 1

            gantt_content.append(self.convert_processID(running_queue))
            time = time + 1  # running loop end

        gantt_content.pop(-1)
        self.gantt_chart.append(gantt_content)
        return terminate_queue

    def hrrn(self, submit_queue):  # Task5  Highest Response Ratio Next
        gantt_content = []

        ready_queue = []
        running_queue = None
        terminate_queue = []

        self.sort_process('process_ID', submit_queue)
        self.sort_process('arrival_time', submit_queue)
        time = 0
        while len(submit_queue) is not 0 or len(ready_queue) is not 0 or running_queue is not None:  # runningloop start
            submit_queue, ready_queue = self.detect_job_arrival(submit_queue, ready_queue, time)

            running_queue, terminate_queue = self.detect_job_terminal(running_queue, terminate_queue, time)

            # Calculate Response Ratio
            for i in range(len(ready_queue)):
                temp = ready_queue[i]
                response_ratio = (time - temp.arrival_time + temp.remain_time) / temp.cpu_burst
                ready_queue[i].priority = response_ratio

            self.sort_process('process_ID', ready_queue)
            self.sort_process('arrival_time', ready_queue)
            self.sort_process('response_ratio', ready_queue)

            if running_queue is None:  # dispatch job
                if len(ready_queue) is not 0:
                    running_queue = ready_queue[0]
                    ready_queue.pop(0)
                    running_queue.remain_time = running_queue.remain_time - 1
            else:
                running_queue.remain_time = running_queue.remain_time - 1

            gantt_content.append(self.convert_processID(running_queue))
            time = time + 1  # running loop end

        gantt_content.pop(-1)
        self.gantt_chart.append(gantt_content)
        return terminate_queue

    def sort_process(self, type_of_sort, queue):

        if type_of_sort is 'process_ID':
            for i in range(len(queue)):  # sort pid first
                tempNum = queue[i]
                j = i - 1
                while j >= 0 and tempNum.process_ID < queue[j].process_ID:
                    queue[j + 1] = queue[j]
                    j = j - 1
                queue[j + 1] = tempNum

        elif type_of_sort is 'cpu_burst':
            for i in range(len(queue)):
                tempNum = queue[i]
                j = i - 1
                while j >= 0 and tempNum.cpu_burst < queue[j].cpu_burst:
                    queue[j + 1] = queue[j]
                    j = j - 1
                queue[j + 1] = tempNum

        elif type_of_sort is 'arrival_time':
            for i in range(len(queue)):
                tempNum = queue[i]
                j = i - 1
                while j >= 0 and tempNum.arrival_time < queue[j].arrival_time:
                    queue[j + 1] = queue[j]
                    j = j - 1
                queue[j + 1] = tempNum

        elif type_of_sort is 'priority':
            for i in range(len(queue)):
                tempNum = queue[i]
                j = i - 1
                while j >= 0 and tempNum.priority < queue[j].priority:
                    queue[j + 1] = queue[j]
                    j = j - 1
                queue[j + 1] = tempNum

        elif type_of_sort is 'response_ratio':
            for i in range(len(queue)):
                tempNum = queue[i]
                j = i - 1
                while j >= 0 and tempNum.priority > queue[j].priority:
                    queue[j + 1] = queue[j]
                    j = j - 1
                queue[j + 1] = tempNum
        elif type_of_sort is 'remain_time':
            for i in range(len(queue)):
                tempNum = queue[i]
                j = i - 1
                while j >= 0 and tempNum.remain_time < queue[j].remain_time:
                    queue[j + 1] = queue[j]
                    j = j - 1
                queue[j + 1] = tempNum

        else:
            print('Error type in sort_process')
        return queue

    def detect_job_arrival(self, submit_queue, ready_queue, time):
        while len(submit_queue) is not 0:
            if submit_queue[0].arrival_time is time:
                ready_queue.append(submit_queue[0])
                submit_queue.pop(0)
            else:
                break
        return submit_queue, ready_queue

    def detect_job_terminal(self, running_queue, terminate_queue, time):
        if running_queue is not None and running_queue.remain_time is 0:  # terminal_job
            running_queue.turnaround_time = time - running_queue.arrival_time
            running_queue.waiting_time = time - running_queue.arrival_time - running_queue.cpu_burst
            terminate_queue.append(running_queue)
            running_queue = None
        return running_queue, terminate_queue

    def convert_processID(self, process):
        if process is None:
            return '-'
        elif process.process_ID is 0:
            return '0'
        elif process.process_ID is 1:
            return '1'
        elif process.process_ID is 2:
            return '2'
        elif process.process_ID is 3:
            return '3'
        elif process.process_ID is 4:
            return '4'
        elif process.process_ID is 5:
            return '5'
        elif process.process_ID is 6:
            return '6'
        elif process.process_ID is 7:
            return '7'
        elif process.process_ID is 8:
            return '8'
        elif process.process_ID is 9:
            return '9'
        elif process.process_ID is 10:
            return 'A'
        elif process.process_ID is 11:
            return 'B'
        elif process.process_ID is 12:
            return 'C'
        elif process.process_ID is 13:
            return 'D'
        elif process.process_ID is 14:
            return 'E'
        elif process.process_ID is 15:
            return 'F'
        elif process.process_ID is 16:
            return 'G'
        elif process.process_ID is 17:
            return 'H'
        elif process.process_ID is 18:
            return 'I'
        elif process.process_ID is 19:
            return 'J'
        elif process.process_ID is 20:
            return 'K'
        elif process.process_ID is 21:
            return 'L'
        elif process.process_ID is 22:
            return 'M'
        elif process.process_ID is 23:
            return 'N'
        elif process.process_ID is 24:
            return 'O'
        elif process.process_ID is 25:
            return 'P'
        elif process.process_ID is 26:
            return 'Q'
        elif process.process_ID is 27:
            return 'R'
        elif process.process_ID is 28:
            return 'S'
        elif process.process_ID is 29:
            return 'T'
        elif process.process_ID is 30:
            return 'U'
        elif process.process_ID is 31:
            return 'V'
        elif process.process_ID is 32:
            return 'W'
        elif process.process_ID is 33:
            return 'X'
        elif process.process_ID is 34:
            return 'Y'
        elif process.process_ID is 35:
            return 'Z'

    def analyaze(self, type, terminate_queue):
        # input : [][] terminate_queue
        # output : [][]   self.waiting_list
        # output : [][]   self.turnaround_time_list
        self.sort_process('process_ID', terminate_queue)

        if self.waiting_list is None and self.turnaround_time_list is None:
            self.waiting_list = []
            self.waiting_list.append(['waiting'])
            self.waiting_list.append(['ID'])
            self.waiting_list.append(['==========================================================='])
            for i in terminate_queue:
                self.waiting_list.append([i.process_ID])
            self.waiting_list.append(['==========================================================='])

            self.turnaround_time_list = []
            self.turnaround_time_list.append(['Turnaround Time'])
            self.turnaround_time_list.append(['ID'])
            self.turnaround_time_list.append(['==========================================================='])
            for i in terminate_queue:
                self.turnaround_time_list.append([i.process_ID])
            # self.turnaround_time_list.append(['==========================================================='])

        self.waiting_list[1].append(type)
        for i in range(len(terminate_queue)):
            self.waiting_list[3 + i].append(terminate_queue[i].waiting_time)

        self.turnaround_time_list[1].append(type)
        for i in range(len(terminate_queue)):
            self.turnaround_time_list[3 + i].append(terminate_queue[i].turnaround_time)

def readfile():
    path = input("Please enter File Name (eg. input1 、 input1.txt) : ")
    # path = 'input3'
    a = path[-4:]
    if a != '.txt':
        path = path + '.txt'

    data_input = []
    f = None
    job_task = None
    time_slice = None
    try:
        f = open(path, 'r')
        job_task, time_slice = f.readline().split()

        input_list = f.readline()
        input_list = [str(x) for x in f.read().split()]
        while len(input_list) is not 0:
            # process_ID (string)     cpu_burst (int)     arrival_time (int)     priority (int)
            data_input.append(input_list[:4])
            input_list = input_list[4:]

    except IOError:
        print('Error: can not found ' + path)
        if f:
            f.close()
    finally:
        if f:
            f.close()

    return data_input, job_task, time_slice, path[:-4]


def writefile(path, gantt_chart, waiting_list, turnaround_time_list):
    path_output = 'out_' + path + '.txt'
    with open(path_output, 'w', encoding='UTF-8') as f:
        for i in range(len(gantt_chart)):
            if i is 0 or i % 2 is 1:
                for j in range(len(gantt_chart[i])):
                    f.write(str(gantt_chart[i][j]))
                f.write('\n')

            else:
                for j in range(len(gantt_chart[i])):
                    f.write(gantt_chart[i][j])
                f.write('\n')
        f.write('===========================================================' + '\n')
        f.write('\n')

        for i in range(len(waiting_list)):
            if i is 0 or i is 2 or i is len(waiting_list):
                f.write(str(waiting_list[i][0]) + '\n')
            else:
                for j in range(len(waiting_list[i])-1):
                    f.write(str(waiting_list[i][j]) + '\t')
                f.write(str(waiting_list[i][-1]) + '\n')

        f.write('\n')

        for i in range(len(turnaround_time_list)):
            if i is 0 or i is 2 or i is len(turnaround_time_list):
                f.write(str(turnaround_time_list[i][0]) + '\n')
            else:
                for j in range(len(turnaround_time_list[i]) - 1):
                    f.write(str(turnaround_time_list[i][j]) + '\t')
                f.write(str(turnaround_time_list[i][-1]) + '\n')

        # f.write('\n')


if __name__ == '__main__':
    while True:
        info, job_task, time_slice, path = readfile()
        waiting_list = []
        turnaround_time_list = []
        gantt_chart = []
        result = Schedule(info, job_task, int(time_slice))
        writefile(path, result.gantt_chart, result.waiting_list, result.turnaround_time_list)

        if mode is 1:
            for i in result.gantt_chart:
                print(i)
            for i in result.waiting_list:
                print(i)
            for i in result.turnaround_time_list:
                print(i)

        print('done')
        print()
        print()
