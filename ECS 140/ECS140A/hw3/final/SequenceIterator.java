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