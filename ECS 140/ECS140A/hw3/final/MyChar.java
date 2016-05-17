class MyChar extends Element{
	private char content;
	public MyChar(){
		//default constructor
		content = '0';
	}
	
	public MyChar(char val){
		content = val;
	}
	
	public MyChar(MyChar src){
		//copy constructor for pt3
		this.content = src.content;
	}
	
	@Override
	public MyChar copy(){
		return (new MyChar(this));
	}
	
	public char Get(){ return content; }
	public void Set(char val){ content = val; }
	
	@Override
	public void Print(){
		System.out.print("\'" + content + "\'");
	}

	public boolean equals(MyChar other){
		if(this.content == other.content){
			return true;
		}

		return false;
	}
}