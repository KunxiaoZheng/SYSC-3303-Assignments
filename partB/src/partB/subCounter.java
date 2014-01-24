package partB;

public class subCounter implements Runnable{
	
	public void run(){
		for (int i =100000;i>0;i--){
			partB.number--;
		}
		//System.out.print(partB.number);
	}

}
