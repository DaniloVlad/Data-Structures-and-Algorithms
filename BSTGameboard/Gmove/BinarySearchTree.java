//ran out of time, sorry!
public class BinarySearchTree implements BinarySearchTreeADT {
	private BinaryNode root;
	//create tree
	public BinarySearchTree() {
		this.root = new BinaryNode();

	}
	//	return root node
	public BinaryNode getRoot() {
		return this.root;
	}

	//search for pixel
	public Pixel get(BinaryNode r, Location key) {
		if(r.isLeaf())
			return null;
		else { //main comparisons for decision making
			int cmp = r.getData().getLocation().compareTo(key);
			if(cmp < 0) 
				return get(r.getRight(), key);
			 else if(cmp > 0)
				return get(r.getLeft(), key);
			 else
				 return r.getData();
		}
	}

	
	public void put(BinaryNode r, Pixel data) throws DuplicatedKeyException {
		if(r.isLeaf()) { //base case, insert a node
			r.setData(data);
			r.setLeft(new BinaryNode());
			r.getLeft().setParent(r);
			r.setRight(new BinaryNode());
			r.getRight().setParent(r);
		
		}
		else {
			Pixel cmp = this.get(this.root, data.getLocation());
			
			if(cmp != null) //no 2 keys!!
				throw new DuplicatedKeyException("Dup :(");
			else {
				if(r.getData().getLocation().compareTo(data.getLocation()) > 0)
					 put(r.getLeft(), data); //only have to go one way or the other
				else
					put(r.getRight(),data);
			}
		}
	
			
	}
	
	public void remove(BinaryNode r, Location key) throws InexistentKeyException {
		//do check and throw necessary exception
		Pixel tmp = this.get(r, key);
		if(tmp ==null && r == this.root)
			throw new InexistentKeyException("No such key!");
		else {
			int main = r.getData().getLocation().compareTo(key);
			if(r.isLeaf()) //ikr 
				r.setData(null);
			else {
				if(main >0)
					remove(r.getLeft(), key); //...
				else if(main < 0)
					remove(r.getRight(), key);
				
			}
			
		
		}
		
		
	}
	
	public Pixel successor(BinaryNode r, Location key) {
		//check if key is in span of the set
		//do the rest of the maths
		Pixel cmp;
		try {
			cmp = largest(r);
		} catch (EmptyTreeException e) {
			return null;
		}
		
		if(cmp.getLocation().compareTo(key)<0)
			return cmp;
			
		
		else if(cmp.getLocation().compareTo(key) > 0) {
			if(r.getRight().isLeaf())
				return r.getRight().getData();
			else
				return successor(r.getRight(), key);
		}
		else
			return cmp;
	}


	public Pixel predecessor(BinaryNode r, Location key) {
		//almost got here
		
	}

	
	public Pixel smallest(BinaryNode r) throws EmptyTreeException {
		if(r.getLeft().isLeaf())
			return r.getLeft().getData();
		else
			return smallest(r.getLeft().getLeft()); //too the left too the left 
	}

	
	public Pixel largest(BinaryNode r) throws EmptyTreeException {
		if(r.isLeaf())
			throw new EmptyTreeException("no tree!");
		if(r.getRight().isLeaf())
			return r.getRight().getData();
		else
			return smallest(r.getRight().getRight()); //same thing in reverse 
		
	}
}
