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