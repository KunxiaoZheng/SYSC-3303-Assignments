package partB;

public class partB {
	public static long number;
	public static void main(String [] args)throws InterruptedException{
		number=0;
		addCounter add=new addCounter();
		subCounter sub=new subCounter();
		Thread[] addThreads=new Thread[5];
		Thread[] subThreads=new Thread[5];
		
		for(int i =0; i<5;i++){
			addThreads[i]=new Thread(add);
			subThreads[i]=new Thread(sub);
			addThreads[i].start();
			subThreads[i].start();
		}
		for(int i =0; i<5;i++){
			addThreads[i].join();
			subThreads[i].join();
		}
		System.out.print(number);
	}
}
