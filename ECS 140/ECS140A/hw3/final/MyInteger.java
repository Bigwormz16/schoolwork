class MyInteger extends Element {
	private int content;
	public MyInteger(){
		content = 0;
	}
	
	public MyInteger(int val){
		content = val;
	}
	
	public MyInteger(MyInteger src){
		//copy constructor for pt3
		this.content = src.content;
	}
	
	@Override
	public MyInteger copy(){
		return (new MyInteger(this));
	}
	
	public int  Get(){ return content; }
	public void Set(int val){ content = val; }
	
	// part 2 - print method
	@Override
	public void Print(){
		System.out.print(content);
	}
}