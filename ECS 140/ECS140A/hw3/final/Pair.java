//part 6
class Pair extends Element {
	private MyChar key;
	private Element value;

	public Pair(){
		key = null;
		value = null;
	}

	public Pair(MyChar key, Element value){
		this.key = key;
		this.value = value;
	}

	@Override
	public void Print(){
		System.out.print("(");
		key.Print();
		System.out.print(" ");
		value.Print();
		System.out.print(")");
	}

	@Override
	public Pair copy(){
		return (new Pair(key, value));
	}

	public boolean is(MyChar inKey){
		if(key.equals(inKey))
			return true;

		return false;
	}

	public Element Get(){ return value; }
	public MyChar GetKey(){ return key; }
	public void Set(Element e){
		value = e;
	}

	public boolean greater(Pair other){
		//return true if this.key comes earlier in the alphabet
		//check a few preconditions (null values)
		if(this.key == null){
			return false;
		} else if(other == null){
			return true;
		} else if(other.key == null){
			return true;
		}

		//compare keys
		//a < b
		if(this.key.Get() <= other.key.Get()){
			//this key is higher in alphabet than other
			return true;
		} else {
			return false;
		}
	}
}