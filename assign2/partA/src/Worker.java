import java.util.concurrent.Callable;


public class Worker implements Callable<String>{
	int time;
	int name;
	long start,end;
	int startLog,endLog;
	public Worker (int num,int time){
		name=num;
		this.time= time;
		startLog=Log.getNumWorker();
	}
	@Override
	public String call() throws Exception {
		Log.addWorker();	//add this worker to the log
		start=System.currentTimeMillis();//get the start time
		Thread.sleep(time);
		endLog=Log.getNumWorker();		
		end=System.currentTimeMillis();//get the end time
		Log.removeWorker();		//remove this worker from the log
		return "Worker #"+name+": start with "+startLog+" workers in the log and end with "
		+endLog+" workers in the log"+
		"\nworked for "+(int)(end-start)+
		"ms, with expected time "+time+"ms.";
	}

}
