package Task1;

import java.util.LinkedList;

/**
 * @Author Jakub Szwedowicz
 * @Create 18.03.2021
 * @Version 1.0
 */
public class SJF_Preemptive extends SJF{
    public SJF_Preemptive(LinkedList<Process> processesQueue, CPU cpu, int chanceForNewProcess){
        super(processesQueue, cpu, chanceForNewProcess);
    }

    @Override
    protected void addToQueue(Process process) {
        if(!cpu.getProcessFinished()){
            if(cpu.getActiveProcess().getTimeRemaining() > process.getTimeRemaining()){
                Process proc = cpu.takeActiveProcess();
                waitingTimeSum -= proc.getWaitedTime();
//                processesFinished--;
//                waitingTimeSum += process.getWaitedTime();    when
//                processesFinished++;
                cpu.assignProcess(process);
                process = proc;
            }
        }
        super.addToQueue(process);
    }
}
