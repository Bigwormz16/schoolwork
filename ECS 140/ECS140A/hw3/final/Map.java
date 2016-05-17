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