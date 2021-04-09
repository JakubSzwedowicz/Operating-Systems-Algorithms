package Task1;

import java.util.LinkedList;

/**
 * @Author Jakub Szwedowicz
 * @Create 19.03.2021
 * @Version 1.0
 */
public class List1 {
    public static void runTest(){
        int averageSum = 0;
        int cycles = 10;
        String filename = "Resources/process_list3";
        for(int i = 0; i < cycles; i++){
            Algorithm alg = new FCFS(new LinkedList<Process>(), new CPU(1), 5);
            alg.loadProcessesFromFile(filename);
            averageSum += alg.run();
        }
        System.out.println("First Come First Serve average time units after " + cycles + " cycles: " + averageSum / cycles);
        averageSum = 0;
        for(int i = 0; i < cycles; i++){
            Algorithm alg = new SJF(new LinkedList<Process>(), new CPU(1), 5);
            alg.loadProcessesFromFile(filename);
            averageSum += alg.run();
        }
        System.out.println("Shortest Job First average time units after " + cycles + " cycles: " + averageSum / cycles);
        averageSum = 0;
        for(int i = 0; i < cycles; i++){
            Algorithm alg = new SJF_Preemptive(new LinkedList<Process>(), new CPU(1), 5);
            alg.loadProcessesFromFile(filename);
            averageSum += alg.run();
        }
        System.out.println("Shortest Job First (preemptive variant) average time units after " + cycles + " cycles: " + averageSum / cycles);

        averageSum = 0;
        for(int i = 0; i < cycles; i++){
            Algorithm alg = new RoundRobin(new LinkedList<Process>(), new CPU(1), 5);
            alg.loadProcessesFromFile(filename);
            averageSum += alg.run();
        }
        System.out.println("Round Robin average time units after " + cycles + " cycles: " + averageSum / cycles);
    }
}
