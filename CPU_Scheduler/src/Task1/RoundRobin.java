package Task1;

import java.util.LinkedList;

/**
 * @Author Jakub Szwedowicz
 * @Create 19.03.2021
 * @Version 1.0
 */
public class RoundRobin extends Algorithm {
    public RoundRobin(LinkedList<Process> processesQueue, CPU cpu, int chanceForANewProcess) throws IllegalArgumentException {
        super(processesQueue, cpu, chanceForANewProcess);
    }

    @Override
    protected void addToQueue(Process process) {
        processesQueue.add(process);
    }

    @Override
    public int run() {
        while(true){
            cpu.assignProcess(processesQueue.removeFirst());
            cpu.doCycle();
            maybeAddNewRandomProcess();
            incrementWaitingTime();
            if(cpu.getProcessFinished()){
                Process proc = cpu.takeActiveProcess();
                waitingTimeSum += proc.getWaitedTime();
                processesFinished++;
                if(processesQueue.isEmpty()){
                    break;
                }
            } else {
                processesQueue.add(cpu.takeActiveProcess());
            }
        }
        return waitingTimeSum/processesFinished;
    }
}
