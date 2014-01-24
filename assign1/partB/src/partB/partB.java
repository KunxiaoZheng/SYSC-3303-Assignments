package partB;

public class partB {
	public static long number;
	public static void main(String [] args)throws InterruptedException{
		number=0;
		int numOfThreads=5;
		addCounter add=new addCounter();
		subCounter sub=new subCounter();
		Thread[] addThreads=new Thread[numOfThreads];
		Thread[] subThreads=new Thread[numOfThreads];
		
		for(int i =0; i<numOfThreads;i++){
			addThreads[i]=new Thread(add);
			subThreads[i]=new Thread(sub);
			addThreads[i].start();
			subThreads[i].start();
		}
		for(int i =0; i<numOfThreads;i++){
			addThreads[i].join();
			subThreads[i].join();
		}
		System.out.print(number);
	}
}
