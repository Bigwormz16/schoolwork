class MyChar extends Element{
	private char content;
	public MyChar(){
		//default constructor
		content = '0';
	}
	
	public MyChar(char val){
		content = val;
	}
	
	public char Get(){ return content; }
	public void Set(char val){ content = val; }
	
	@Override
	public void Print(){
		System.out.print("\'" + content + "\'");
	}
}

class MyInteger extends Element {
	private int content;
	public MyInteger(){
		content = 0;
	}
	
	public MyInteger(int val){
		content = val;
	}
	
	public int  Get(){ return content; }
	public void Set(int val){ content = val; }
	
	// part 2 - print method
	@Override
	public void Print(){
		System.out.print(content);
	}
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
	
	public Sequence(Element elm, Sequence seq){
		content = elm;
		next = seq;
	}
	public Element Get(){ return content; }
	public void Set(Element val){ content = val; }
	
	// part 2 funcs
	@Override
	public void Print(){
		// print sequence
		System.out.print("[ ");
		if(content != null){
			content.Print();
		}
		
		Sequence iter = this.next;
		while(iter != null){
			if(iter.content != null){
				System.out.print(' ');
				iter.content.Print();
			}
			iter = iter.next;
		}
		System.out.print(" ]");
	}
	
	public Element first(){
		return content;
	}
	
	public Sequence rest(){
		return next;
	}
	
	public int length(){
		//
		int count = 0;
		Sequence iter = next;
		while(iter != null){
			iter = iter.next;
			count++;
		}
		
		return count;
	}
	
	public void add(Element elm, int pos){
		if(pos > this.length()){
			System.err.println("Error: pos greater than sequence length!");
			System.exit(-1);
		}
		
		//special case
		if(pos == 0){
			//copy current head
			Sequence temp = new Sequence(this.content, this.next);
			//swap head element
			this.content = elm;
			//change link to copied head
			this.next = temp;
			
			return; //done
		}
			
		Sequence iter = this;
		Sequence prev = new Sequence();
		int count = 0;
		while(count < pos){
			if(iter.next == null){
				break;
			}
			prev = iter; //TODO: do this the non-lazy way
			iter = iter.next; //go through the links
			count++;
		}
		
		if(count != pos){
			System.err.println("Error: couldn't add element to sequence.");
			System.exit(-1);
		}
		prev.next = new Sequence(elm, iter);
	}
	
	public void delete(int pos){
		//check if pos exists
		if(pos > this.length()){
			return;
		}
	
		if(pos == 0){
			content = this.next.content;
			this.next = this.next.next;
			
			return;
		}
	
		int count = 0;
		Sequence iter = this;
		Sequence prev = new Sequence();
		while(count < pos){
			if(iter.next == null){
				break;
			}
			prev = iter; //TODO: make non-lazy
			iter = iter.next; //go through the links
			count++;
		}
		
		//probably not necessary - TODO: delete
		if(count != pos){
			System.err.println("Error: couldn't remove element from sequence.");
			System.exit(-1);
		}
		
		//iter is the item that we wish to remove
		//skip past it in links, gc will collect it
		prev.next = iter.next;
	}
	
}

class Main {
	public static void main(String[] args){
		System.out.println("Successfully compiled!");
		
		//test classes
		MyChar a = new MyChar('a');
		MyChar b = new MyChar('b');
		MyChar c = new MyChar('c');
		
		MyInteger t1 = new MyInteger(1);
		MyInteger t2 = new MyInteger(2);
		MyInteger t3 = new MyInteger(3);
		
		Sequence seq = new Sequence();
		seq.add(c, 0);
		seq.add(b, 0);
		seq.add(a, 0);
		
		seq.Print();
		
		seq.delete(0);
		
		seq.Print();
				
		System.exit(0);
	}
}
