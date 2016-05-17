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

class Sequence extends Element {
	protected Element content;
	protected Sequence next;

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
		//TODO: look into adding this later
		if(elm == this){
			System.err.println("Recursive adds are not allowed.");
			System.exit(-1);
		}
	
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
	
	//part 3 functions
	public Element index(int pos){
		//check range
		if(pos > this.length()){
			System.err.println("Error: index out of range.");
			System.exit(-1);
		}
		
		//iterate to pos index
		int count = 0;
		Sequence iter = this;
		while(count < pos){
			iter = iter.next;
			count++;
		}
		
		//return the element
		return iter.content;
	}
	
	public Sequence flatten(){
		Sequence iter = this;
		Sequence nestedSeq;
		Sequence newSeq = new Sequence();
		
		int addPoint = 0;
//		Sequence nestedIter;
		while(iter != null){
			//check if content item is a sequence
			if(iter.content instanceof Sequence){
				//recursively call flatten (must be cast to sequence to compile)
				nestedSeq = ((Sequence)iter.content).flatten();
				
				//copy new seq into our current sequence
				while(nestedSeq != null){
					//add element to the back
					newSeq.add(nestedSeq.content, addPoint);
					
					//iterate to next item in seq
					nestedSeq = nestedSeq.next;
					addPoint++;
				}
				
			} else { //if content isnt a sequence
				//just add it to the back
				newSeq.add(iter.content, addPoint);
				addPoint++;
			}
			
			iter = iter.next;
		} //end while
		
		return newSeq;
	}
	
	@Override
	public Sequence copy(){
		//basically the same code as flatten,
		//just copy the recursive reference		
		Sequence iter = this;
		Sequence nestedSeq;
		Sequence newSeq = new Sequence();
		
		int addPoint = 0;
		while(iter != null){
			//check if content item is a sequence
			if(iter.content instanceof Sequence){
				//grab a recursive copy
				nestedSeq = ((Sequence)iter.content).copy();
				
				//add new seq into our current sequence
				newSeq.add(nestedSeq, addPoint);
				/*while(nestedSeq != null){
					//add element to the back
					newSeq.add(nestedSeq.content, addPoint);
					
					//iterate to next item in seq
					nestedSeq = nestedSeq.next;
					addPoint++;
				}*/
				
			} else { //if content isnt a sequence
				//just add it to the back TODO double check if this is deep
				if(iter.content != null){
					newSeq.add(iter.content.copy(), addPoint);
				} else {
					//content is null
					//just add a null to the seq for now
					newSeq.add(null, addPoint);
				}
			}
			addPoint++; //moved outside of if-statement
			iter = iter.next;
		} //end while
		
		return newSeq;
	}

	//part 4 iterator funcs
	public SequenceIterator begin(){
		return (new SequenceIterator(this));
	}

	public SequenceIterator end(){
		Sequence iter = this;

		//iterate to end
		while(iter.next != null){
			iter = iter.next;
		}

		//found the end -> return a seq. iter
		return (new SequenceIterator(iter));
	}
}


//part 4
class SequenceIterator {
	protected Sequence iter;

	public SequenceIterator(){
		iter = null;
	}

	public SequenceIterator(Sequence seq){
		iter = seq;
	}

	public void advance(){
		//use rest func since Sequence.next is private
		iter = iter.rest();
	}

	public Element get(){
		return iter.Get();
	}

	public boolean equal(SequenceIterator other){
		// todo: possibly check iter as well
		if(this.iter == other.iter){
			return true;
		} else {
			return false;
		}
	}
}

//part 5
class Matrix extends Sequence {
	// private Sequence content;
	// 
	// constructor for creating a matrix of specific number of rows and columns
	private int rowsize, colsize;

	public Matrix(int rowsize, int colsize){
		//fill out the sequence
		for(int i = 0; i < rowsize * colsize; i++){
			//link a bunch of MyInts together
			this.add(new MyInteger(), 0);
		}

		this.rowsize = rowsize;
		this.colsize = colsize;
	}

	public void Set(int row, int col, int value){
		//set the value of an element
		//row * colsize + column
		//[0, 0] -> postion 0
		//[1, 1] -> 1*colsize + 1 -> 
		Sequence iter = this;
		int position = (row*colsize) + col;
		for(int i = 0; i < position; i++){
			iter = iter.next;
		}

		//iter now at [row][col], set the value
		((MyInteger)iter.content).Set(value);
	}

	public int Get(int row, int col){
		//get the value of an element
		Sequence iter = this;
		int position = (row*colsize) + col;
		for(int i = 0; i < position; i++){
			iter = iter.next;
		}

		//iter now at [row][col], grab the value
		return ((MyInteger)iter.content).Get();
	}

