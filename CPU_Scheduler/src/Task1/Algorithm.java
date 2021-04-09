package Task1;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.LinkedList;
import java.util.Random;
import java.util.Scanner;

/**
 * @Author Jakub Szwedowicz
 * @Create 17.03.2021
 * @Version 1.0
 */

public abstract class Algorithm {
    protected LinkedList<Process> processesQueue;
    protected CPU cpu;
    private final int chanceForANewProcess;
    private Random generator;
    private int executionPower;
    protected int waitingTimeSum;
    protected int processesFinished;

    public Algorithm(LinkedList<Process> processesQueue, CPU cpu, int chanceForANewProcess) throws IllegalArgumentException{
        if(chanceForANewProcess < 0 || chanceForANewProcess > 100){
            throw new IllegalArgumentException("Chance for a new process has to be in range [0, 100]!\n\t change = " + chanceForANewProcess);
        }
        this.processesQueue = processesQueue;
        this.cpu = cpu;
        this.executionPower = cpu.getExecutionPower();
        this.waitingTimeSum = 0;
        if(chanceForANewProcess == 0){
            chanceForANewProcess--;
        }
        this.chanceForANewProcess = chanceForANewProcess;
        generator = new Random();
    }

    protected abstract void addToQueue(Process process);

    protected Process getNextProcess() {
//        List1.Process res = processesQueue.getFirst();
        Process res = processesQueue.removeFirst();
        return res;
    }

    public abstract int run();

    public void loadProcessesFromFile(String filename){
        try(Scanner reader = new Scanner(new FileReader(filename))){
            String line;
            int[] processData = new int[3];
            while(reader.hasNextInt()){
                processData[0] = reader.nextInt();
                processData[1] = reader.nextInt();
                processData[2] = reader.nextInt();
                addToQueue(new Process(processData[0], processData[1], processData[2]));
            }
        } catch (FileNotFoundException ex){
            ex.printStackTrace();
        }
    }

    protected void maybeAddNewRandomProcess(){
        int roll = generator.nextInt(101);
        if(roll < chanceForANewProcess){
            Process newProcess = generateNewProcess();
            addToQueue(newProcess);
        }
    }

    private Process generateNewProcess(){
        int timeRequired = generator.nextInt(26);
        int priority = generator.nextInt(140);
        return new Process(timeRequired, priority);
    }

    protected void incrementWaitingTime(){
        for(Process p : processesQueue){
            p.incrementTimeWaited(executionPower);
        }
    }
    protected boolean hasNextProcess(){
        return !processesQueue.isEmpty();
    }

}
