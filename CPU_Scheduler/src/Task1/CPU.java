package Task1;

/**
 * @Author Jakub Szwedowicz
 * @Create 17.03.2021
 * @Version 1.0
 */
public class CPU {
    //MEMBERS
    private Process activeProcess;
    private boolean processFinished;
    private final int executionPower;

    // PUBLIC
    public CPU(int executionPower) {
        this.executionPower = executionPower;
        this.activeProcess = null;
        this.processFinished = true;
    }

    public void assignProcess(Process process) {
        activeProcess = process;
        processFinished = false;
    }

    public void doCycle() {
        if(activeProcess != null){
            processFinished = activeProcess.executeProcess(executionPower);
        }
    }

    public Process takeActiveProcess() {
        Process res = activeProcess;
        activeProcess = null;
        processFinished = true;
        return res;
    }
    public Process getActiveProcess() {
        return activeProcess;
    }

    public int getExecutionPower(){
        return executionPower;
    }

    public boolean getProcessFinished() {
        return processFinished;
    }

}