	public Matrix Sum(Matrix mat){
		//return the sum of two matrices: mat & this

		//assert that matrices have same bounds
		if(this.rowsize != mat.rowsize || this.colsize != mat.colsize){
			System.err.println("Error: matrix size mismatch!");
			System.exit(-1);
		}

		//item to be returned
		Matrix sumMatrix = new Matrix(this.rowsize, this.colsize);
		Sequence sumIter = sumMatrix; //iterator to set values

		SequenceIterator mat1 = this.begin(),
						 mat2 = mat.begin();

		for(int i = 0; i < this.length(); i++){
			//sum = mat1 value + mat2 value
			//(Get() called twice, second time grabs int from MyInteger)
			//todo: fix this disgusting mess - generic abstract in element class
			((MyInteger)sumIter.content).Set(((MyInteger)mat1.get()).Get() + ((MyInteger)mat2.get()).Get());

			//advance all the iterators
			sumIter = sumIter.next;
			mat1.advance();
			mat2.advance();
		}

		return sumMatrix;
	}

	public Matrix Product(Matrix mat){
		//return the product of two matrices: mat & this
		if(this.colsize != mat.rowsize){
			System.out.println("Matrix dimensions incompatible for Product");
			System.exit(-1);
		}

		int result = 0; //holds the sum of products

		Matrix prodMatrix = new Matrix(this.rowsize, mat.colsize);
		//dot product: new dimensions = rows from first matrix, columns from 2nd
		//i = row, j = column -> mult elements of each row by elements of each column
		for(int i = 0; i < this.rowsize; i++){
			//add upp
			for(int j = 0; j < mat.colsize; j++){
				//element in row * element in column
				//add up row_element * col_element
				result = 0;
				for(int k = 0; k < this.colsize; k++){
					/*int a = this.Get(i, k); <-- fixed row for 1st matrix
					int b = mat.Get(k, j);    <-- fixed column for 2nd matrix */
					int a = this.Get(i, k);
					int b =  mat.Get(k, j);
					//System.err.println("Multiplying " + a + " by " + b + " = " + (a*b));
					result = result + (a * b);
				}

				prodMatrix.Set(i, j, result); //set result
				//result = 0; //clear the sum for next calculation
			}
		}

		return prodMatrix;
	} //end product

	@Override
	public void Print(){
		//print the elements of matrix
		for(int row = 0; row < rowsize; row++){
			System.out.print("[ "); //begin with a bracket
			for(int col = 0; col < colsize; col++){
				//value separated by spaces
				System.out.print(this.Get(row, col) + " ");
			}
			System.out.println("]"); //end of row
		}
	} //end of print

} //end of Matrix

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

class MapIterator extends SequenceIterator {
	//private Sequence iter;

	public MapIterator(Sequence seq){
		iter = seq;
	}

	public void advance(){
		//use rest func since Sequence.next is private
		iter = iter.rest();
	}

	public Pair get(){
		return (Pair)iter.Get();
	}

	public boolean equal(MapIterator other){
		if(this.iter == other.iter){
			return true;
		} else {
			return false;
		}
	}

	public boolean hasNext(){
		if(iter.next != null){
			return true;
		} else {
			return false;
		}
	}
}

class Map extends Sequence {
	public Map(){
		super();

	}

	public void add(Pair inval){
		//place to add the item in the sequence
		int position = 0;

		if(length() == 0){
			add(inval, 0);
			return;
		}

		char this_key, other_key;

		MapIterator iter = new MapIterator(this);
		while(iter.hasNext()){
			//a > b is false
			//if key is greater alphabetically,
			//break from loop
			this_key = iter.get().GetKey().Get();
			if(iter.get().greater(inval) == false){
				break;
			}

			//otherwise, increment spot
			iter.advance();
			position++;
		}
		//call the superclass method to do the rest
		super.add(inval, position);
	}

	public MapIterator find(MyChar key){
		MapIterator iter = new MapIterator(this);
		while(iter.hasNext()){
			if( iter.get().is(key) ){
				return iter;
			}

			iter.advance();
		}

		//otherwise, return null [TODO: for now]
		return end();
	}

	public MapIterator begin(){
		return (new MapIterator(this));
	}

	public MapIterator end(){
		Sequence iter = this;

		//iterate to end
		while(iter.next != null){
			iter = iter.next;
		}

		//found the end -> return a seq. iter
		return (new MapIterator(iter));
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
		
		Sequence seq2 = new Sequence();
		seq2.add(t3, 0);
		seq2.add(t2, 0);
		seq2.add(t1, 0);
		
		seq2.add(seq, 0);
		
//		seq.add(seq, 0);
		
		System.out.println("a");
		seq.Print();
		
		seq2.Print();
		
		System.out.println("a");
		seq2.flatten().Print();
				
		System.exit(0);
	}
}
