class MyChar extends Element{
	private char content;
	public MyChar(){
		//default constructor
		content = '0';
	}
	
	public char Get(){ return content; }
	public void Set(char val){ content = val; }
}

class MyInteger extends Element {
	private int content;
	public MyInteger(){
		content = 0;
	}
	
	public int  Get(){ return content; }
	public void Set(int val){ content = val; }
}

class Sequence extends Element {
	private Element content;
	private Sequence next;
	public Sequence(){
		//default constructor
		// . . .
		content = null;
		next = null;
	}
	public Element Get(){ return content; }
	public void Set(Element val){ content = val; }
}

class Main {
	public static void main(String[] args){
		System.out.println("Successfully compiled!");
	}
}
