package Task1;

/**
 * @Author Jakub Szwedowicz
 * @Create 17.03.2021
 * @Version 1.0
 */
public class Process {
    // MEMBERS
    private int id;
    private static int nextID;
    private int timeRequired;
    private int timeRemaining;
    private int timeWaited;
    private int priority;

    // PUBLIC
    public Process(int timeRequired, int priority) {
        this.id = nextID++;
        this.timeRequired = timeRequired;
        this.timeRemaining = timeRequired;
        this.priority = priority;
    }

    public Process(int id, int timeRequired, int priority) {
        if(id >= nextID){
            nextID = id + 1;
        }
        this.id = id;
        this.timeRequired = timeRequired;
        this.timeRemaining = timeRequired;
        this.priority = priority;
    }

    public boolean executeProcess(int time) {
        timeRemaining -= time;
        return isFinished();
    }

    public boolean isFinished() {
        if (timeRemaining <= 0) {
            return true;
        }
        return false;
    }


    public int getTimeRequired() {
        return timeRequired;
    }

    public int getTimeRemaining() {
        return timeRemaining;
    }

    public int getPriority() {
        return priority;
    }

    public int getWaitedTime(){
        return timeWaited;
    }

    public void incrementTimeWaited(int time){
        timeWaited += time;
    }


    public String toString() {
        return "List1.Process: " + id + ", time required = " + timeRequired + ", priority = " + priority;
    }
}
