import java.awt.List;
import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.*;
public class TestDriver {

	public static ThreadPoolExecutor executor;
	public static ArrayList<Future<String>> workerList;

	public static void main(String[] args) throws InterruptedException, ExecutionException {
		//creating thread pool executor
		final ThreadPoolExecutor executor= (ThreadPoolExecutor)Executors.newCachedThreadPool();
		Random generator = new Random(); 
		final ArrayList<Future<String>> workerList=new ArrayList<Future<String>>(500);
		//adding workers
		for(int i =1;i<=500;i++){
			Worker worker=new Worker(i, generator.nextInt(19999) + 1);
			workerList.add(executor.submit(worker));
		}
		//a thread that displays info about executor
		executor.submit(new Runnable(){
			@Override
			public void run() {
				boolean done =true;
				int test =3;
				while(done){
					try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					if(workerList.size()==0&&test>0){
						test--;
					}else if(workerList.size()==0&&test==0){
						done=false;
					}else{
						for (int i = 0; i < workerList.size(); i++) {
							done=false;
							if (!workerList.get(i).isDone()) {
								i = workerList.size();
								done=true;
							}
						}
					}
					System.out.println("\n"+executor);
					System.out.println("number of workers currently in the log are:"+Log.nWorkers+"\n");
				}
			}
		});
		String result;		

		//print out the worker who is finished
		while(workerList.size()!=0){
			for (int i = 0; i < workerList.size(); i++) {
				if (workerList.get(i).isDone()) {
					result=workerList.get(i).get();
						System.out.println(result);
					workerList.remove(i);
				}
			}
		}
		executor.shutdown();    
		Thread.sleep(2200);
		System.out.println("done");
	}	
}
