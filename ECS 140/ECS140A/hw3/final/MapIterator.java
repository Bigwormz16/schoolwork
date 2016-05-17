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