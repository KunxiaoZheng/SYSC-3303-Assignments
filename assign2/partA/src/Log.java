package partA;

public class Log {
	public static int nWorkers;
	public synchronized static void addWorker(){
		nWorkers++;
	}
	public synchronized static void removeWorker(){
		nWorkers--;
	}
}