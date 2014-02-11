package partA;

import java.util.concurrent.Callable;


public class Worker implements Callable<Integer>{
	int time;
	public Worker (int time){
		this.time= time;
	}
	@Override
	public Integer call() throws Exception {
		Log.addWorker();
		Log.removeWorker();
		return time;
	}

}
