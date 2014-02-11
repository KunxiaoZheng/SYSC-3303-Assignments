package partA;
import java.util.concurrent.*;

public class TestDriver {
	public static void main(String[] args) throws InterruptedException, ExecutionException {
		ExecutorService executor= Executors.newCachedThreadPool();
		Worker worker=new Worker(5);
		Future<Integer>test=executor.submit(worker);
		System.out.print(executor);
        int val=test.get();     
        System.out.println(val);
	}
}
