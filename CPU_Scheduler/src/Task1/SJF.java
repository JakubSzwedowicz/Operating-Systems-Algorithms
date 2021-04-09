package Task1;

import java.util.Iterator;
import java.util.LinkedList;

/**
 * @Author Jakub Szwedowicz
 * @Create 18.03.2021
 * @Version 1.0
 */
public class SJF extends Algorithm {

    public SJF(LinkedList<Process> processesQueue, CPU cpu, int chanceForNewProcess){
        super(processesQueue, cpu, chanceForNewProcess);
    }

    @Override
    protected void addToQueue(Process process) {
        Iterator it = processesQueue.iterator();
        int i = 0;
        while(it.hasNext()){
            Process proc = (Process) it.next();
            if(proc.getTimeRemaining() > process.getTimeRemaining()){
                break;
            }
            i++;
        }
        processesQueue.add(i, process);
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
}
