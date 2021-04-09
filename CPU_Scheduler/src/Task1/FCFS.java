package Task1;

import java.util.LinkedList;

/**
 * @Author Jakub Szwedowicz
 * @Create 18.03.2021
 * @Version 1.0
 */
public class FCFS extends Algorithm {
    public FCFS(LinkedList<Process> processesQueue, CPU cpu, int chanceForNewProcess){
        super(processesQueue, cpu, chanceForNewProcess);
    }

    @Override
    public int run() {
        while(true){
            if(cpu.getProcessFinished()){
                if(processesQueue.isEmpty()){
                    break;
                }
                Process proc = getNextProcess();
                waitingTimeSum += proc.getWaitedTime();
                processesFinished++;
                cpu.assignProcess(proc);
            }
            cpu.doCycle();
            maybeAddNewRandomProcess();
            incrementWaitingTime();
        }
        return waitingTimeSum/processesFinished;
    }


    @Override
    protected void addToQueue(Process process) {
        processesQueue.add(process);
    }


}
