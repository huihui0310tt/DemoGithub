import copy


class Job:
    def __init__(self, name):
        self.name = name
        self.frequency = 0

    def count_frequency(self):
        self.frequency = self.frequency + 1

    def reset_frequenY(self):
        self.frequency = 0

    def debug_print_info(self):
        print('name is : ', self.name)
        print('frequency is : ', str(self.frequency))
        print()


class Simulate:
    def __init__(self, frame_size, job_list, task):
        self.frame_size = frame_size
        self.job_list = []
        self.frame_table = []
        self.task = task
        self.page_fault = 0
        self.page_replace = 0
        self.log = []

        for i in job_list:
            if i is not '\n':
                self.job_list.append(self.init_joblist(i))

        self.running(task)

    def init_joblist(self, job_name):
        for i in self.job_list:
            if i.name == job_name:
                return i

        return Job(job_name)

    def count_page_fault(self):
        self.page_fault = self.page_fault + 1

    def count_page_replace(self):
        self.page_replace = self.page_replace + 1

    def set_log(self, job_id, page_fault):
        # page_fault = true :  NOT page_fault
        # page_fault = false :     page_fault
        if len(self.log) is 0:
            if self.task is 1:
                self.log.append('--------------FIFO-----------------------')
            elif self.task is 2:
                self.log.append('--------------LRU-----------------------')
            elif self.task is 3:
                self.log.append('--------------Least Frequently Used Page Replacement-----------------------')
            elif self.task is 4:
                self.log.append('--------------Most Frequently Used Page Replacement -----------------------')
            elif self.task is 5:
                self.log.append('--------------Least Frequently Used LRU Page Replacement-----------------------')
            elif self.task is 6:
                self.log.append('--------------Most Frequently Used LRU Page Replacement -----------------------')
            else:
                print('No such type is line 64')
        one_log = [job_id, [], page_fault]
        for i in self.frame_table:
            one_log[1].append(i.name)
        self.log.append(one_log)

    def hit_table(self, instr, name):
        # instr : FIFO LRU
        record_index = None
        temp_job = None
        for i in range(len(self.frame_table)):
            if self.frame_table[i].name is name:
                record_index = i
                temp_job = self.frame_table[i]
                temp_job.count_frequency()
                break

        if record_index is None:
            self.count_page_fault()
            return False
        else:
            if instr is 'FIFO':
                pass
            elif instr is 'LRU':
                self.frame_table.pop(record_index)
                self.frame_table.append(temp_job)
            else:
                print('No such case')

            return True

    def pop_table(self, instr):
        if len(self.frame_table) is self.frame_size:
            self.count_page_replace()
            if instr is 'formal':
                self.frame_table.pop(0)
            elif instr is 'LFU':
                record_index = None

                for i in range(len(self.frame_table)):
                    if record_index is None:
                        record_index = i
                    elif self.frame_table[i].frequency < self.frame_table[record_index].frequency:
                        record_index = i

                self.frame_table.pop(record_index)
            elif instr is 'MFU':
                record_index = 0

                for i in range(len(self.frame_table)):
                    if self.frame_table[i].frequency > self.frame_table[record_index].frequency:
                        record_index = i

                self.frame_table.pop(record_index)
            else:
                print('no such type')

    def running(self, task):

        for i in self.job_list:

            if task is 1 or task is 3 or task is 4:
                have_hit = self.hit_table(instr='FIFO', name=i.name)
            elif task is 2 or task is 5 or task is 6:
                have_hit = self.hit_table(instr='LRU', name=i.name)
            else:
                print('error')

            if have_hit is False:
                if task is 1 or task is 2:
                    self.pop_table(instr='formal')
                elif task is 3 or task is 5:
                    self.pop_table(instr='LFU')
                elif task is 4 or task is 6:
                    self.pop_table(instr='MFU')
                else:
                    print('error')

                self.frame_table.append(i)
                i.reset_frequenY()
            self.set_log(job_id=i.name, page_fault=have_hit)

    def getlog(self):
        for i in range(len(self.log)):
            if i is not 0:
                # print(str(i[1]))
                self.log[i][1].reverse()
                if self.log[i][2] is True:
                    self.log[i][2] = 'T'
                else:
                    self.log[i][2] = 'F'

        info = 'Page Fault = ' + str(self.page_fault) + '  Page Replaces = ' + str(
            self.page_replace) + '  Page Frames = ' + str(self.frame_size)
        self.log.append(info)
        return self.log


class IO:
    def __init__(self):
    #self.frame_size = None
        self.path = None

    def readfile(self):
        path = input("Please enter File Name (eg. input1 、 input1.txt) : ")

        a = path[-4:]
        if a != '.txt':
            path = path + '.txt'
        self.path = path[:-4]
        f = None
        frame_size = None
        input_list = []
        try:
            f = open(path, 'r')
            frame_size = f.readline()
            input_list = f.readline()

        except IOError:
            print('Error: can not found ' + path)
            if f:
                f.close()
        finally:
            if f:
                f.close()

        return frame_size, input_list
        #return self.frame_size, input_list, path[:-4]

    def writefile(self, log):
        path_output = 'out_' + self.path + '.txt'
        with open(path_output, 'w', encoding='UTF-8') as f:
            for i in range(len(log)):
                for j in range(len(log[i])):
                    if j is 0 or j is len(log[i]) - 1:
                        f.write(log[i][j] + '\n')
                    else:
                        f.write(log[i][j][0])
                        f.write('\t')
                        for k in log[i][j][1]:
                            f.write(k)
                        if log[i][j][2] is 'F':
                            f.write('\t')
                            f.write(log[i][j][2])
                        f.write('\n')
                if i is not len(log) - 1:
                    f.write('\n')
        # for i in log:
        #     for j in i:
        #         print(j)
        #
        #     print()
        #     print()


if __name__ == '__main__':
    while True:
        io = IO()
        frame_size, job_list = io.readfile()
        write_log = []

        for round in range(6):
            if round is 0:
                simulate = Simulate(frame_size=int(frame_size), job_list=copy.deepcopy(job_list), task=1)
                write_log.append(simulate.getlog())
            elif round is 1:
                simulate = Simulate(frame_size=int(frame_size), job_list=copy.deepcopy(job_list), task=2)
                write_log.append(simulate.getlog())
            elif round is 2:
                simulate = Simulate(frame_size=int(frame_size), job_list=copy.deepcopy(job_list), task=3)
                write_log.append(simulate.getlog())
            elif round is 3:
                simulate = Simulate(frame_size=int(frame_size), job_list=copy.deepcopy(job_list), task=4)
                write_log.append(simulate.getlog())
            elif round is 4:
                simulate = Simulate(frame_size=int(frame_size), job_list=copy.deepcopy(job_list), task=5)
                write_log.append(simulate.getlog())
            elif round is 5:
                simulate = Simulate(frame_size=int(frame_size), job_list=copy.deepcopy(job_list), task=6)
                write_log.append(simulate.getlog())

        io.writefile(write_log)

        print('done')
        print()
        print()
