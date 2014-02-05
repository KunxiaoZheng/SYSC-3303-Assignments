package partA;

public class TestDriver {

	public static void main(String[] args) {
		Executor executor= new Executor();
		executor.newCachedThreadPool(2);
	}

}
